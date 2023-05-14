#include <minecpp/game/ChunkPosition.h>
#include <minecpp/util/Loop.h>
#include <minecpp/world/population/Population.h>
#include <spdlog/spdlog.h>

namespace minecpp::world::population {

constexpr std::uint64_t g_chunk_seed_coef_1 = 0x2b8a12ba85c7;
constexpr std::uint64_t g_chunk_seed_coef_2 = 0x1e3ca454fe3e7;
constexpr std::uint64_t g_chunk_seed_coef_3 = 0x9adacb410e23;
constexpr std::uint64_t g_chunk_seed_coef_4 = 0xf84606d2fff5;

namespace {

std::uint64_t make_chunk_seed(std::uint64_t seed, game::ChunkPosition pos)
{
   return seed * (g_chunk_seed_coef_1 * static_cast<std::uint64_t>(pos.x()) +
                  g_chunk_seed_coef_2 * static_cast<std::uint64_t>(pos.z()) + g_chunk_seed_coef_3) +
          g_chunk_seed_coef_4;
}

}// namespace

Population::Population(IChunkSystem &chunks, std::uint64_t seed) :
    m_chunk_system(chunks),
    m_seed(seed)
{
}

void Population::populate_chunk(game::ChunkPosition pos)
{
   auto *chunk = m_chunk_system.chunk_at(pos);
   if (chunk == nullptr) {
      spdlog::error("no chunk found at position");
      return;
   }

   // populate main chunk
   get_chunk_placements_by_chunk(*chunk).populate_chunk(*chunk);

   // populate from chunks around
   minecpp::util::around(pos.x(), pos.z(), [this, chunk](int x, int z) {
      game::ChunkPosition pos{x, z};
      get_chunk_placements(pos).populate_neighbour(*chunk, pos);
   });

   chunk->set_full();
}

ChunkPlacements &Population::load_chunk_placements(Chunk &chunk)
{
   auto placement_ptr = std::make_unique<ChunkPlacements>(chunk, make_chunk_seed(m_seed, chunk.pos()));
   auto &placement    = *placement_ptr;
   m_cache.emplace(chunk.pos().hash(), std::move(placement_ptr));
   return placement;
}

ChunkPlacements &Population::get_chunk_placements_by_chunk(Chunk &chunk)
{
   auto iter = m_cache.find(chunk.pos().hash());
   if (iter != m_cache.end()) {
      return *iter->second;
   }
   return load_chunk_placements(chunk);
}

ChunkPlacements &Population::get_chunk_placements(game::ChunkPosition pos)
{
   auto iter = m_cache.find(pos.hash());
   if (iter != m_cache.end()) {
      return *iter->second;
   }

   auto *chunk = m_chunk_system.chunk_at(pos);
   if (chunk == nullptr || m_chunk_system.chunk_state_at(pos) == world::EMPTY) {
      chunk = m_chunk_system.create_chunk_with_terrain_at(pos);
   }

   return load_chunk_placements(*chunk);
}

}// namespace minecpp::world::population
