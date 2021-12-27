#pragma once
#include "notifier.h"
#include <mb/result.h>
#include <minecpp/game/game.h>
#include <minecpp/player/id.h>

namespace minecpp::game {

class World {
 public:
   virtual Notifier &notifier() = 0;
   virtual mb::result<mb::empty> add_refs(player::Id player, std::vector<game::ChunkPosition> refs) = 0;
   virtual mb::result<mb::empty> free_refs(player::Id player, std::vector<game::ChunkPosition> refs) = 0;
   virtual mb::result<int> height_at(int x, int z) = 0;
   virtual mb::result<mb::empty> set_block(const game::BlockPosition &pos, game::BlockState state) = 0;
};

}// namespace minecpp::game
