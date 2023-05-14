#ifndef MINECPP_GRPC_SERVER_BIDI_H
#define MINECPP_GRPC_SERVER_BIDI_H
#include <future>
#include <grpcpp/grpcpp.h>
#include <mb/result.h>
#include <minecpp/container/Queue.h>
#include <minecpp/grpc/Bidi.h>
#include <minecpp/util/Pool.h>
#include <spdlog/spdlog.h>

namespace minecpp::grpc::server {

template<typename TStream>
struct CompletionEvent
{
   using read_type = typename TStream::read_type;

   EventType tag;
   std::shared_ptr<TStream> client;
   read_type *read_ptr;

   CompletionEvent(EventType tag, std::shared_ptr<TStream> client, read_type *read_ptr = nullptr) :
       tag(tag),
       client(client),
       read_ptr(read_ptr)
   {
   }
};

template<typename TServer>
class InternalStream
{
 public:
   enum class State
   {
      Disconnected,
      Connected,
   };

   using write_type = typename TServer::write_type;
   using read_type  = typename TServer::read_type;

   InternalStream() :
       m_stream(&m_context)
   {
   }

   void write(const write_type &message, void *tag)
   {
      if (m_write_mutex.try_lock()) {
         // critical section
         // we can write here
         m_stream.Write(message, tag);
         return;
      }

      m_write_queue.template push(std::make_tuple(message, tag));
   }

   void read(read_type *message, void *tag)
   {
      m_stream.Read(message, tag);
   }

   void disconnect(void *tag)
   {
      m_disconnect_handler();

      ::grpc::Status status{};
      m_stream.Finish(status, tag);
   }

   void bind_read_callback(std::function<void(const read_type &msg)> func)
   {
      m_read_handler = std::move(func);
   }

   void bind_disconnect_callback(std::function<void()> func)
   {
      m_disconnect_handler = std::move(func);
   }

   [[nodiscard]] State state() const
   {
      return m_state;
   }

   void on_connected()
   {
      m_state = State::Connected;
   }

   void on_finish_write()
   {
      if (m_write_queue.is_empty()) {
         // we're finished writing
         // and there is nothing more to write
         // we can unlock the mutex
         m_write_mutex.unlock();
         return;
      }

      // keep the mutex locked
      // we're in the critical section
      // let's pop another message

      auto [msg, tag] = m_write_queue.pop();
      m_stream.Write(std::move(msg), tag);
   }

   void on_finish_read(const read_type *msg)
   {
      assert(m_read_handler && "read handler should not be empty on send_to_player");

      // call the handler and read another message
      m_read_handler(*msg);
   }

   void on_disconnect()
   {
      m_state = State::Disconnected;
   }

   [[nodiscard]] ::grpc::ServerContext &context()
   {
      return m_context;
   }

   [[nodiscard]] ::grpc::ServerAsyncReaderWriter<write_type, read_type> &stream()
   {
      return m_stream;
   }

 private:
   std::function<void(const read_type &msg)> m_read_handler;
   std::function<void()> m_disconnect_handler;
   container::Queue<std::tuple<write_type, void *>> m_write_queue;
   State m_state{State::Disconnected};
   std::mutex m_write_mutex;

   ::grpc::ServerContext m_context;
   ::grpc::ServerAsyncReaderWriter<write_type, read_type> m_stream;
};

template<typename TServer>
class Stream
{
 public:
   using write_type             = typename TServer::write_type;
   using read_type              = typename TServer::read_type;
   using complention_event_type = CompletionEvent<InternalStream<TServer>>;

   Stream(std::shared_ptr<InternalStream<TServer>> server,
          util::AtomicPool<complention_event_type> &event_pool, util::AtomicPool<read_type> &read_pool) :
       m_server(std::move(server)),
       m_event_pool(event_pool),
       m_read_pool(read_pool)
   {
   }

   void write(const write_type &msg)
   {
      auto event = m_event_pool.template construct(EventType::Write, m_server);
      m_server->write(msg, event);
   }

   void disconnect()
   {
      auto event = m_event_pool.template construct(EventType::Disconnect, m_server);
      m_server->disconnect(event);
   }

   template<typename TInstance, typename TCallback>
   void bind_read_callback(TInstance *instance, TCallback callback)
   {
      m_server->bind_read_callback(
              [instance, callback](const read_type &msg) { std::invoke(callback, instance, msg); });
      read();
   }

   template<typename TInstance, typename TCallback>
   void bind_disconnect_callback(TInstance *instance, TCallback callback)
   {
      m_server->bind_disconnect_callback([instance, callback]() { std::invoke(callback, instance); });
   }

 private:
   void read()
   {
      auto msg   = m_read_pool.template construct();
      auto event = m_event_pool.template construct(EventType::Read, m_server, msg);
      m_server->read(msg, event);
   }

   std::shared_ptr<InternalStream<TServer>> m_server;
   util::AtomicPool<complention_event_type> &m_event_pool;
   util::AtomicPool<read_type> &m_read_pool;
};

template<typename TService, typename TWrite, typename TRead, auto FRequest>
class BidiServer
{
 public:
   using event_type      = CompletionEvent<InternalStream<BidiServer>>;
   using write_type      = TWrite;
   using read_type       = TRead;
   using connect_cb_type = std::function<void(Stream<BidiServer>)>;

   mb::result<mb::empty> worker_routine()
   {
      for (;;) {
         void *tag_ptr;
         bool queue_ok, data_ok;
         {
            std::lock_guard<std::mutex> lock(m_next_lock);
            queue_ok = m_queue->Next(&tag_ptr, &data_ok);
         }
         if (!queue_ok) {
            return mb::ok;
         }
         if (!data_ok) {
            spdlog::error("couldn't read data");
            continue;
         }

         auto event = static_cast<event_type *>(tag_ptr);

         switch (event->tag) {
         case EventType::Accept: {
            event->client->on_connected();
            m_connection_callback(Stream<BidiServer>(event->client, m_event_pool, m_read_pool));
            m_event_pool.free(event);
            accept();
            continue;
         }
         case EventType::Write: {
            event->client->on_finish_write();
            m_event_pool.free(event);
            continue;
         }
         case EventType::Read: {
            event->client->on_finish_read(event->read_ptr);

            auto msg        = m_read_pool.template construct();
            auto read_event = m_event_pool.template construct(EventType::Read, event->client, msg);
            event->client->read(msg, read_event);

            m_read_pool.free(event->read_ptr);
            m_event_pool.free(event);
            continue;
         }
         case EventType::Disconnect: {
            event->client->on_disconnect();
            m_event_pool.free(event);
            continue;
         }
         }

         return mb::error("invalid event type\n");
      }
   }

   template<typename TInstance, typename TCallback>
   explicit BidiServer(const std::string &bind_address, TInstance *instance, TCallback callback,
                       std::size_t worker_count) :
       m_connection_callback([instance, callback](Stream<BidiServer> stream) {
          std::invoke(callback, instance, std::move(stream));
       })
   {
      ::grpc::ServerBuilder builder;
      builder.AddListeningPort(bind_address, ::grpc::InsecureServerCredentials());
      builder.RegisterService(&m_service);
      m_queue  = builder.AddCompletionQueue();
      m_server = builder.BuildAndStart();
      m_workers.resize(worker_count);
      std::generate(m_workers.begin(), m_workers.end(),
                    [this]() { return std::async(std::launch::async, &BidiServer::worker_routine, this); });
   }

   ~BidiServer()
   {
      //      wait();
      m_server->Shutdown();
      m_queue->Shutdown();
   }

   auto accept()
   {
      auto stream = std::make_shared<InternalStream<BidiServer>>();
      auto event  = m_event_pool.construct(EventType::Accept, stream);
      std::invoke(FRequest, &m_service, &(stream->context()), &(stream->stream()), m_queue.get(),
                  dynamic_cast<::grpc::ServerCompletionQueue *>(m_queue.get()), event);
   }

   mb::emptyres wait()
   {
      std::vector<mb::emptyres> results;
      results.reserve(m_workers.size());
      std::for_each(m_workers.begin(), m_workers.end(),
                    [](std::future<mb::result<mb::empty>> &worker) { worker.wait(); });
      std::transform(m_workers.begin(), m_workers.end(), std::back_inserter(results),
                     [](std::future<mb::result<mb::empty>> &worker) -> mb::result<mb::empty> {
                        if (!worker.valid())
                           return mb::ok;
                        return worker.get();
                     });
      auto err_it = std::find_if(results.begin(), results.end(),
                                 [](const mb::result<mb::empty> &res) { return !res.ok(); });
      if (err_it == results.end()) {
         return mb::ok;
      }
      return *err_it;
   }

   BidiServer(const BidiServer &)                = delete;
   BidiServer &operator=(const BidiServer &)     = delete;
   BidiServer(BidiServer &&) noexcept            = delete;
   BidiServer &operator=(BidiServer &&) noexcept = delete;

 private:
   connect_cb_type m_connection_callback;
   TService m_service;
   std::unique_ptr<::grpc::CompletionQueue> m_queue;
   std::unique_ptr<::grpc::Server> m_server;
   std::vector<std::future<mb::result<mb::empty>>> m_workers;
   std::mutex m_next_lock;
   util::AtomicPool<event_type> m_event_pool;
   util::AtomicPool<TRead> m_read_pool;
};

}// namespace minecpp::grpc::server

#define MINECPP_DECLARE_BIDI_SERVER(name, service, proc, write, read) \
   using name = ::minecpp::grpc::server::BidiServer<service, write, read, &service::Request##proc>;

#endif//MINECPP_GRPC_SERVER_BIDI_H
