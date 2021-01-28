#include <minecpp/game/worldgen/population/population.h>
#include <minecpp/mineutils/loop.h>

namespace Game::WorldGen::Population {

constexpr std::uint64_t chunk_seed_coef1 = 0x2b8a12ba85c7;
constexpr std::uint64_t chunk_seed_coef2 = 0x1e3ca454fe3e7;
constexpr std::uint64_t chunk_seed_coef3 = 0x9adacb410e23;
constexpr std::uint64_t chunk_seed_coef4 = 0xf84606d2fff5;

constexpr std::uint64_t make_chunk_seed(std::uint64_t seed, Block::ChunkPos pos) {
   return seed * (chunk_seed_coef1 * pos.x + chunk_seed_coef2 * pos.z + chunk_seed_coef3) + chunk_seed_coef4;
}

Population::Population(Chunks &chunks, std::uint64_t seed) : m_chunks(chunks), m_seed(seed) {
}

void Population::populate_chunk(Block::ChunkPos pos) {
   auto &chunk = m_chunks.get_incomplete_chunk(pos.x, pos.z);

   // populate main chunk
   get_chunk_placements_by_chunk(chunk).populate_chunk(chunk);

   // populate from chunks around
   Utils::around(pos.x, pos.z, [this, &chunk](int x, int z) {
      auto pos = Block::ChunkPos(x, z);
      get_chunk_placements(pos).populate_neighbour(chunk, pos);
   });

   chunk.full = true;
}

ChunkPlacements &Population::load_chunk_placements(Chunk &chunk) {
   auto placement_ptr = std::make_unique<ChunkPlacements>(chunk, make_chunk_seed(m_seed, chunk.pos()));
   auto &placement = *placement_ptr;
   m_cache.emplace(std::pair(chunk.pos().hash(), std::move(placement_ptr)));
   return placement;
}

ChunkPlacements &Population::get_chunk_placements_by_chunk(Chunk &chunk) {
   auto iter = m_cache.find(chunk.pos().hash());
   if (iter != m_cache.end()) {
      return *iter->second;
   }
   return load_chunk_placements(chunk);
}

ChunkPlacements &Population::get_chunk_placements(Block::ChunkPos pos) {
   auto iter = m_cache.find(pos.hash());
   if (iter != m_cache.end()) {
      return *iter->second;
   }
   return load_chunk_placements(m_chunks.get_incomplete_chunk(pos.x, pos.z));
}

}// namespace Game::WorldGen::Population
