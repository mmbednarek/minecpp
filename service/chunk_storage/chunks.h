#pragma once
#include "regions.h"
#include <boost/uuid/uuid.hpp>
#include <cstdint>
#include <map>
#include <mb/result.h>
#include <memory>
#include <minecpp/error/result.h>
#include <minecpp/game/block/position.h>
#include <minecpp/game/chunk/chunk.h>
#include <minecpp/game/chunks.h>
#include <minecpp/game/game.h>
#include <minecpp/game/worldgen/generator.h>
#include <minecpp/game/worldgen/terrain/terrain.h>
#include <minecpp/player/id.h>
#include <minecpp/random/java_random.h>

namespace minecpp::service::chunk_storage {

using uuid = boost::uuids::uuid;

class ChunkManager : public minecpp::game::Chunks
{
   std::map<int64_t, std::unique_ptr<minecpp::game::Chunk>> m_chunks;
   Regions m_regions;
   minecpp::game::worldgen::Generator gen;


 public:
   explicit ChunkManager(Regions regions);

   minecpp::game::Chunk &get_incomplete_chunk(int x, int z) override;
   mb::result<mb::empty> put_chunk(int x, int z, std::unique_ptr<minecpp::game::Chunk> chunk) override;
   mb::result<minecpp::game::ChunkState> get_chunk_state(int x, int z) override;
   mb::result<minecpp::game::Chunk &> get_chunk(int x, int y);
   mb::result<minecpp::game::Chunk &> get_chunk(const minecpp::game::ChunkPosition &pos);
   mb::result<minecpp::game::Chunk &> load_chunk(int x, int y);
   [[nodiscard]] mb::result<mb::empty> save_chunk(int x, int z);
   mb::result<mb::empty> set_block(int x, int y, int z, uint32_t state);
   mb::result<int> height_at(int x, int z);
   mb::result<uuid> add_refs(uuid engine_id, player::Id player_id, std::vector<minecpp::game::block::ChunkPos> coords);
   mb::result<mb::empty> free_refs(player::Id player_id, std::vector<minecpp::game::block::ChunkPos> coords);
};

}// namespace minecpp::service::chunk_storage
