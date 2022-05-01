#include <minecpp/game/block/registry.h>
#include <minecpp/game/worldgen/terrain/terrain.h>
#include <minecpp/random/java_random.h>
#include <minecpp/repository/block.h>
#include <spdlog/spdlog.h>

namespace minecpp::game::worldgen::terrain {

constexpr auto sea_level = 63;
constexpr auto sand_level = 64;

Terrain::Terrain(uint64_t seed, int x, int z) : height_gen(seed), rand(seed), x(x), z(z) {
   for (int rx = 0; rx < chunk_size; ++rx) {
      for (int rz = 0; rz < chunk_size; ++rz) {
         auto block_x = chunk_size * x + rx;
         auto block_z = chunk_size * z + rz;

         set_height_at(rx, rz, height_gen.at(block_x, block_z));
      }
   }

   std::copy(height_map.begin(), height_map.end(), orig_height_map.begin());

   air_id = repository::encode_block_by_tag("minecraft:air");
   stone_id = repository::encode_block_by_tag("minecraft:stone");
   dirt_id = repository::encode_block_by_tag("minecraft:dirt");
   grass_id = repository::encode_block_by_tag("minecraft:grass_block", std::make_pair("snowy", "false"));
   gravel_id = repository::encode_block_by_tag("minecraft:gravel");
   sand_id = repository::encode_block_by_tag("minecraft:sand");
   water_id = repository::encode_block_by_tag("minecraft:water");
   snow_id = repository::encode_block_by_tag("minecraft:snow");
   snow_block_id = repository::encode_block_by_tag("minecraft:snow_block");
}

bool Terrain::section_empty(int sec) {
   if (sec * chunk_size < sea_level) {
      return false;
   }
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

         if (block_y == height + 1) {
            if (block_y >= 95) {
               return snow_id;
            }
         }

         return air_id;
      }

      if (block_y == height) {
         if (block_y < 62) {
            return dirt_id;
         }
         if (block_y < sand_level) {
            return sand_id;
         }
         if (block_y > 130) {
            return snow_block_id;
         }
         if (block_y > 110) {
            if (rand.next_int(2) == 0) {
               return snow_block_id;
            }
            return stone_id;
         }
         if (block_y > 100) {
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
         if (block_y < 62) {
            return dirt_id;
         }
         if (block_y < sand_level) {
            return sand_id;
         }
         if (block_y > 110) {
            return snow_block_id;
         }
         if (block_y > 100) {
            return stone_id;
         }
         return dirt_id;
      }
      if (block_y > 130) {
         return snow_block_id;
      }
     return stone_id;
   });
   return builder.build();
}

std::unique_ptr<Chunk> Terrain::generate() {
   auto result = std::make_unique<Chunk>(x, z, height_map);
   for (int i = 0; i < 16; ++i) {
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

}// namespace minecpp::game::worldgen::terrain