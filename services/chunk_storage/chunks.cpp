#include "chunks.h"
#include <minecpp/game/block/position.h>
#include <minecpp/region/reader.h>
#include <minecpp/util/compression.h>
#include <spdlog/spdlog.h>

namespace ChunkStorage {

ChunkManager::ChunkManager(Regions regions) : regions(std::move(regions)), gen(*this, 43254124543534345) {}

constexpr int64_t max_z = 1875060;
static constexpr int64_t hash_chunk_pos(int x, int z) {
   return static_cast<int64_t>(z) + max_z * static_cast<int64_t>(x);
}

minecpp::game::Chunk &ChunkManager::get_incomplete_chunk(int x, int z) {
   auto hash = hash_chunk_pos(x, z);
   auto iter = chunks.find(hash);
   if (iter != chunks.end()) {
      return *iter->second;
   }

   gen.generate_terrain(x, z);
   iter = chunks.find(hash);
   return *iter->second;
}

mb::result<minecpp::game::Chunk &> ChunkManager::get_chunk(int x, int z) {
   auto iter = chunks.find(hash_chunk_pos(x, z));
   if (iter != chunks.end() && iter->second->full) {
      return *iter->second;
   }
   return load_chunk(x, z);
}

mb::result<minecpp::game::Chunk &> ChunkManager::get_chunk(minecpp::game::block::ChunkPos pos) {
   return get_chunk(pos.x, pos.z);
}

mb::result<minecpp::game::Chunk &> ChunkManager::load_chunk(int x, int z) {
   /*
   auto data = MB_TRY(regions.read_chunk(x, z));
   auto chunk_data = std::any_cast<std::vector<uint8_t>>(data);
   std::istringstream compressed_stream(std::string((char *) chunk_data.data(), chunk_data.size()));

   minecpp::util::ZlibInputStream chunk_stream(compressed_stream);
   minecpp::nbt::Reader cr(chunk_stream);
   cr.check_signature();
   cr.find_compound("Level");

   auto chunk = MB_TRY(minecpp::game::Chunk::from_nbt(cr));
    */
   gen.generate_chunk(x, z);
   auto &chunk = chunks.at(hash_chunk_pos(x, z));
   return *chunk;
}

mb::result<mb::empty> ChunkManager::set_block(int x, int y, int z, uint32_t state) {
   minecpp::game::block::Position pos(x, y, z);
   auto chunk_pos = pos.chunk_pos();
   auto hashed_pos = hash_chunk_pos(chunk_pos.x, chunk_pos.z);

   if (auto iter = chunks.find(hashed_pos); iter == chunks.end()) {
      if (auto res = load_chunk(chunk_pos.x, chunk_pos.z); !res.ok()) {
         return res.err();
      }
   }

   chunks[hashed_pos]->set_block(pos.offset_x(), y, pos.offset_z(), state);
   return mb::ok;
}

mb::result<uuid> ChunkManager::add_refs(uuid engine_id, uuid player_id, std::vector<minecpp::game::block::ChunkPos> coords) {
   uuid target_engine{};
   for (const auto &coord : coords) {
      auto chunk = MB_TRY(get_chunk(coord.x, coord.z));
      if (!chunk.add_ref(engine_id, player_id)) {
         target_engine = chunk.get_lock();
      }
   }
   return target_engine;
}

mb::result<mb::empty> ChunkManager::free_refs(uuid player_id, std::vector<minecpp::game::block::ChunkPos> coords) {
   for (const auto &coord : coords) {
      auto chunk = MB_TRY(get_chunk(coord.x, coord.z));
      chunk.free_ref(player_id);
   }
   return mb::ok;
}

mb::result<int> ChunkManager::height_at(int x, int z) {
   auto res = get_chunk(minecpp::game::block::Position(x, 0, z).chunk_pos());
   if (!res.ok()) {
      return res.err();
   }
   return res.unwrap().height_at(x, z);
}

mb::result<mb::empty> ChunkManager::put_chunk(int x, int z, std::unique_ptr<minecpp::game::Chunk> chunk) {
   chunks[hash_chunk_pos(x, z)] = std::move(chunk);
   return mb::ok;
}

mb::result<minecpp::game::ChunkState> ChunkManager::get_chunk_state(int x, int z) {
   auto iter = chunks.find(hash_chunk_pos(x, z));
   if (iter == chunks.end()) {
      return minecpp::game::ChunkState::ABSENT;
   }

   if (iter->second->full) {
      return minecpp::game::ChunkState::COMPLETE;
   }

   return minecpp::game::ChunkState::TERRAIN;
}

}// namespace ChunkStorage
