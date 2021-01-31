#pragma once
#include "notifier.h"
#include <mb/result.h>

namespace minecpp::game {

class World {
 public:
   virtual Notifier &notifier() = 0;
   virtual mb::result<mb::empty> add_refs(uuid player, std::vector<block::ChunkPos> refs) = 0;
   virtual mb::result<mb::empty> free_refs(uuid player, std::vector<block::ChunkPos> refs) = 0;
   virtual mb::result<int> height_at(int x, int z) = 0;
};

}
