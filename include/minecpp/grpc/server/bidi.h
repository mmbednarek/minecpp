#ifndef MINECPP_GRPC_SERVER_BIDI_H
#define MINECPP_GRPC_SERVER_BIDI_H
#include "../../util/pool.h"
#include "../bidi.h"
#include <future>
#include <grpcpp/grpcpp.h>
#include <mb/result.h>

namespace minecpp::grpc::server {

template<typename TWrite, typename TRead, typename TTag>
struct CompletionEvent;

template<typename TWrite, typename TRead, typename TTag>
struct BidiClient
{
   ::grpc::ServerContext ctx;
   ::grpc::ServerAsyncReaderWriter<TWrite, TRead> stream;
   TTag tag{};

   BidiClient() :
       stream(&ctx)
   {
   }

   template<typename TPool>
   void write(TPool &pool, const TWrite &value)
   {
      auto event = pool.construct(EventType::Write, this);
      stream.Write(value, event);
   }

   template<typename TPool, typename TReadPool>
   void read(TPool &pool, TReadPool &read_pool)
   {
      auto msg   = read_pool.construct();
      auto event = pool.construct(EventType::Read, this, msg);
      stream.Read(msg, event);
   }

   template<typename TPool>
   void disconnect(TPool &pool)
   {
      auto event = pool.construct(EventType::Disconnect, this);
      ::grpc::Status status{};
      stream.Finish(status, event);
   }
};

template<typename TWrite, typename TRead, typename TTag>
struct CompletionEvent
{
   EventType tag;
   BidiClient<TWrite, TRead, TTag> *client;
   TRead *read_ptr;

   CompletionEvent(EventType tag, BidiClient<TWrite, TRead, TTag> *client, TRead *read_ptr = nullptr) :
       tag(tag),
       client(client),
       read_ptr(read_ptr)
   {
   }
};

template<typename TWrite, typename TRead, typename TTag>
class Stream
{
   BidiClient<TWrite, TRead, TTag> &m_client;
   util::AtomicPool<CompletionEvent<TWrite, TRead, TTag>> &m_event_pool;
   util::AtomicPool<TRead> &m_read_pool;

 public:
   Stream(BidiClient<TWrite, TRead, TTag> &client,
          util::AtomicPool<CompletionEvent<TWrite, TRead, TTag>> &event_pool,
          util::AtomicPool<TRead> &read_pool) :
       m_client(client),
       m_event_pool(event_pool),
       m_read_pool(read_pool)
   {
   }

   void write(const TWrite &message) { m_client.write(m_event_pool, message); }

   void read() { m_client.read(m_event_pool, m_read_pool); }

   void disconnect() { m_client.disconnect(m_event_pool); }

   [[nodiscard]] const TTag &tag() const { return m_client.tag; }

   void set_tag(const TTag &tag) { m_client.tag = tag; }
};

template<typename TService, typename TWrite, typename TRead, typename TCallback, typename TTag, auto FRequest>
class BidiServer
{
   TCallback &m_callback;
   TService m_service;
   std::unique_ptr<::grpc::CompletionQueue> m_queue;
   std::unique_ptr<::grpc::Server> m_server;
   std::vector<std::future<mb::result<mb::empty>>> m_workers;
   std::mutex m_next_lock;
   util::AtomicPool<BidiClient<TWrite, TRead, TTag>> m_client_pool;
   util::AtomicPool<CompletionEvent<TWrite, TRead, TTag>> m_event_pool;
   util::AtomicPool<TRead> m_read_pool;

 public:
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
            spdlog::info("shutting down the server");
            return mb::ok;
         }
         if (!data_ok) {
            return mb::error("cannot read message\n");
         }

         auto event = static_cast<CompletionEvent<TWrite, TRead, TTag> *>(tag_ptr);

         switch (event->tag) {
         case EventType::Accept: {
            m_callback.on_connected(Stream<TWrite, TRead, TTag>(*event->client, m_event_pool, m_read_pool));
            m_event_pool.free(event);
            accept();
            continue;
         }
         case EventType::Write: {
            m_callback.on_finish_write(
                    Stream<TWrite, TRead, TTag>(*event->client, m_event_pool, m_read_pool));
            m_event_pool.free(event);
            continue;
         }
         case EventType::Read: {
            m_callback.on_finish_read(Stream<TWrite, TRead, TTag>(*event->client, m_event_pool, m_read_pool),
                                      *event->read_ptr);
            m_read_pool.free(event->read_ptr);
            m_event_pool.free(event);
            continue;
         }
         case EventType::Disconnect: {
            m_callback.on_disconnect(Stream<TWrite, TRead, TTag>(*event->client, m_event_pool, m_read_pool));
            m_client_pool.free(event->client);
            m_event_pool.free(event);
            continue;
         }
         }

         return mb::error("invalid event type\n");
      }
   }

   explicit BidiServer(const std::string &bind_address, TCallback &callback, int worker_count) :
       m_callback(callback)
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
      m_server->Shutdown();
      m_queue->Shutdown();
      wait();
   }

   auto accept()
   {
      // TODO: Free the context
      auto client_ptr = m_client_pool.construct();
      auto event      = m_event_pool.construct(EventType::Accept, client_ptr);
      std::invoke(FRequest, &m_service, &(client_ptr->ctx), &(client_ptr->stream), m_queue.get(),
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
};

}// namespace minecpp::grpc::server

#endif//MINECPP_GRPC_SERVER_BIDI_H
