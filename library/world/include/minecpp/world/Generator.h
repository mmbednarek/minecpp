#pragma once
#include <minecpp/world/Chunks.h>
#include <minecpp/world/population/Population.h>

namespace minecpp::world {

class Generator
{
   std::uint64_t m_seed;
   Chunks &m_chunks;
   population::Population m_population;

 public:
   explicit Generator(Chunks &provider, std::uint64_t seed);

   void generate_chunk(game::ChunkPosition position);
   void generate_terrain(game::ChunkPosition position);
   void generate_light(game::ChunkPosition position);
   void populate_chunk(game::ChunkPosition position);
};

}// namespace minecpp::world