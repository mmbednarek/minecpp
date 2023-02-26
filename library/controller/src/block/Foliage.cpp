#include <minecpp/controller/block/Foliage.h>

namespace minecpp::controller::block {

using game::BlockPosition;
using game::BlockStateId;
using game::Face;
using game::IWorld;

std::optional<BlockStateId> Foliage::on_neighbour_change(IWorld &world, BlockStateId block_state_id,
                                                         BlockStateId neighbour_block_state_id,
                                                         BlockPosition position, Face face)
{
   // destroy block if any block change, forward neighbour change
   world.destroy_block(position);
   return std::nullopt;
}

}// namespace minecpp::controller::block
