#pragma once
#include "Regions.h"
#include <boost/uuid/uuid.hpp>
#include <cstdint>
#include <map>
#include <mb/result.h>
#include <memory>
#include <minecpp/error/Result.h>
#include <minecpp/game/Game.h>
#include <minecpp/game/player/Id.h>
#include <minecpp/random/JavaRandom.h>
#include <minecpp/world/Chunk.h>
#include <minecpp/world/Chunks.h>
#include <minecpp/world/Generator.h>
#include <minecpp/world/terrain/Terrain.h>

namespace minecpp::service::chunk_storage {

using uuid = boost::uuids::uuid;

class ChunkManager : public world::Chunks
{
   std::map<int64_t, std::unique_ptr<world::Chunk>> m_chunks;
   Regions m_regions;
   world::Generator gen;


 public:
   explicit ChunkManager(Regions regions);

   world::Chunk &get_incomplete_chunk(int x, int z) override;
   mb::result<mb::empty> put_chunk(int x, int z, std::unique_ptr<world::Chunk> chunk) override;
   mb::result<world::ChunkState> get_chunk_state(int x, int z) override;
   mb::result<world::Chunk &> get_chunk(int x, int y);
   mb::result<world::Chunk &> get_chunk(const minecpp::game::ChunkPosition &pos);
   mb::result<world::Chunk &> load_chunk(int x, int y);
   [[nodiscard]] mb::result<mb::empty> save_chunk(int x, int z);
   mb::result<mb::empty> set_block(int x, int y, int z, uint32_t state);
   mb::result<int> height_at(int x, int z);
   mb::result<uuid> add_refs(uuid engine_id, game::PlayerId player_id,
                             std::vector<minecpp::game::ChunkPosition> coords);
   mb::result<mb::empty> free_refs(game::PlayerId player_id,
                                   std::vector<minecpp::game::ChunkPosition> coords);
};

}// namespace minecpp::service::chunk_storage
