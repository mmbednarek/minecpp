#include "block/Foliage.h"

#include "minecpp/world/BlockState.h"

namespace minecpp::controller::block {

using game::BlockPosition;
using game::BlockStateId;
using game::Face;
using game::IWorld;
using world::BlockState;

bool Foliage::on_player_place_block(IWorld &world, game::PlayerId /*player_id*/, game::BlockId block_id,
                                    game::BlockPosition position, game::Face face,
                                    const math::Vector3f &/*crosshair_position*/)
{
   auto target_position = position.neighbour_at(face);
   auto base_position       = target_position.neighbour_at(Face::Bottom);

   auto base_block_state_id = world.block_at(base_position);
   if (base_block_state_id.has_failed())
      return false;

   BlockState base_block_state(*base_block_state_id);
   if (base_block_state.solid_faces() != minecpp::game::FaceMask::All)
      return false;

   world::BlockState state(block_id, 0);
   return world.set_block_at(target_position, state.block_state_id()).ok();
}

std::optional<BlockStateId> Foliage::on_neighbour_change(IWorld &world, BlockStateId /*block_state_id*/,
                                                         BlockStateId /*neighbour_block_state_id*/,
                                                         BlockPosition position, Face face)
{
   if (face == Face::Bottom)
      world.destroy_block(position);

   return std::nullopt;
}

}// namespace minecpp::controller::block
