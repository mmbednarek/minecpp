#pragma once
#include "../chunks.h"
#include "population/population.h"

namespace Game::WorldGen {

class Generator {
   std::uint64_t m_seed;
   Chunks &m_chunks;
   Population::Population m_population;
 public:
   explicit Generator(Chunks &provider, std::uint64_t seed);

   void generate_chunk(int x, int z);
   void generate_terrain(int x, int z);
   void populate_chunk(int x, int z);
};

}