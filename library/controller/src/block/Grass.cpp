#include <minecpp/controller/block/Grass.h>
#include <minecpp/repository/Block.h>
#include <minecpp/world/BlockState.h>

namespace minecpp::controller::block {

bool Grass::on_player_place_block(game::IWorld &world, game::PlayerId /*player_id*/, int block_id,
                                  game::BlockPosition position, game::Face face,
                                  const math::Vector3f & /*crosshair_position*/)
{
   auto neighbour_position = position.neighbour_at(face);
   world::BlockState state(block_id, 0);
   state.set("snowy", false);

   return world.set_block(neighbour_position, state.block_state_id()).ok();
}

}// namespace minecpp::controller::block
