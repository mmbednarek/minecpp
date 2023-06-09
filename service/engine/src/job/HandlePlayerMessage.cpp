#include "HandlePlayerMessage.h"

#include "minecpp/event/Serverbound.h"

#include <spdlog/spdlog.h>

namespace minecpp::service::engine::job {

HandlePlayerMessage::HandlePlayerMessage(EventHandler &event_handler, HandlePlayerMessage::Event event) :
    m_event_handler{event_handler},
    m_event{std::move(event)}
{
}

void HandlePlayerMessage::run()
{
   try {
      event::visit_serverbound(m_event, m_event_handler);
   } catch (std::runtime_error &err) {
      spdlog::error("error while handling request: {}", err.what());
   }
}

}// namespace minecpp::service::engine::job
