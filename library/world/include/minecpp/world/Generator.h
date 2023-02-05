#pragma once
#include <minecpp/world/IChunkSystem.h>
#include <minecpp/world/population/Population.h>

namespace minecpp::world {

class Generator
{
 public:
   explicit Generator(IChunkSystem &provider, std::uint64_t seed);

   void generate_chunk(game::ChunkPosition position);
   void generate_terrain(game::ChunkPosition position);
   void generate_light(game::ChunkPosition position);
   void populate_chunk(game::ChunkPosition position);

 private:
   std::uint64_t m_seed;
   IChunkSystem &m_chunk_system;
   population::Population m_population;
//   game::ILightSystem &m_light_system;
};

}// namespace minecpp::world