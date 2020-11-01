#pragma once
#include "regions.h"
#include <boost/uuid/uuid.hpp>
#include <cstdint>
#include <error/result.h>
#include <game/blocks/position.h>
#include <game/chunk/chunk.h>
#include <game/chunks.h>
#include <game/worldgen/generator.h>
#include <game/worldgen/terrain/terrain.h>
#include <map>
#include <memory>
#include <minerandom/java_random.h>

namespace ChunkStorage {

using uuid = boost::uuids::uuid;

class ChunkManager : public Game::Chunks {
   std::map<int64_t, std::unique_ptr<Game::Chunk>> chunks;
   Regions regions;
   Game::WorldGen::Generator gen;


 public:
   explicit ChunkManager(Regions regions);

   Game::Chunk &get_incomplete_chunk(int x, int z) override;
   result<empty> put_chunk(int x, int z, std::unique_ptr<Game::Chunk> chunk) override;
   result<Game::ChunkState> get_chunk_state(int x, int z) override;
   result<Game::Chunk &> get_chunk(int x, int y);
   result<Game::Chunk &> get_chunk(Game::Block::ChunkPos pos);
   result<Game::Chunk &> load_chunk(int x, int y);
   result<empty> set_block(int x, int y, int z, uint32_t state);
   result<int> height_at(int x, int z);
   result<uuid> add_refs(uuid engine_id, uuid player_id, std::vector<Game::Block::ChunkPos> coords);
   result<empty> free_refs(uuid player_id, std::vector<Game::Block::ChunkPos> coords);
};

}// namespace ChunkStorage
