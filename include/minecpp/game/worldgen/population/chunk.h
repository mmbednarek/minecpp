#pragma once
#include <cstdint>
#include <map>
#include <minecpp/game/chunk/chunk.h>

namespace Game::WorldGen::Population {

struct Placement {
   int object_id;
   short x, z;
   short chunk_x, chunk_z;
   short height;
};

class ChunkPlacements {
   std::uint64_t m_seed;
   std::unordered_map<std::uint64_t, Placement> m_placements;
 public:
   ChunkPlacements(Game::Chunk &chunk, std::uint64_t seed);

   void populate_chunk(Game::Chunk &chunk);
   void populate_neighbour(Game::Chunk &chunk, Block::ChunkPos pos);
   void check_pos();
 private:
   Placement get_placement(int x, int z);
   void prepare_chunk(Game::Chunk &chunk);
   void put_object(Game::Chunk &chunk, int id, int x, int y, int z);
};

}
