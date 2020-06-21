#include "chunks.h"
#include <mineutils/compression.h>
#include <region/reader.h>

namespace ChunkStorage {

ChunkManager::ChunkManager(Regions regions) : regions(std::move(regions)) {}

constexpr int64_t max_z = 1875060;

static constexpr int64_t coord(int x, int z) {
   return static_cast<int64_t>(z) + max_z * static_cast<int64_t>(x);
}

Game::NetChunk &ChunkManager::get_chunk(int x, int z) {
   auto iter = chunks.find(coord(x, z));
   if (iter != chunks.end()) {
      return *iter->second;
   }

   load_chunk(x, z);

   return *chunks.at(coord(x, z));
}

static constexpr int chunk_to_region(int cord) {
   if (cord < 0) {
      return cord / 32 - 1;
   }
   return cord / 32;
}

static constexpr int block_to_chunk(int cord) {
   return cord < 0 ? (cord / 16 - 1) : (cord / 16);
}

void ChunkManager::load_chunk(int x, int z) {
   auto data = regions.read_region(chunk_to_region(x), chunk_to_region(z),
                                   [x, z](std::fstream &f) {
                                      Region::Reader r(f);
                                      return r.load_chunk(x, z);
                                   });

   auto chunk_data = std::any_cast<std::vector<uint8_t>>(data);

   std::istringstream compressed_stream(
       std::string((char *)chunk_data.data(), chunk_data.size()));

   Utils::ZlibInputStream chunk_stream(compressed_stream);
   NBT::Reader cr(chunk_stream);
   cr.check_signature();
   cr.find_compound("Level");

   chunks[coord(x, z)] = std::make_unique<Game::NetChunk>(Game::NetChunk(cr));
}

void ChunkManager::set_block(int x, int y, int z, uint32_t state) {
   chunks[coord(block_to_chunk(x), block_to_chunk(z))]->set_block(
       x % 16, y, z % 16, state);
}

} // namespace ChunkStorage
