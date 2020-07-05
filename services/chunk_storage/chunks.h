#pragma once
#include "regions.h"
#include <boost/uuid/uuid.hpp>
#include <cstdint>
#include <game/blocks/position.h>
#include <game/chunk/chunk.h>
#include <map>
#include <memory>

namespace ChunkStorage {

using uuid = boost::uuids::uuid;

class ChunkManager {
   std::map<int64_t, std::unique_ptr<Game::Chunk>> chunks;
   Regions regions;
 public:
   explicit ChunkManager(Regions regions);

   Game::Chunk &get_chunk(int x, int y);
   void load_chunk(int x, int y);
   void set_block(int x, int y, int z, uint32_t state);
   int height_at(int x, int z);
   uuid add_refs(uuid engine_id, uuid player_id, std::vector<Game::Block::ChunkPos> coords);
   uuid free_refs(uuid player_id, std::vector<Game::Block::ChunkPos> coords);
};

}
