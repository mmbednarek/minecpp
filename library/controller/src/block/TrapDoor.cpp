#include <minecpp/controller/block/TrapDoor.h>
#include <minecpp/repository/Block.h>
#include <minecpp/world/BlockState.h>

using minecpp::world::BlockState;

namespace minecpp::controller::block {

bool TrapDoor::on_player_place_block(game::IWorld &world, game::PlayerId player_id, game::BlockId block_id,
                                     game::BlockPosition position, game::Face face,
                                     const math::Vector3f &crosshair_position)
{
   auto direction = Default::find_player_direction(world, player_id, position);
   if (not direction.has_value())
      return false;

   auto target_position = position.neighbour_at(face);

   const auto source_block_type = Default::get_source_block_type(world, target_position);
   if (not source_block_type.has_value())
      return false;

   auto placement = Default::deduce_half_placement(face, crosshair_position.y());

   BlockState block_state(block_id, 0);
   block_state.set("waterlogged", *source_block_type == SourceBlockType::Water);
   block_state.set("half", placement);
   block_state.set("facing", direction->opposite());
   block_state.set("open", false);
   block_state.set("powered", false);

   return world.set_block(target_position, block_state.block_state_id()).ok();
}

bool TrapDoor::on_player_action(game::IWorld &world, game::PlayerId /*player_id*/,
                                game::BlockStateId block_state_id, game::BlockPosition position,
                                game::Face /*face*/, const math::Vector3f & /*crosshair_position*/)
{
   BlockState block_state(block_state_id);
   block_state.set("open", not block_state.get<bool>("open").value_or(false));
   return world.set_block(position, block_state.block_state_id()).ok();
}

}// namespace minecpp::controller::block