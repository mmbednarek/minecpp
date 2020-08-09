#include "chunks.h"
#include <error/result.h>
#include <game/blocks/position.h>
#include <mineutils/compression.h>
#include <region/reader.h>

namespace ChunkStorage {

ChunkManager::ChunkManager(Regions regions) : regions(std::move(regions)) {}

constexpr int64_t max_z = 1875060;

static constexpr int64_t hash_chunk_pos(int x, int z) {
   return static_cast<int64_t>(z) + max_z * static_cast<int64_t>(x);
}

result<Game::Chunk &> ChunkManager::get_chunk(int x, int z) {
   auto iter = chunks.find(hash_chunk_pos(x, z));
   if (iter != chunks.end()) {
      return *iter->second;
   }

   return load_chunk(x, z);
}

result<Game::Chunk &> ChunkManager::get_chunk(Game::Block::ChunkPos pos) {
   return get_chunk(pos.x, pos.z);
}

result<Game::Chunk &> ChunkManager::load_chunk(int x, int z) {
   auto data = tryget(regions.read_chunk(x, z));
   auto chunk_data = std::any_cast<std::vector<uint8_t>>(data);
   std::istringstream compressed_stream(std::string((char *) chunk_data.data(), chunk_data.size()));

   Utils::ZlibInputStream chunk_stream(compressed_stream);
   NBT::Reader cr(chunk_stream);
   cr.check_signature();
   cr.find_compound("Level");

   auto hash = hash_chunk_pos(x, z);
   auto chunk = tryget(Game::Chunk::from_nbt(cr));
   auto &chunk_ref = *chunk;
   chunks[hash] = std::move(chunk);
   return chunk_ref;
}

result<empty> ChunkManager::set_block(int x, int y, int z, uint32_t state) {
   Game::Block::Position pos(x, y, z);
   auto chunk_pos = pos.chunk_pos();
   auto hashed_pos = hash_chunk_pos(chunk_pos.x, chunk_pos.z);

   if (auto iter = chunks.find(hashed_pos); iter == chunks.end()) {
      if (auto res = load_chunk(chunk_pos.x, chunk_pos.z); !res.ok()) {
         return res.err();
      }
   }

   chunks[hashed_pos]->set_block(pos.offset_x(), y, pos.offset_z(), state);
   return result_ok;
}

result<uuid> ChunkManager::add_refs(uuid engine_id, uuid player_id, std::vector<Game::Block::ChunkPos> coords) {
   uuid target_engine{};
   for (const auto &coord : coords) {
      auto chunk = tryget(get_chunk(coord.x, coord.z));
      if (!chunk.add_ref(engine_id, player_id)) {
         target_engine = chunk.get_lock();
      }
   }
   return target_engine;
}

result<uuid> ChunkManager::free_refs(uuid player_id, std::vector<Game::Block::ChunkPos> coords) {
   for (const auto &coord : coords) {
      auto chunk = tryget(get_chunk(coord.x, coord.z));
      chunk.free_ref(player_id);
   }
}

result<int> ChunkManager::height_at(int x, int z) {
   return tryget(get_chunk(Game::Block::Position(x, 0, z).chunk_pos())).height_at(x, z);
}

}// namespace ChunkStorage
