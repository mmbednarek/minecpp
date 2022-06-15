#pragma once
#include "Regions.h"
#include <boost/uuid/uuid.hpp>
#include <cstdint>
#include <map>
#include <mb/result.h>
#include <memory>
#include <minecpp/error/Result.h>
#include <minecpp/game/chunk/Chunk.h>
#include <minecpp/game/Chunks.h>
#include <minecpp/game/Game.h>
#include <minecpp/game/worldgen/Generator.h>
#include <minecpp/game/worldgen/terrain/Terrain.h>
#include <minecpp/player/Id.h>
#include <minecpp/random/JavaRandom.h>

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
   mb::result<uuid> add_refs(uuid engine_id, player::Id player_id,
                             std::vector<minecpp::game::ChunkPosition> coords);
   mb::result<mb::empty> free_refs(player::Id player_id, std::vector<minecpp::game::ChunkPosition> coords);
};

}// namespace minecpp::service::chunk_storage
