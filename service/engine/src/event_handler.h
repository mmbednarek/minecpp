#ifndef MINECPP_EVENT_HANDLER_H
#define MINECPP_EVENT_HANDLER_H
#include "minecpp/command/standard_stream.h"
#include <minecpp/command/command_manager.h>
#include <minecpp/command/runtime_context.h>
#include <minecpp/player/player.h>
#include <minecpp/proto/event/serverbound/v1/serverbound.pb.h>

namespace minecpp::game {
class World;
}

namespace minecpp::service::engine {

namespace serverbound_v1 = proto::event::serverbound::v1;

class Dispatcher;
class PlayerManager;
class EntityManager;

class EventHandler
{
   Dispatcher &m_dispatcher;
   PlayerManager &m_player_manager;
   EntityManager &m_entity_manager;
   game::World &m_world;
   game::BlockState m_selected_block = 1;
   command::StandardStream m_command_std_stream;
   command::CommandManager m_command_manager;
   command::RuntimeContext m_command_context;

 public:
   EventHandler(Dispatcher &dispatcher, PlayerManager &player_manager, EntityManager &entity_manager,
                game::World &world);

   void handle_accept_player(const serverbound_v1::AcceptPlayer &event, player::Id player_id);
   void handle_set_player_position(const serverbound_v1::SetPlayerPosition &event, player::Id player_id);
   void handle_set_player_rotation(const serverbound_v1::SetPlayerRotation &event, player::Id player_id);
   void handle_chat_message(const serverbound_v1::ChatMessage &event, player::Id player_id);
   void handle_remove_player(const serverbound_v1::RemovePlayer &event, player::Id player_id);
   void handle_player_digging(const serverbound_v1::PlayerDigging &event, player::Id player_id);
   void handle_update_ping(const serverbound_v1::UpdatePing &event, player::Id player_id);
   void handle_animate_hand(const serverbound_v1::AnimateHand &event, player::Id player_id);
   void handle_load_initial_chunks(const serverbound_v1::LoadInitialChunks &event, player::Id player_id);
   void handle_block_placement(const serverbound_v1::BlockPlacement &event, player::Id player_id);
   void handle_change_inventory_item(const serverbound_v1::ChangeInventoryItem &event, player::Id player_id);
   void handle_change_held_item(const serverbound_v1::ChangeHeldItem &event, player::Id player_id);
   void handle_issue_command(const serverbound_v1::IssueCommand &event, player::Id player_id);

 private:
   void send_inventory_data(const player::Player &player);
};

}// namespace minecpp::service::engine

#endif//MINECPP_EVENT_HANDLER_H
