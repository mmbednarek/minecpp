#pragma once
#include "EntityManager.hpp"
#include "Game.h"
#include "Notifier.h"
#include <mb/result.h>
#include <minecpp/game/player/Provider.hpp>

namespace minecpp::game {

class World
{
 public:
   virtual Notifier &notifier()                                                                      = 0;
   virtual EntityManager &entities()                                                                 = 0;
   virtual player::Provider &players()                                                               = 0;
   virtual mb::result<mb::empty> add_refs(PlayerId player, std::vector<game::ChunkPosition> refs)  = 0;
   virtual mb::result<mb::empty> free_refs(PlayerId player, std::vector<game::ChunkPosition> refs) = 0;
   virtual mb::result<int> height_at(int x, int z)                                                   = 0;
   virtual mb::result<mb::empty> set_block(const game::BlockPosition &pos, game::BlockStateId state) = 0;
   virtual mb::result<game::BlockStateId> get_block(const game::BlockPosition &pos)                  = 0;
};

}// namespace minecpp::game
