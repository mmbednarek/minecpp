#pragma once
#include "event_manager.h"
#include <minecpp/proto/service/engine/v1/engine.grpc.pb.h>

namespace minecpp::service::engine {

class EventHandler;

class ApiImpl final : public proto::service::engine::v1::EngineService::AsyncService {
   using Stream = grpc::ServerReaderWriter<minecpp::proto::event::clientbound::v1::Event, minecpp::proto::event::serverbound::v1::Event>;

   struct Client {
      Stream &stream;
      EventManager::Queue &queue;

      Client(Stream &stream, EventManager &event_manager) : stream(stream),
                                                            queue(event_manager.create_queue("front")) {}
   };

   bool m_running = true;
   EventHandler &m_event_handler;
   EventManager &m_event_manager;
   std::vector<std::unique_ptr<Client>> m_queues;
   std::mutex m_queues_mutex;

 public:
   ApiImpl(EventHandler &event_handler, EventManager &event_manager);

   grpc::Status Join(grpc::ServerContext *context, Stream *stream) override;


   void write_routine(grpc::CompletionQueue &cq);
   void stop();
};

}// namespace minecpp::service::engine