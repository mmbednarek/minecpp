#pragma once
#include "Default.h"

namespace minecpp::controller::block {

class TrapDoor : public Default
{
 public:
   bool on_player_place_block(game::IWorld &world, game::PlayerId player_id, game::BlockId block_id,
                              game::BlockPosition position, game::Face face,
                              const math::Vector3f &crosshair_position) override;

   bool on_player_action(game::IWorld &world, game::PlayerId player_id, game::BlockStateId block_state_id,
                         game::BlockPosition position, game::Face face,
                         const math::Vector3f &crosshair_position) override;
};

}// namespace minecpp::controller::block
