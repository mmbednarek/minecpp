#pragma once
#include "Default.h"

namespace minecpp::controller::block {

class Door : public Default  {
 public:
   bool on_player_place_block(game::World &world, game::PlayerId player_id, game::BlockId block_id,
                              game::BlockPosition position, game::Face face) override;

   std::optional<game::BlockStateId> on_neighbour_change(game::World &world,
                                                         game::BlockStateId block_state_id,
                                                         game::BlockStateId neighbour_block_state_id,
                                                         game::BlockPosition position,
                                                         game::Face face) override;
};

}
