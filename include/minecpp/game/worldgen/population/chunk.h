#pragma once
#include <cstdint>
#include <map>
#include <minecpp/game/chunk/chunk.h>

namespace minecpp::game::worldgen::population {

struct Placement
{
   int object_id;
   unsigned object_seed;
   short x, z;
   short chunk_x, chunk_z;
   short height;
};

class ChunkPlacements
{
   std::uint64_t m_seed;
   std::unordered_map<std::uint64_t, Placement> m_placements;

 public:
   ChunkPlacements(game::Chunk &chunk, std::uint64_t seed);

   void populate_chunk(game::Chunk &chunk);
   void populate_neighbour(game::Chunk &chunk, block::ChunkPos pos);
   void check_pos();

 private:
   Placement get_placement(int x, int z);
   void prepare_chunk(game::Chunk &chunk);
   void put_object(game::Chunk &chunk, int id, int x, int y, int z);
};

}// namespace minecpp::game::worldgen::population
