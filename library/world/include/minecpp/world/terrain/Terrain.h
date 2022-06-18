#pragma once
#include "Height.h"
#include <cstdint>
#include <memory>
#include <minecpp/random/JavaRandom.h>
#include <minecpp/random/Perlin.h>
#include <minecpp/random/Perlin3d.h>
#include <minecpp/random/Random.h>
#include <minecpp/world/Chunk.h>
#include <minecpp/world/Section.h>

namespace minecpp::world::terrain {

inline constexpr int chunk_size = 16;

class Terrain
{
   HeightGenerator height_gen;
   random::JavaRandom rand;
   int x, z;
   std::array<short, 256> height_map;
   std::array<short, 256> orig_height_map;

   int air_id;
   int stone_id;
   int dirt_id;
   int grass_id;
   int gravel_id;
   int sand_id;
   int water_id;
   int snow_id;
   int snow_block_id;

 public:
   Terrain(uint64_t seed, int x, int z);

   std::unique_ptr<Chunk> generate();

 private:
   [[nodiscard]] constexpr short height_at(int x, int z);
   [[nodiscard]] constexpr short orig_height_at(int x, int z);
   constexpr void set_height_at(int x, int z, short height);

   Section generate_section(int sec);
   bool section_empty(int sec);
};

}// namespace minecpp::world::terrain
