#pragma once
#include "notifier.h"
#include <error/result.h>

namespace Game {

class World {
 public:
   virtual Notifier &notifier() = 0;
   virtual result<empty> add_refs(uuid player, std::vector<Block::ChunkPos> refs) = 0;
   virtual result<empty> free_refs(uuid player, std::vector<Block::ChunkPos> refs) = 0;
   virtual result<int> height_at(int x, int z) = 0;
};

}
