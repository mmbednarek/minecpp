#pragma once
#include "Height.h"
#include "minecpp/random/IRandom.h"
#include <cstdint>
#include <memory>
#include <minecpp/random/JavaRandom.h>
#include <minecpp/random/Perlin.h>
#include <minecpp/random/Perlin3D.h>
#include <minecpp/world/Chunk.h>
#include <minecpp/world/Section.h>

namespace minecpp::world::terrain {

inline constexpr int g_chunk_size = 16;

class Terrain
{
 public:
   Terrain(uint64_t seed, int x, int z);

   void write_terrain_to_chunk(Chunk *chunk);

 private:
   [[nodiscard]] constexpr short height_at(int x, int z);
   constexpr void set_height_at(int x, int z, short height);

   Section generate_section(int sec);
   bool section_empty(int sec);

 private:
   HeightGenerator m_height_gen;
   random::JavaRandom m_rand;
   std::array<short, 256> m_height_map{};
   std::array<short, 256> m_orig_height_map{};

   game::BlockStateId m_air_id{};
   game::BlockStateId m_stone_id{};
   game::BlockStateId m_dirt_id{};
   game::BlockStateId m_grass_id{};
   game::BlockStateId m_sand_id{};
   game::BlockStateId m_water_id{};
   game::BlockStateId m_snow_id{};
   game::BlockStateId m_snow_block_id{};
};

}// namespace minecpp::world::terrain
