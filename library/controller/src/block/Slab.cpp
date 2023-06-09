#include "minecpp/repository/Block.h"
#include <minecpp/controller/block/Slab.h>
#include <minecpp/game/property/SlabType.h>
#include <minecpp/world/BlockState.h>

using minecpp::game::Face;
using minecpp::game::SlabType;

namespace minecpp::controller::block {

bool Slab::on_player_place_block(game::IWorld &world, game::PlayerId /*player_id*/, int block_id,
                                 game::BlockPosition position, Face face,
                                 const math::Vector3f &crosshair_position)
{
   auto block_state_id = world.block_at(position);
   if (block_state_id.has_failed())
      return false;

   if (face == Face::Top || face == Face::Bottom) {
      world::BlockState state(*block_state_id);
      if (state.block_id() == block_id && state.get<game::SlabType>("type") != game::SlabType::Double) {
         state.set<game::SlabType>("type", game::SlabType::Double);
         return world.set_block_at(position, state.block_state_id()).ok();
      }
   }

   auto neighbour_position   = position.neighbour_at(face);
   auto neighbour_block_type = Default::get_source_block_type(world, neighbour_position);

   world::BlockState new_state(block_id, 0);
   new_state.set<game::SlabType>(
           "type", game::SlabType::from_half_placement(deduce_half_placement(face, crosshair_position.y())));
   new_state.set("waterlogged", neighbour_block_type == SourceBlockType::Water);
   return world.set_block_at(neighbour_position, new_state.block_state_id()).ok();
}

}// namespace minecpp::controller::block
