#include "event_handler.h"
#include "dispatcher.h"
#include "entities.h"
#include "players.h"
#include <minecpp/chat/chat.h>
#include <minecpp/game/world.h>

namespace minecpp::service::engine {

EventHandler::EventHandler(Dispatcher &dispatcher, PlayerManager &player_manager, EntityManager &entity_manager, game::World &world) : m_dispatcher(dispatcher),
                                                                                                                                       m_player_manager(player_manager),
                                                                                                                                       m_entity_manager(entity_manager),
                                                                                                                                       m_world(world) {}

void EventHandler::handle_accept_player(const serverbound_v1::AcceptPlayer &event, player::Id player_id) {
      spdlog::info("player accept request from {}", event.name());
      auto join_result = m_player_manager.join_player(m_world, event.name(), player_id);
      if (!join_result.ok()) {
         m_dispatcher.deny_player(player_id, join_result.msg());
         return;
      }

      auto &player = MB_ESCAPE(m_player_manager.get_player(player_id));// We can assume no problems here
      auto &entity = MB_ESCAPE(m_player_manager.get_entity(player_id));

      m_dispatcher.accept_player(player, entity);
      m_dispatcher.player_list(player.id(), m_player_manager.player_status_list());
      m_dispatcher.entity_list(player.id(), m_entity_manager.entities());
      m_dispatcher.add_player(player.id(), player.name(), player.ping());
      m_dispatcher.spawn_player(player.id(), player.entity_id(), entity.get_pos(), entity::Rotation(entity.get_yaw(), entity.get_pitch()));
      m_dispatcher.send_chat(chat::MessageType::SystemMessage, chat::format_join_message(player.name()));
}

void EventHandler::handle_set_player_position(const serverbound_v1::SetPlayerPosition &event, player::Id player_id) {
   auto &entity = MB_ESCAPE(m_player_manager.get_entity(player_id));
   auto player_position = entity::read_entity_position(event.position());
   entity.set_pos(m_dispatcher, player_position);
   MB_ESCAPE(m_player_manager.get_player(player_id)).on_movement(m_world, player_position);
}

void EventHandler::handle_set_player_rotation(const serverbound_v1::SetPlayerRotation &event, player::Id player_id) {
   auto &entity = MB_ESCAPE(m_player_manager.get_entity(player_id));
   entity.set_rot(event.rotation().yaw(), event.rotation().pitch());
   m_dispatcher.entity_look(player_id, entity.get_id(), entity::Rotation(entity.get_yaw(), entity.get_pitch()));
}

void EventHandler::handle_chat_message(const serverbound_v1::ChatMessage &event, player::Id player_id) {
   try {
      if (event.message().empty())
         return;

      if (event.message()[0] == '/') {
         // TODO: Handle commands
         return;
      }

      auto &player = MB_ESCAPE(m_player_manager.get_player(player_id));

      spdlog::info("CHAT [{}] {}", player.name(), event.message());
      m_dispatcher.send_chat(chat::MessageType::PlayerMessage, chat::format_chat_message(player.name(), event.message()));
   } catch (std::runtime_error &err) {
      spdlog::error("handle chat message: {}", err.what());
   }
}

void EventHandler::handle_remove_player(const serverbound_v1::RemovePlayer &event, player::Id player_id) {
   auto &player = MB_ESCAPE(m_player_manager.get_player(player_id));
   m_dispatcher.send_chat(chat::MessageType::SystemMessage, chat::format_left_message(player.name()));
   m_dispatcher.remove_player(player_id, player.entity_id());
   m_player_manager.remove_player(player_id);
}

void EventHandler::handle_destroy_block(const serverbound_v1::DestroyBlock &event, player::Id player_id) {
   auto block_position = game::BlockPosition::from_proto(event.block_position());
   m_dispatcher.update_block(block_position, 0);
   m_world.set_block(block_position, 0);
}

void EventHandler::handle_update_ping(const serverbound_v1::UpdatePing &event, player::Id player_id) {
   auto &player = MB_ESCAPE(m_player_manager.get_player(player_id));
   player.set_ping(event.ping());
}

void EventHandler::handle_animate_hand(const serverbound_v1::AnimateHand &event, player::Id player_id) {
   auto &player = MB_ESCAPE(m_player_manager.get_player(player_id));
   m_dispatcher.animate_hand(player_id, player.entity_id(), event.hand());
}

void EventHandler::handle_load_initial_chunks(const serverbound_v1::LoadInitialChunks &event, player::Id player_id) {
   auto &player = MB_ESCAPE(m_player_manager.get_player(player_id));
   auto res = player.load_chunks(m_world);
   if (!res.ok()) {
      spdlog::error("error loading chunks: {}", res.msg());
   }
}

}// namespace minecpp::service::engine
