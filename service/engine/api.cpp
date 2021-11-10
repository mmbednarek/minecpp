#include "api.h"
#include "event_handler.h"
#include <minecpp/event/serverbound.h>
#include <spdlog/spdlog.h>

namespace minecpp::service::engine {

ApiImpl::ApiImpl(EventHandler &event_handler, EventManager &event_manager) : m_event_handler(event_handler),
                                                                             m_event_manager(event_manager) {}

grpc::Status ApiImpl::Join(grpc::ServerContext *context, Stream *stream) {
   m_queues_mutex.lock();
   m_queues.push_back(std::make_unique<Client>(*stream, m_event_manager));
   m_queues_mutex.unlock();

   spdlog::info("front connection");

   while (m_running) {
      proto::event::serverbound::v1::Event proto_event;
      stream->Read(&proto_event);
      event::visit_serverbound(proto_event, m_event_handler);
   }
   return grpc::Status();
}

void ApiImpl::write_routine(grpc::CompletionQueue &cq) {
   while (m_running) {
      std::lock_guard<std::mutex> lg(m_queues_mutex);
      for (auto &queue : m_queues) {
         if (queue->queue.empty())
            continue;

         auto event = queue->queue.pop();
         spdlog::info("sending event: {}", event.payload().type_url());
         queue->stream.Write(event);
      }
   }
}

void ApiImpl::stop() {
   m_running = false;
}

}// namespace minecpp::service::engine