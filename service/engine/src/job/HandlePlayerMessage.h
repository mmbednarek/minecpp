#pragma once

#include "../JobSystem.h"

#include "minecpp/proto/event/serverbound/Serverbound.pb.h"

namespace minecpp::service::engine {
class Service;
}

namespace minecpp::service::engine::job {

class HandlePlayerMessage : public IJob
{
 public:
   using Event = proto::event::serverbound::Event;

   HandlePlayerMessage(Service &service, Event event);

   void run() override;

 private:
   Service &m_service;
   Event m_event;
};

}// namespace minecpp::service::engine::job