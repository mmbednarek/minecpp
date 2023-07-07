#pragma once

#include "../EventHandler.h"
#include "../JobSystem.h"

namespace minecpp::service::engine::job {

class HandlePlayerMessage : public IJob
{
 public:
   using Event = proto::event::serverbound::Event;

   HandlePlayerMessage(EventHandler &event_handler, Event event);

   void run() override;

 private:
   EventHandler &m_event_handler;
   Event m_event;
};

}// namespace minecpp::service::engine::job