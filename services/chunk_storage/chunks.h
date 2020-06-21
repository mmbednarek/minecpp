#pragma once
#include <cstdint>
#include <map>
#include <memory>
#include <game/chunk/netchunk.h>
#include "regions.h"

namespace ChunkStorage {

class ChunkManager {
   std::map<int64_t, std::unique_ptr<Game::NetChunk>> chunks;
   Regions regions;
 public:
   explicit ChunkManager(Regions regions);

   Game::NetChunk &get_chunk(int x, int y);
   void load_chunk(int x, int y);
   void set_block(int x, int y, int z, uint32_t state);
};

}
