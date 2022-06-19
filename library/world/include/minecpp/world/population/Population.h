#pragma once
#include "Chunk.h"
#include <cstdint>
#include <map>
#include <minecpp/random/Random.h>
#include <minecpp/world/Chunks.h>

namespace minecpp::world::population {

class Population
{
   Chunks &m_chunks;
   std::uint64_t m_seed;
   std::unordered_map<std::uint64_t, std::unique_ptr<ChunkPlacements>> m_cache;

 public:
   explicit Population(Chunks &chunks, std::uint64_t seed);

   void populate_chunk(game::ChunkPosition pos);
   ChunkPlacements &load_chunk_placements(Chunk &chunk);
   ChunkPlacements &get_chunk_placements_by_chunk(Chunk &chunk);
   ChunkPlacements &get_chunk_placements(game::ChunkPosition pos);
};

}// namespace minecpp::world::population