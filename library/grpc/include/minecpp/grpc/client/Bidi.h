#ifndef MINECPP_GRPC_CLIENT_BIDI_H
#define MINECPP_GRPC_CLIENT_BIDI_H
#include <algorithm>
#include <future>
#include <grpcpp/grpcpp.h>
#include <mb/result.h>
#include <minecpp/grpc/Bidi.h>
#include <minecpp/util/Pool.h>

namespace minecpp::grpc::client {

template<typename TRead>
struct CompletionEvent
{
   EventType event_type;
   TRead *read_ptr;

   explicit CompletionEvent(EventType event_type, TRead *read_ptr = nullptr) :
       event_type(event_type),
       read_ptr(read_ptr)
   {
   }
};

static ::grpc::Status g_status{};

template<typename TWrite, typename TRead>
class Stream
{
   util::AtomicPool<CompletionEvent<TRead>> m_event_pool;
   util::AtomicPool<TRead> m_read_pool;
   std::unique_ptr<::grpc::ClientAsyncReaderWriter<TWrite, TRead>> m_stream;

 public:
   enum class GetNextError
   {
      Shutdown,
      BrokenSocket,
   };

   template<typename TStartFunc, typename TStub>
   explicit Stream(TStartFunc start, TStub *stub, ::grpc::ClientContext *ctx,
                   ::grpc::CompletionQueue *queue) :
       m_stream(std::invoke(start, stub, ctx, queue, m_event_pool.construct(EventType::Accept)))
   {
   }

   void write(const TWrite &message)
   {
      auto event = m_event_pool.construct(EventType::Write);
      m_stream->Write(message, event);
   }

   void read()
   {
      auto read_ptr = m_read_pool.construct();
      auto event    = m_event_pool.construct(EventType::Read, read_ptr);
      m_stream->Read(read_ptr, event);
   }

   void disconnect()
   {
      auto event = m_event_pool.construct(EventType::Disconnect);
      m_stream->Finish(&g_status, event);
   }

   void free_event(CompletionEvent<TRead> *event)
   {
      m_event_pool.free(event);
   }

   void free_object(TRead *event)
   {
      m_read_pool.free(event);
   }
};

template<typename TStub, typename TWrite, typename TRead, typename TCallback>
class Connection
{
   TCallback &m_callback;
   ::grpc::CompletionQueue m_queue;
   ::grpc::ClientContext m_ctx;
   std::shared_ptr<::grpc::Channel> m_channel;
   TStub m_stub;
   std::mutex m_next_lock;
   std::shared_ptr<Stream<TWrite, TRead>> m_stream;
   std::vector<std::future<mb::result<mb::empty>>> m_workers;

 public:
   enum class GetNextError
   {
      Shutdown,
      BrokenSocket,
   };

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
            m_callback.on_connected(std::weak_ptr<Stream<TWrite, TRead>>(m_stream));
            m_stream->free_event(event);
            continue;
         }
         case EventType::Write: {
            m_callback.on_finish_write(std::weak_ptr<Stream<TWrite, TRead>>(m_stream));
            m_stream->free_event(event);
            continue;
         }
         case EventType::Read: {
            m_callback.on_finish_read(std::weak_ptr<Stream<TWrite, TRead>>(m_stream), *event->read_ptr);
            m_stream->free_object(event->read_ptr);
            m_stream->free_event(event);
            continue;
         }
         case EventType::Disconnect: {
            m_callback.on_disconnect(std::weak_ptr<Stream<TWrite, TRead>>(m_stream));
            m_stream->free_event(event);
            m_queue.Shutdown();
            return mb::ok;
         }
         }

         return mb::error("unknown event type");
      }
   }

   template<typename TStartFunc>
   Connection(TStartFunc start, const std::string &address, TCallback &callback, std::size_t worker_count) :
       m_callback(callback),
       m_channel(::grpc::CreateChannel(address, ::grpc::InsecureChannelCredentials())),
       m_stub(m_channel),
       m_stream{std::make_shared<Stream<TWrite, TRead>>(start, &m_stub, &m_ctx, &m_queue)}
   {
      m_workers.resize(worker_count);
      std::generate(m_workers.begin(), m_workers.end(),
                    [this]() { return std::async(&Connection::worker_routine, this); });
   }

   ~Connection()
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
   mb::result<CompletionEvent<TRead> *, GetNextError> get_next()
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

      return static_cast<CompletionEvent<TRead> *>(tag_ptr);
   }
};

}// namespace minecpp::grpc::client

#endif//MINECPP_GRPC_CLIENT_BIDI_H
