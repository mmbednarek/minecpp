#include "HandlePlayerMessage.h"

#include "../EventHandler.h"
#include "../Service.h"

#include "minecpp/event/Serverbound.h"
#include "minecpp/proto/event/serverbound/Serverbound.pb.h"

#include <spdlog/spdlog.h>

namespace minecpp::service::engine::job {

HandlePlayerMessage::HandlePlayerMessage(Service &service, EventHandler &event_handler,
                                         HandlePlayerMessage::Event event) :
    m_service{service},
    m_event_handler{event_handler},
    m_event{std::move(event)}
{
}

void HandlePlayerMessage::run()
{
   try {
      if (m_event.payload().Is<proto::event::serverbound::RawMessage>()) {
         proto::event::serverbound::RawMessage raw_message;
         m_event.payload().UnpackTo(&raw_message);
         m_service.handle_raw_message(
                 game::player::read_id_from_proto(m_event.player_id()),
                 container::BufferView(reinterpret_cast<unsigned char *>(raw_message.mutable_data()->data()),
                                       raw_message.data().size()));
      } else {
         event::visit_serverbound(m_event, m_event_handler);
      }
   } catch (std::runtime_error &err) {
      spdlog::error("error while handling request: {}", err.what());
   }
}

}// namespace minecpp::service::engine::job
