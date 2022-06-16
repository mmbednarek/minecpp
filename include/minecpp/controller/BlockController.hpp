#ifndef MINECPP_BLOCK_CONTROLLER_HPP
#define MINECPP_BLOCK_CONTROLLER_HPP
#include <minecpp/game/World.h>

namespace minecpp::controller {

class BlockController
{
 public:
   virtual ~BlockController() noexcept = default;

   virtual bool on_player_place_block(game::World &world, game::PlayerId player_id, game::BlockId block_id,
                                      game::BlockPosition position, game::Face face) = 0;

   virtual std::optional<game::BlockStateId> on_neighbour_change(game::World &world,
                                                                 game::BlockStateId block_state_id,
                                                                 game::BlockStateId neighbour_block_state_id,
                                                                 game::BlockPosition position,
                                                                 game::Face face) = 0;
};

}// namespace minecpp::controller

#endif//MINECPP_BLOCK_CONTROLLER_HPP
