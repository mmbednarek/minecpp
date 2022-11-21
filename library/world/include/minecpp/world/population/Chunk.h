#pragma once
#include <cstdint>
#include <map>
#include <minecpp/world/Chunk.h>

namespace minecpp::world::population {

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
   ChunkPlacements(Chunk &chunk, std::uint64_t seed);

   void populate_chunk(Chunk &chunk);
   void populate_neighbour(Chunk &chunk, game::ChunkPosition pos);
   void check_pos();

 private:
   Placement get_placement(int x, int z);
   void prepare_chunk(Chunk &chunk);
   void put_object(Chunk &chunk, int id, game::BlockPosition position);
};

}// namespace minecpp::world::population
