#pragma once
#include "minecpp/game/chunks.h"
#include "minecpp/game/worldgen/population/population.h"

namespace minecpp::game::worldgen {

class Generator {
   std::uint64_t m_seed;
   Chunks &m_chunks;
   population::Population m_population;
 public:
   explicit Generator(Chunks &provider, std::uint64_t seed);

   void generate_chunk(int x, int z);
   void generate_terrain(int x, int z);
   void populate_chunk(int x, int z);
};

}