#include "chunks.h"
#include <game/blocks/position.h>
#include <mineutils/compression.h>
#include <region/reader.h>

namespace ChunkStorage {

ChunkManager::ChunkManager(Regions regions) : regions(std::move(regions)) {}

constexpr int64_t max_z = 1875060;

static constexpr int64_t hash_chunk_pos(int x, int z) {
   return static_cast<int64_t>(z) + max_z * static_cast<int64_t>(x);
}

Game::Chunk &ChunkManager::get_chunk(int x, int z) {
   auto iter = chunks.find(hash_chunk_pos(x, z));
   if (iter != chunks.end()) {
      return *iter->second;
   }

   load_chunk(x, z);

   return *chunks.at(hash_chunk_pos(x, z));
}

static constexpr int chunk_to_region(int cord) { return cord < 0 ? (cord / 32 - 1) : cord / 32; }

void ChunkManager::load_chunk(int x, int z) {
   auto data = regions.read_region(chunk_to_region(x), chunk_to_region(z), [x, z](std::fstream &f) {
      Region::Reader r(f);
      return r.load_chunk(x, z);
   });

   auto chunk_data = std::any_cast<std::vector<uint8_t>>(data);

   std::istringstream compressed_stream(std::string((char *)chunk_data.data(), chunk_data.size()));

   Utils::ZlibInputStream chunk_stream(compressed_stream);
   NBT::Reader cr(chunk_stream);
   cr.check_signature();
   cr.find_compound("Level");

   chunks[hash_chunk_pos(x, z)] = std::make_unique<Game::Chunk>(Game::Chunk(cr));
}

void ChunkManager::set_block(int x, int y, int z, uint32_t state) {
   Game::Block::Position pos(x, y, z);
   auto chunk_pos = pos.chunk_pos();
   auto hashed_pos = hash_chunk_pos(chunk_pos.x, chunk_pos.z);

   if (auto iter = chunks.find(hashed_pos); iter == chunks.end()) {
      load_chunk(chunk_pos.x, chunk_pos.z);
   }

   chunks[hashed_pos]->set_block(pos.offset_x(), y, pos.offset_z(), state);
}

uuid ChunkManager::add_refs(uuid engine_id, uuid player_id, std::vector<Game::Block::ChunkPos> coords) {
   uuid target_engine{};
   for (const auto &coord : coords) {
      auto chunk = get_chunk(coord.x, coord.z);
      if (!chunk.add_ref(engine_id, player_id)) {
         target_engine = chunk.get_lock();
      }
   }

   return target_engine;
}

uuid ChunkManager::free_refs(uuid player_id, std::vector<Game::Block::ChunkPos> coords) {
   for (const auto &coord : coords) {
      auto chunk = get_chunk(coord.x, coord.z);
      chunk.free_ref(player_id);
   }
}

int ChunkManager::height_at(int x, int z) {
   Game::Block::Position pos(x, 0, z);
   auto chunk_pos = pos.chunk_pos();
   auto hashed_pos = hash_chunk_pos(chunk_pos.x, chunk_pos.z);

   if (auto iter = chunks.find(hashed_pos); iter == chunks.end()) {
      load_chunk(chunk_pos.x, chunk_pos.z);
   }

   return chunks[hashed_pos]->height_at(x, z);
}

} // namespace ChunkStorage
