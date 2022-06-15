#ifndef MINECPP_DEFAULTCONTROLLER_H
#define MINECPP_DEFAULTCONTROLLER_H
#include <minecpp/game/controller/BlockController.hpp>

namespace minecpp::game::controller::block {

class Default : public BlockController {
 public:
   bool on_player_place_block(World &world, player::Id player_id, int block_id, BlockPosition position,
                              Face face) override;
};

}

#endif//MINECPP_DEFAULTCONTROLLER_H
