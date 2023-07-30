#include "HandlePlayerMessage.h"

#include "../Service.h"

#include "minecpp/proto/event/serverbound/Serverbound.pb.h"

#include <spdlog/spdlog.h>

namespace minecpp::service::engine::job {

HandlePlayerMessage::HandlePlayerMessage(Service &service, HandlePlayerMessage::Event event) :
    m_service{service},
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
      } else if (m_event.payload().Is<proto::event::serverbound::AcceptPlayer>()) {
         proto::event::serverbound::AcceptPlayer accept_player;
         m_event.payload().UnpackTo(&accept_player);
         m_service.on_accept_player(game::player::read_id_from_proto(m_event.player_id()),
                                    accept_player.name());
      } else if (m_event.payload().Is<proto::event::serverbound::PreInitialChunks>()) {
         m_service.on_pre_initial_chunks(game::player::read_id_from_proto(m_event.player_id()));
      } else if (m_event.payload().Is<proto::event::serverbound::PostInitialChunks>()) {
         m_service.on_post_initial_chunks(game::player::read_id_from_proto(m_event.player_id()));
      } else if (m_event.payload().Is<proto::event::serverbound::RemovePlayer>()) {
         m_service.on_remove_player(game::player::read_id_from_proto(m_event.player_id()));
      } else {
         spdlog::error("unknown message: {}", m_event.payload().type_url());
      }
   } catch (std::runtime_error &err) {
      spdlog::error("error while handling request: {}", err.what());
   }
}

}// namespace minecpp::service::engine::job
