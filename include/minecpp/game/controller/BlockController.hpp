#ifndef MINECPP_BLOCK_CONTROLLER_HPP
#define MINECPP_BLOCK_CONTROLLER_HPP
#include <minecpp/game/World.h>

namespace minecpp::game::controller {

class BlockController {
 public:
   virtual ~BlockController() noexcept = default;

   virtual bool on_player_place_block(World &world, item::ItemId itemId, BlockPosition position, Face face) = 0;
};

}

#endif//MINECPP_BLOCK_CONTROLLER_HPP
