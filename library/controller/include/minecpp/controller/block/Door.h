#pragma once
#include "Default.h"

namespace minecpp::controller::block {

class Door : public Default
{
 public:
   bool on_player_place_block(game::World &world, game::PlayerId player_id, game::BlockId block_id,
                              game::BlockPosition position, game::Face face) override;

   std::optional<game::BlockStateId> on_neighbour_change(game::World &world,
                                                         game::BlockStateId block_state_id,
                                                         game::BlockStateId neighbour_block_state_id,
                                                         game::BlockPosition position,
                                                         game::Face face) override;

   game::Side find_side(game::World &world, game::BlockPosition upper, game::BlockPosition lower, game::Direction dir, game::BlockId door_id);
   bool check_side(game::World &world, game::BlockPosition pos, game::Direction dir, game::Side side, game::BlockId door_id);
   bool on_player_action(game::World &world, game::PlayerId player_id, game::BlockStateId block_state_id,
                         game::BlockPosition position, game::Face face,
                         util::Vec3 crosshair_position) override;
};

}// namespace minecpp::controller::block
