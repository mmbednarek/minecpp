#pragma once

#include "World.h"
#include <minecpp/math/Vector3.h>

namespace minecpp::game {

class IBlockController
{
 public:
   virtual ~IBlockController() noexcept = default;

   virtual bool on_player_place_block(World &world, PlayerId player_id, BlockId block_id,
                                      BlockPosition position, Face face) = 0;

   virtual std::optional<BlockStateId> on_neighbour_change(World &world, BlockStateId block_state_id,
                                                           BlockStateId neighbour_block_state_id,
                                                           BlockPosition position, Face face) = 0;

   /**
    *
    * @param world
    * @param player_id
    * @param block_state_id
    * @param position
    * @return supress block placement
    */
   virtual bool on_player_action(World &world, PlayerId player_id, BlockStateId block_state_id,
                                 BlockPosition position, Face face, math::Vector3 crosshair_position) = 0;
};

}// namespace minecpp::game
