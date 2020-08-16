#pragma once
#include <cstdint>
#include <error/result.h>
#include <map>
#include <minerandom/random.h>

namespace Game::WorldGen {

struct Placement {
   int object_id;
   short x, z;
   short height;
};

class Population {
   Rand::Random &rand;
   std::map<uint64_t, Placement> placements;
   uint64_t coef1, coef2, coef3;

 public:
   explicit Population(Rand::Random &rand);

   void prepare_chunk(std::array<short, 256> &heightmap, int x, int z);
   void put_object(std::array<short, 256> &heightmap, int id, int x, int z);
   Placement get_placement(int x, int z);
};

}// namespace Game::WorldGen