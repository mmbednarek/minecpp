#include <minecpp/controller/block/Stairs.h>
#include <minecpp/repository/Block.h>
#include <minecpp/world/BlockState.h>

using minecpp::world::BlockState;

namespace minecpp::controller::block {

bool Stairs::on_player_place_block(game::IWorld &world, game::PlayerId player_id, game::BlockId block_id,
                                   game::BlockPosition position, game::Face face,
                                   const math::Vector3f &crosshair_position)
{
   auto target_position = position.neighbour_at(face);

   const auto source_block_type = Default::get_source_block_type(world, target_position);
   if (not source_block_type.has_value())
      return false;

   const auto player_direction = Default::find_player_direction(world, player_id, target_position);
   if (not player_direction.has_value())
      return false;

   auto placement = Default::deduce_half_placement(face, crosshair_position.y());

   BlockState state(block_id, 0);
   state.set("half", placement);
   state.set("facing", *player_direction);
   state.set("waterlogged", *source_block_type == SourceBlockType::Water);

   return world.set_block_at(target_position, state.block_state_id()).ok();
}

}// namespace minecpp::controller::block
