#pragma once

#include "minecpp/command/CommandManager.h"
#include "minecpp/command/RuntimeContext.h"
#include "minecpp/command/StandardStream.h"
#include "minecpp/game/BlockPosition.h"
#include "minecpp/game/Game.h"
#include "minecpp/game/Types.hpp"
#include "minecpp/math/Rotation.h"
#include "minecpp/math/Vector3.h"

namespace minecpp::service::engine {
class PlayerManager;
class World;
class Dispatcher;
}// namespace minecpp::service::engine

namespace minecpp::service::engine::service {

class PlayerInterface
{
 public:
   PlayerInterface(PlayerManager &player_manager, World &world, Dispatcher &dispatcher);

   void handle_change_inventory_item(game::PlayerId player_id, game::SlotId slot_id,
                                     const game::ItemSlot &item_slot);
   void handle_change_held_item(game::PlayerId player_id, int active_slot_id);
   void handle_drop_carried_item(game::PlayerId player_id, bool is_whole_stack);
   void handle_set_carried_item(game::PlayerId player_id, const game::ItemSlot &item_slot);
   void handle_chat_message(game::PlayerId player_id, std::string_view message);
   void handle_issue_command(game::PlayerId player_id, std::string_view command);

 private:
   PlayerManager &m_player_manager;
   World &m_world;
   Dispatcher &m_dispatcher;
   command::StandardStream m_command_std_stream;
   command::CommandManager m_command_manager;
   command::RuntimeContext m_command_context;
};

}// namespace minecpp::service::engine::service
