#pragma once
#include "notifier.h"
#include <minecpp/error/result.h>

namespace minecpp::game {

class World {
 public:
   virtual Notifier &notifier() = 0;
   virtual result<empty> add_refs(uuid player, std::vector<block::ChunkPos> refs) = 0;
   virtual result<empty> free_refs(uuid player, std::vector<block::ChunkPos> refs) = 0;
   virtual result<int> height_at(int x, int z) = 0;
};

}
