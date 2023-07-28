#pragma once

#include "minecpp/game/player/Id.h"
#include "minecpp/net/play/Serverbound.schema.h"
#include "minecpp/proto/chunk/Chunk.pb.h"

namespace minecpp::service::engine {

class EventHandler;

class Service
{
 public:
   explicit Service(EventHandler &handler);

   void handle_raw_message(game::PlayerId player_id, container::BufferView data);

   void send(const ::google::protobuf::Message &message, game::PlayerId id);

   void on_confirm_teleport(game::PlayerId player_id, const net::play::sb::ConfirmTeleport &msg);
   void on_chat_command(game::PlayerId player_id, const net::play::sb::ChatCommand &msg);
   void on_chat_message(game::PlayerId player_id, const net::play::sb::ChatMessage &msg);
   void on_client_settings(game::PlayerId player_id, const net::play::sb::ClientSettings &msg);
   void on_interact(game::PlayerId player_id, const net::play::sb::Interact &msg);
   void on_set_player_position(game::PlayerId player_id, const net::play::sb::SetPlayerPosition &msg);
   void on_set_player_position_and_rotation(game::PlayerId player_id, const net::play::sb::SetPlayerPositionAndRotation &msg);
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
   EventHandler &m_event_handler;
};

}// namespace minecpp::service::front
