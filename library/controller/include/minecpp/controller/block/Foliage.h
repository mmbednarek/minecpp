#pragma once

#include "Default.h"

namespace minecpp::controller::block {

class Foliage : public Default {
 public:
   std::optional<game::BlockStateId> on_neighbour_change(game::IWorld &world,
                                                         game::BlockStateId block_state_id,
                                                         game::BlockStateId neighbour_block_state_id,
                                                         game::BlockPosition position,
                                                         game::Face face) override;
};

}