#include <minecpp/controller/BlockManager.h>
#include <minecpp/repository/State.h>

namespace minecpp::controller {

bool controller::BlockManager::on_player_place_block(game::IWorld &world, game::PlayerId player_id,
                                                     game::BlockId block_id, game::BlockPosition position,
                                                     game::Face face)
{
   return controller(block_id).on_player_place_block(world, player_id, block_id, position, face);
}

std::optional<game::BlockStateId> BlockManager::on_neighbour_change(game::IWorld &world,
                                                                    unsigned int block_state_id,
                                                                    unsigned int neighbour_block_state_id,
                                                                    game::BlockPosition position,
                                                                    game::Face face)
{
   auto [block_id, block_state] = repository::StateManager::the().parse_block_id(block_state_id);
   return controller(block_id).on_neighbour_change(world, block_state_id, neighbour_block_state_id, position,
                                                   face);
}

bool BlockManager::on_player_action(game::IWorld &world, game::PlayerId player_id,
                                    game::BlockStateId block_state_id, game::BlockPosition position,
                                    game::Face face, math::Vector3 crosshair_position)
{
   auto [block_id, block_state] = repository::StateManager::the().parse_block_id(block_state_id);
   return controller(block_id).on_player_action(world, player_id, block_state_id, position, face,
                                                crosshair_position);
}

game::IBlockController &BlockManager::controller(game::BlockId block_id)
{
   auto controller = m_controllers.find(block_id);
   if (controller == m_controllers.end()) {
      return m_default_controller;
   }
   return *(controller->second);
}

}// namespace minecpp::controller