#pragma once

#include "minecpp/game/player/Id.h"
#include "minecpp/net/play/Serverbound.schema.h"
#include "minecpp/proto/chunk/Chunk.pb.h"

namespace minecpp::service::engine {

namespace service {
class PlayerInteraction;
class PlayerInterface;
class PlayerMovement;
class PlayerSession;
}// namespace service

class Service
{
 public:
   Service(service::PlayerInteraction &interaction_service, service::PlayerInterface &interface_service,
           service::PlayerMovement &movement_service, service::PlayerSession &session_service);

   void handle_raw_message(game::PlayerId player_id, container::BufferView data);

   void on_accept_player(game::PlayerId player_id, std::string_view name);
   void on_remove_player(game::PlayerId player_id);
   void on_pre_initial_chunks(game::PlayerId player_id);
   void on_post_initial_chunks(game::PlayerId player_id);

   void on_confirm_teleport(game::PlayerId player_id, const net::play::sb::ConfirmTeleport &msg);
   void on_chat_command(game::PlayerId player_id, const net::play::sb::ChatCommand &msg);
   void on_chat_message(game::PlayerId player_id, const net::play::sb::ChatMessage &msg);
   void on_client_settings(game::PlayerId player_id, const net::play::sb::ClientSettings &msg);
   void on_interact(game::PlayerId player_id, const net::play::sb::Interact &msg);
   void on_set_player_position(game::PlayerId player_id, const net::play::sb::SetPlayerPosition &msg);
   void on_set_player_position_and_rotation(game::PlayerId player_id,
                                            const net::play::sb::SetPlayerPositionAndRotation &msg);
   void on_set_player_rotation(game::PlayerId player_id, const net::play::sb::SetPlayerRotation &msg);
   void on_set_is_player_on_ground(game::PlayerId player_id, const net::play::sb::SetIsPlayerOnGround &msg);
   void on_player_command(game::PlayerId player_id, const net::play::sb::PlayerCommand &msg);
   void on_player_digging(game::PlayerId player_id, const net::play::sb::PlayerDigging &msg);
   void on_keep_alive(game::PlayerId player_id, const net::play::sb::KeepAlive &msg);
   void on_animate_hand(game::PlayerId player_id, const net::play::sb::AnimateHand &msg);
   void on_use_item_on(game::PlayerId player_id, const net::play::sb::UseItemOn &msg);
   void on_click_window(game::PlayerId player_id, const net::play::sb::ClickWindow &msg);
   void on_close_window(game::PlayerId player_id, const net::play::sb::CloseWindow &msg);
   void on_set_held_item(game::PlayerId player_id, const net::play::sb::SetHeldItem &msg);
   void on_plugin_message(game::PlayerId player_id, const net::play::sb::PluginMessage &msg);
   void on_use_item(game::PlayerId player_id, const net::play::sb::UseItem &msg);
   void on_client_command(game::PlayerId player_id, const net::play::sb::ClientCommand &msg);

   static void on_failure(game::PlayerId player_id, std::uint8_t message_id);

 private:
   service::PlayerInteraction &m_interaction_service;
   service::PlayerInterface &m_interface_service;
   service::PlayerMovement &m_movement_service;
   service::PlayerSession &m_session_service;
};

}// namespace minecpp::service::engine
