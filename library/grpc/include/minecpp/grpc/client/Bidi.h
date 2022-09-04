#ifndef MINECPP_GRPC_CLIENT_BIDI_H
#define MINECPP_GRPC_CLIENT_BIDI_H
#include <algorithm>
#include <functional>
#include <future>
#include <grpcpp/grpcpp.h>
#include <mb/result.h>
#include <minecpp/container/Queue.h>
#include <minecpp/grpc/Bidi.h>
#include <minecpp/util/Pool.h>

namespace minecpp::grpc::client {

template<typename TStream>
struct CompletionEvent
{
   using read_type = typename TStream::read_type;

   EventType event_type;
   std::shared_ptr<TStream> stream;
   read_type *read_ptr;

   explicit CompletionEvent(EventType event_type, std::shared_ptr<TStream> stream,
                            read_type *read_ptr = nullptr) :
       event_type(event_type),
       stream(stream),
       read_ptr(read_ptr)
   {
   }
};

template<typename TConnManager>
class InternalStream
{
 public:
   enum class State
   {
      Disconnected,
      Connected,
   };

   using write_type = typename TConnManager::write_type;
   using read_type  = typename TConnManager::read_type;
   using stub_type  = typename TConnManager::stub_type;

   explicit InternalStream(std::shared_ptr<::grpc::Channel> channel, std::unique_ptr<stub_type> stub) :
       m_channel{std::move(channel)},
       m_stub{std::move(stub)}
   {
   }

   template<typename TStartFunc>
   void start(TStartFunc start, ::grpc::ClientContext *ctx, ::grpc::CompletionQueue *queue, void *tag)
   {
      m_stream = std::invoke(start, m_stub.get(), ctx, queue, tag);
   }

   void write(const write_type &message, void *tag)
   {
      if (m_write_mutex.try_lock()) {
         m_stream->Write(message, tag);
         return;
      }

      m_write_queue.template emplace(message, tag);
   }

   void read(read_type *message, void *tag)
   {
      m_stream->Read(message, tag);
   }

   void disconnect(void *tag)
   {
      ::grpc::Status status;
      m_stream->Finish(&status, tag);
   }

   void bind_read_callback(std::function<void(const read_type &msg)> func)
   {
      m_read_handler = std::move(func);
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
      m_stream->Write(std::move(msg), tag);
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

      if (m_disconnect_handler) {
         m_disconnect_handler();
      }
   }

 private:
   std::shared_ptr<::grpc::Channel> m_channel;
   std::unique_ptr<stub_type> m_stub;
   container::Queue<std::tuple<write_type, void *>> m_write_queue;
   State m_state{State::Disconnected};
   std::function<void(const read_type &msg)> m_read_handler;
   std::function<void()> m_disconnect_handler;
   std::unique_ptr<::grpc::ClientAsyncReaderWriter<write_type, read_type>> m_stream;
   std::mutex m_write_mutex;
};

template<typename TConnManager>
class Stream
{
 public:
   using write_type = typename TConnManager::write_type;
   using read_type  = typename TConnManager::read_type;
   using stub_type  = typename TConnManager::stub_type;

   Stream(std::shared_ptr<InternalStream<TConnManager>> stream,
          util::AtomicPool<CompletionEvent<InternalStream<TConnManager>>> &event_pool,
          util::AtomicPool<read_type> &read_pool) :
       m_stream{std::move(stream)},
       m_event_pool{event_pool},
       m_read_pool{read_pool}
   {
   }

   Stream(Stream&& other) noexcept :
       m_stream{std::move(other.m_stream)},
       m_event_pool{other.m_event_pool},
       m_read_pool{other.m_read_pool}
   {
   }

   void write(const write_type &msg)
   {
      auto event = m_event_pool.construct(EventType::Write, m_stream);
      m_stream->write(msg, event);
   }

   void disconnect()
   {
      auto event = m_event_pool.construct(EventType::Disconnect, m_stream);
      m_stream->disconnect(event);
   }

   template<typename TInstance, typename TCallback>
   void bind_read_callback(TInstance *instance, TCallback callback)
   {
      m_stream->bind_read_callback(
              [instance, callback](const read_type &msg) { std::invoke(callback, instance, msg); });
      read();
   }

 private:
   void read()
   {
      auto read_ptr = m_read_pool.construct();
      auto event    = m_event_pool.construct(EventType::Read, m_stream, read_ptr);
      m_stream->read(read_ptr, event);
   }

   std::shared_ptr<InternalStream<TConnManager>> m_stream;
   util::AtomicPool<CompletionEvent<InternalStream<TConnManager>>> &m_event_pool;
   util::AtomicPool<read_type> &m_read_pool;
};

template<typename TStub, typename TWrite, typename TRead>
class ConnectionManager
{
 public:
   using write_type = TWrite;
   using read_type  = TRead;
   using stub_type  = TStub;
   using cb_type    = std::function<void(Stream<ConnectionManager>)>;

   enum class GetNextError
   {
      Shutdown,
      BrokenSocket,
   };

   template<typename TStartFunc, typename TInstance, typename TCallback>
   ConnectionManager(TStartFunc start, const std::vector<std::string> &addresses, TInstance *instance,
                     TCallback callback, std::size_t worker_count) :
       m_connection_callback([instance, callback](Stream<ConnectionManager> connection) {
          std::invoke(callback, instance, std::move(connection));
       })
   {
      for (const auto &address : addresses) {
         auto channel = ::grpc::CreateChannel(address, ::grpc::InsecureChannelCredentials());
         auto stub    = std::make_unique<TStub>(channel);
         auto stream  = std::make_shared<InternalStream<ConnectionManager>>(std::move(channel), std::move(stub));

         auto *event = m_event_pool.template construct(EventType::Accept, stream);
         stream->template start(start, &m_ctx, &m_queue, event);
      }

      m_workers.resize(worker_count);
      std::generate(m_workers.begin(), m_workers.end(),
                    [this]() { return std::async(&ConnectionManager::worker_routine, this); });
   }

   mb::result<mb::empty> worker_routine()
   {
      for (;;) {
         auto event_res = get_next();
         if (event_res.has_failed()) {
            if (event_res.err() == GetNextError::Shutdown) {
               return mb::ok;
            }
            return mb::error("error reading message");
         }
         auto &event = event_res.get();

         switch (event->event_type) {
         case EventType::Accept: {
            event->stream->on_connected();
            m_connection_callback(Stream<ConnectionManager>(event->stream, m_event_pool, m_read_pool));
            m_event_pool.free(event);
            continue;
         }
         case EventType::Write: {
            event->stream->on_finish_write();
            m_event_pool.free(event);
            continue;
         }
         case EventType::Read: {
            event->stream->on_finish_read(event->read_ptr);

            auto msg        = m_read_pool.template construct();
            auto read_event = m_event_pool.template construct(EventType::Read, event->stream, msg);
            event->stream->read(msg, read_event);

            m_read_pool.free(event->read_ptr);
            m_event_pool.free(event);
            continue;
         }
         case EventType::Disconnect: {
            event->stream->on_disconnect();
            m_event_pool.free(event);
            return mb::ok;
         }
         }

         return mb::error("unknown event type");
      }
   }

   ~ConnectionManager()
   {
      m_queue.Shutdown();
      wait();
   }

   mb::result<mb::empty> wait()
   {
      std::vector<mb::result<mb::empty>> results;
      results.reserve(m_workers.size());
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

 private:
   mb::result<CompletionEvent<InternalStream<ConnectionManager>> *, GetNextError> get_next()
   {
      void *tag_ptr;
      bool queue_ok, data_ok;

      std::lock_guard<std::mutex> lock(m_next_lock);
      queue_ok = m_queue.Next(&tag_ptr, &data_ok);

      if (!queue_ok) {
         return GetNextError::Shutdown;
      }
      if (!data_ok) {
         return GetNextError::BrokenSocket;
      }

      return static_cast<CompletionEvent<InternalStream<ConnectionManager>> *>(tag_ptr);
   }

   cb_type m_connection_callback;
   ::grpc::CompletionQueue m_queue;
   ::grpc::ClientContext m_ctx;
   std::shared_ptr<::grpc::Channel> m_channel;
   std::mutex m_next_lock;
   std::vector<std::future<mb::result<mb::empty>>> m_workers;
   util::AtomicPool<CompletionEvent<InternalStream<ConnectionManager>>> m_event_pool;
   util::AtomicPool<TRead> m_read_pool;
};

}// namespace minecpp::grpc::client

#endif//MINECPP_GRPC_CLIENT_BIDI_H
