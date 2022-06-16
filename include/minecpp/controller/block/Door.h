#pragma once
#include "Default.h"

namespace minecpp::controller::block {

class Door : public Default  {
 public:
   bool on_player_place_block(game::World &world, player::Id player_id, game::BlockId block_id,
                              game::BlockPosition position, game::Face face) override;
};

}
