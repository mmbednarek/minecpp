#pragma once

#include "minecpp/controller/BlockManager.h"
#include "minecpp/controller/RootItem.h"
#include "minecpp/game/BlockPosition.h"
#include "minecpp/game/Game.h"
#include "minecpp/game/Types.hpp"
#include "minecpp/math/Rotation.h"
#include "minecpp/math/Vector3.h"

namespace minecpp::service::engine {
class World;
class Dispatcher;
}// namespace minecpp::service::engine

namespace minecpp::service::engine::service {

class PlayerInteraction
{
 public:
   PlayerInteraction(World &world, Dispatcher &dispatcher, controller::BlockManager &block_manager,
                     controller::RootItem &root_item_controller);

   void handle_start_digging(game::PlayerId player_id, int sequence_id, const game::BlockPosition &position);
   void handle_cancel_digging(game::PlayerId player_id, int sequence_id, const game::BlockPosition &position);
   void handle_finish_digging(game::PlayerId player_id, int sequence_id, const game::BlockPosition &position);
   void handle_drop_active_item(game::PlayerId player_id, bool is_whole_stack);
   void handle_use_item_on(game::PlayerId player_id, int sequence_id, game::Face face,
                           const game::BlockPosition &block_position, const math::Vector3f &cursor_position);
   void handle_interact(game::PlayerId player_id, game::EntityId entity_id,
                        game::InteractionType interaction_type, math::Vector3f position, bool is_off_hand);
   void handle_use_item(game::PlayerId player_id, int sequence_id, bool is_off_hand);
   void handle_animate_hand(game::PlayerId player_id, game::EntityAnimation hand_animation);

   void handle_release_used_item(game::PlayerId player_id);

   void handle_swap_held_items(game::PlayerId player_id);

 private:
   World &m_world;
   Dispatcher &m_dispatcher;
   controller::BlockManager &m_block_manager;
   controller::RootItem &m_root_item_controller;
};

}// namespace minecpp::service::engine::service
