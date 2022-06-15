#ifndef MINECPP_BLOCK_CONTROLLER_HPP
#define MINECPP_BLOCK_CONTROLLER_HPP
#include <minecpp/game/World.h>
#include <minecpp/player/Id.h>

namespace minecpp::game::controller {

class BlockController
{
 public:
   virtual ~BlockController() noexcept = default;

   virtual bool on_player_place_block(World &world, player::Id player_id, int block_id,
                                      BlockPosition position, Face face) = 0;
};

}// namespace minecpp::game::controller

#endif//MINECPP_BLOCK_CONTROLLER_HPP
