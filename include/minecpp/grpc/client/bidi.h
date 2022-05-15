#ifndef MINECPP_GRPC_CLIENT_BIDI_H
#define MINECPP_GRPC_CLIENT_BIDI_H
#include "../../util/pool.h"
#include "../bidi.h"
#include <algorithm>
#include <future>
#include <grpcpp/grpcpp.h>
#include <mb/result.h>

namespace minecpp::grpc::client {

template<typename TRead>
struct CompletionEvent
{
   EventType event_type;
   TRead *read_ptr;

   explicit CompletionEvent(EventType event_type, TRead *read_ptr = nullptr) :
       event_type(event_type), read_ptr(read_ptr)
   {}
};

static ::grpc::Status g_status{};

template<typename TWrite, typename TRead>
class Stream
{
   ::grpc::ClientAsyncReaderWriter<TWrite, TRead> &m_stream;
   util::AtomicPool<CompletionEvent<TRead>> &m_event_pool;
   util::AtomicPool<TRead> &m_read_pool;

 public:
   Stream(::grpc::ClientAsyncReaderWriter<TWrite, TRead> &client, util::AtomicPool<CompletionEvent<TRead>> &event_pool,
          util::AtomicPool<TRead> &read_pool) :
       m_stream(client),
       m_event_pool(event_pool), m_read_pool(read_pool)
   {}

   void write(const TWrite &message)
   {
      auto event = m_event_pool.construct(EventType::Write);
      m_stream.Write(message, event);
   }

   void read()
   {
      auto read_ptr = m_read_pool.construct();
      auto event    = m_event_pool.construct(EventType::Read, read_ptr);
      m_stream.Read(read_ptr, event);
   }

   void disconnect()
   {
      auto event = m_event_pool.construct(EventType::Disconnect);
      m_stream.Finish(&g_status, event);
   }
};

template<typename TStub, typename TWrite, typename TRead, typename TCallback, auto FStart>
class Connection
{
   TCallback &m_callback;
   ::grpc::CompletionQueue m_queue;
   ::grpc::ClientContext m_ctx;
   std::shared_ptr<::grpc::Channel> m_channel;
   TStub m_stub;
   std::mutex m_next_lock;
   std::unique_ptr<::grpc::ClientAsyncReaderWriter<TWrite, TRead>> m_stream;
   util::AtomicPool<CompletionEvent<TRead>> m_event_pool;
   util::AtomicPool<TRead> m_read_pool;
   std::vector<std::future<mb::result<mb::empty>>> m_workers;

 public:
   mb::result<mb::empty> worker_routine()
   {
      for (;;) {
         void *tag_ptr;
         bool queue_ok, data_ok;
         {
            std::lock_guard<std::mutex> lock(m_next_lock);
            queue_ok = m_queue.Next(&tag_ptr, &data_ok);
         }
         if (!queue_ok) {
            //shutdown
            return mb::ok;
         }
         if (!data_ok) {
            return mb::error("error reading message");
         }

         auto event = static_cast<CompletionEvent<TRead> *>(tag_ptr);

         switch (event->event_type) {
         case EventType::Accept: {
            m_callback.on_connected(Stream<TWrite, TRead>(*m_stream, m_event_pool, m_read_pool));
            m_event_pool.free(event);
            continue;
         }
         case EventType::Write: {
            m_callback.on_finish_write(Stream<TWrite, TRead>(*m_stream, m_event_pool, m_read_pool));
            m_event_pool.free(event);
            continue;
         }
         case EventType::Read: {
            m_callback.on_finish_read(Stream<TWrite, TRead>(*m_stream, m_event_pool, m_read_pool), *event->read_ptr);
            m_read_pool.free(event->read_ptr);
            m_event_pool.free(event);
            continue;
         }
         case EventType::Disconnect: {
            m_callback.on_disconnect(Stream<TWrite, TRead>(*m_stream, m_event_pool, m_read_pool));
            m_event_pool.free(event);
            m_queue.Shutdown();
            return mb::ok;
         }
         }

         return mb::error("unknown event type");
      }
   }

   Connection(const std::string &address, TCallback &callback, std::size_t worker_count) :
       m_callback(callback), m_channel(::grpc::CreateChannel(address, ::grpc::InsecureChannelCredentials())),
       m_stub(m_channel)
   {
      auto event = m_event_pool.construct(EventType::Accept);
      m_stream   = std::invoke(FStart, &m_stub, &m_ctx, &m_queue, event);
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
      auto err_it =
              std::find_if(results.begin(), results.end(), [](const mb::result<mb::empty> &res) { return !res.ok(); });
      if (err_it == results.end()) {
         return mb::ok;
      }
      return *err_it;
   }
};

}// namespace minecpp::grpc::client

#endif//MINECPP_GRPC_CLIENT_BIDI_H
