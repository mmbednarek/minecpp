#ifndef MINECPP_EVENT_HANDLER_H
#define MINECPP_EVENT_HANDLER_H
#include <minecpp/command/CommandManager.h>
#include <minecpp/command/RuntimeContext.h>
#include <minecpp/command/StandardStream.h>
#include <minecpp/controller/BlockManager.h>
#include <minecpp/game/player/Player.h>
#include <minecpp/proto/event/serverbound/v1/Serverbound.pb.h>

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
   command::StandardStream m_command_std_stream;
   command::CommandManager m_command_manager;
   command::RuntimeContext m_command_context;
   controller::BlockManager &m_block_manager;

 public:
   EventHandler(Dispatcher &dispatcher, PlayerManager &player_manager, EntityManager &entity_manager,
                game::World &world, controller::BlockManager &block_manager);

   void handle_accept_player(const serverbound_v1::AcceptPlayer &event, game::PlayerId player_id);
   void handle_set_player_position(const serverbound_v1::SetPlayerPosition &event, game::PlayerId player_id);
   void handle_set_player_rotation(const serverbound_v1::SetPlayerRotation &event, game::PlayerId player_id);
   void handle_chat_message(const serverbound_v1::ChatMessage &event, game::PlayerId player_id);
   void handle_remove_player(const serverbound_v1::RemovePlayer &event, game::PlayerId player_id);
   void handle_player_digging(const serverbound_v1::PlayerDigging &event, game::PlayerId player_id);
   void handle_update_ping(const serverbound_v1::UpdatePing &event, game::PlayerId player_id);
   void handle_animate_hand(const serverbound_v1::AnimateHand &event, game::PlayerId player_id);
   void handle_load_initial_chunks(const serverbound_v1::LoadInitialChunks &event, game::PlayerId player_id);
   void handle_block_placement(const serverbound_v1::BlockPlacement &event, game::PlayerId player_id);
   void handle_change_inventory_item(const serverbound_v1::ChangeInventoryItem &event, game::PlayerId player_id);
   void handle_change_held_item(const serverbound_v1::ChangeHeldItem &event, game::PlayerId player_id);
   void handle_issue_command(const serverbound_v1::IssueCommand &event, game::PlayerId player_id);

 private:
   void send_inventory_data(const game::player::Player &player);
};

}// namespace minecpp::service::engine

#endif//MINECPP_EVENT_HANDLER_H