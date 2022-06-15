#pragma once
#include "Notifier.h"
#include <mb/result.h>
#include <minecpp/game/Game.h>
#include <minecpp/player/Id.h>

namespace minecpp::game {

class World
{
 public:
   virtual Notifier &notifier()                                                                      = 0;
   virtual mb::result<mb::empty> add_refs(player::Id player, std::vector<game::ChunkPosition> refs)  = 0;
   virtual mb::result<mb::empty> free_refs(player::Id player, std::vector<game::ChunkPosition> refs) = 0;
   virtual mb::result<int> height_at(int x, int z)                                                   = 0;
   virtual mb::result<mb::empty> set_block(const game::BlockPosition &pos, game::BlockState state)   = 0;
   virtual mb::result<game::BlockState> get_block(const game::BlockPosition &pos)                    = 0;
};

}// namespace minecpp::game
