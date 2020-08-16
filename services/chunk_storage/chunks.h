#pragma once
#include "regions.h"
#include <boost/uuid/uuid.hpp>
#include <cstdint>
#include <error/result.h>
#include <game/blocks/position.h>
#include <game/chunk/chunk.h>
#include <game/worldgen/worldgen.h>
#include <game/worldgen/population.h>
#include <map>
#include <memory>
#include <minerandom/java_random.h>

namespace ChunkStorage {

using uuid = boost::uuids::uuid;

class ChunkManager {
   std::map<int64_t, std::unique_ptr<Game::Chunk>> chunks;
   Regions regions;
   Rand::JavaRandom rand;
   Rand::Perlin perlin;
   Game::WorldGen::Population population;

 public:
   explicit ChunkManager(Regions regions);

   result<Game::Chunk &> get_chunk(int x, int y);
   result<Game::Chunk &> get_chunk(Game::Block::ChunkPos pos);
   result<Game::Chunk &> load_chunk(int x, int y);
   result<empty> set_block(int x, int y, int z, uint32_t state);
   result<int> height_at(int x, int z);
   result<uuid> add_refs(uuid engine_id, uuid player_id, std::vector<Game::Block::ChunkPos> coords);
   result<empty> free_refs(uuid player_id, std::vector<Game::Block::ChunkPos> coords);
};

}// namespace ChunkStorage
