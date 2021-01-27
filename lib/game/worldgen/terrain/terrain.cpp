#include "terrain.h"
#include <game/blocks/registry.h>
#include <minerandom/java_random.h>
#include <spdlog/spdlog.h>

namespace Game::WorldGen::Terrain {

constexpr auto sea_level = 63;
constexpr auto sand_level = 68;

Terrain::Terrain(uint64_t seed, int x, int z) :  height_gen(seed), rand(seed), x(x), z(z) {
   for (int rx = 0; rx < chunk_size; ++rx) {
      for (int rz = 0; rz < chunk_size; ++rz) {
         auto block_x = chunk_size * x + rx;
         auto block_z = chunk_size * z + rz;

         set_height_at(rx, rz, height_gen.at(block_x, block_z));
      }
   }

   std::copy(height_map.begin(), height_map.end(), orig_height_map.begin());

   NBT::CompoundContent empty_attribs;
   NBT::CompoundContent not_snowy;
   not_snowy["snowy"] = NBT::make_string("false");

   air_id = Block::encode_state("minecraft:air", empty_attribs);
   stone_id = Block::encode_state("minecraft:stone", empty_attribs);
   dirt_id = Block::encode_state("minecraft:dirt", empty_attribs);
   grass_id = Block::encode_state("minecraft:grass_block", not_snowy);
   gravel_id = Block::encode_state("minecraft:gravel", empty_attribs);
   sand_id = Block::encode_state("minecraft:sand", empty_attribs);
   water_id = Block::encode_state("minecraft:water", empty_attribs);
   snow_id = Block::encode_state("minecraft:snow", empty_attribs);
   snow_block_id = Block::encode_state("minecraft:snow_block", empty_attribs);
}

bool Terrain::section_empty(int sec) {
   for (int z = 0; z < chunk_size; ++z) {
      for (int x = 0; x < chunk_size; ++x) {
         if (height_at(x, z) + 1 > sec * chunk_size) {
            return false;
         }
      }
   }
   return true;
}

Section Terrain::generate_section(int sec) {
   SectionBuilder builder;
   builder.fill([this, sec](short x, short y, short z) -> int {
      auto block_y = chunk_size * sec + y;
      auto height = height_at(x, z);
      if (block_y > height) {
         if (block_y < sea_level) {
            return water_id;
         }

         if (block_y == height+1) {
            if (block_y >= 95) {
               return snow_id;
            }
         }

         return air_id;
      }

      if (block_y == height) {
         if (block_y < sand_level) {
            return sand_id;
         }
         if (block_y > 100) {
            return snow_block_id;
         }
         if (block_y > 97) {
            if (rand.next_int(2) == 0) {
               return snow_block_id;
            }
            return stone_id;
         }
         if (block_y > 90) {
            return stone_id;
         }
         if (block_y > 86) {
            if (rand.next_int(2) == 0) {
               return stone_id;
            }
            return grass_id;
         }
         return grass_id;
      }
      if (height - block_y < 3) {
         if (block_y < sand_level) {
            return sand_id;
         }
         if (block_y > 97) {
            return snow_block_id;
         }
         if (block_y > 90) {
            return stone_id;
         }
         return dirt_id;
      }
      return stone_id;
   });
   return builder.build();
}

std::unique_ptr<Chunk> Terrain::generate() {
   auto result = std::make_unique<Chunk>(x, z, height_map);
   for (int i = 0; i < 8; ++i) {
      if (section_empty(i))
         break;
      result->put_section(i, generate_section(i));
   }
   return result;
}

constexpr short Terrain::height_at(const int x, const int z) {
   return height_map[x + z * chunk_size];
}

constexpr short Terrain::orig_height_at(int x, int z) {
   return orig_height_map[x + z * chunk_size];
}

constexpr void Terrain::set_height_at(int x, int z, short value) {
   height_map[x + z * chunk_size] = value;
}

}// namespace Game::WorldGen