#pragma once
#include "Default.h"

namespace minecpp::controller::block {

class Stairs : public Default  {
 public:
   bool on_player_place_block(game::World &world, game::PlayerId player_id, game::BlockId block_id,
                              game::BlockPosition position, game::Face face) override;
};

}
