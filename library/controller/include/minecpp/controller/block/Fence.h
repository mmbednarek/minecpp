#pragma once
#include "Default.h"

namespace minecpp::controller::block {

class Fence : public Default
{
 public:
   bool on_player_place_block(game::IWorld &world, game::PlayerId player_id, int block_id,
                              game::BlockPosition position, game::Face face,
                              const math::Vector3f &crosshair_position) override;

   std::optional<game::BlockStateId> on_neighbour_change(game::IWorld &world,
                                                         game::BlockStateId block_state_id,
                                                         game::BlockStateId neighbour_block_state_id,
                                                         game::BlockPosition position,
                                                         game::Face face) override;
};

}// namespace minecpp::controller::block
