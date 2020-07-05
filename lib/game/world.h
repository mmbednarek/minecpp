#pragma once
#include "notifier.h"

namespace Game {

class World {
 public:
   virtual Notifier &notifier() = 0;
   virtual void add_refs(uuid player, std::vector<Block::ChunkPos> refs) = 0;
   virtual void free_refs(uuid player, std::vector<Block::ChunkPos> refs) = 0;
};

}
