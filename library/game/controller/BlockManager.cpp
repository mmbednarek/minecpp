#include <minecpp/game/controller/BlockManager.h>
#include <minecpp/repository/State.h>

namespace minecpp::game::controller {

bool controller::BlockManager::on_player_place_block(World &world, player::Id player_id, int block_id,
                                                     BlockPosition position, Face face)
{
   return controller(block_id).on_player_place_block(world, player_id, block_id, position, face);
}

BlockController &BlockManager::controller(int block_id)
{
   auto controller    = m_controllers.find(block_id);
   if (controller == m_controllers.end()) {
      return m_default_controller;
   }
   return *(controller->second);
}

}// namespace minecpp::game::controller