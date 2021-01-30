#pragma once
#include "regions.h"
#include <boost/uuid/uuid.hpp>
#include <cstdint>
#include <minecpp/error/result.h>
#include <minecpp/game/block/position.h>
#include <minecpp/game/chunk/chunk.h>
#include <minecpp/game/chunks.h>
#include <minecpp/game/worldgen/generator.h>
#include <minecpp/game/worldgen/terrain/terrain.h>
#include <map>
#include <memory>
#include <minecpp/random/java_random.h>

namespace ChunkStorage {

using uuid = boost::uuids::uuid;

class ChunkManager : public minecpp::game::Chunks {
   std::map<int64_t, std::unique_ptr<minecpp::game::Chunk>> chunks;
   Regions regions;
   minecpp::game::worldgen::Generator gen;


 public:
   explicit ChunkManager(Regions regions);

   minecpp::game::Chunk &get_incomplete_chunk(int x, int z) override;
   result<empty> put_chunk(int x, int z, std::unique_ptr<minecpp::game::Chunk> chunk) override;
   result<minecpp::game::ChunkState> get_chunk_state(int x, int z) override;
   result<minecpp::game::Chunk &> get_chunk(int x, int y);
   result<minecpp::game::Chunk &> get_chunk(minecpp::game::block::ChunkPos pos);
   result<minecpp::game::Chunk &> load_chunk(int x, int y);
   result<empty> set_block(int x, int y, int z, uint32_t state);
   result<int> height_at(int x, int z);
   result<uuid> add_refs(uuid engine_id, uuid player_id, std::vector<minecpp::game::block::ChunkPos> coords);
   result<empty> free_refs(uuid player_id, std::vector<minecpp::game::block::ChunkPos> coords);
};

}// namespace ChunkStorage
