#include "worldgen.h"
#include "popobject.h"
#include <game/blocks/registry.h>
#include <minerandom/java_random.h>
#include <spdlog/spdlog.h>

namespace Game::WorldGen {

ChunkGenerator::ChunkGenerator(Population &population, uint64_t seed, int x, int z) :  height_gen(seed), rand(seed), cave_shape(rand), cave_level(rand), population(population), x(x), z(z) {
   for (int rx = 0; rx < chunk_size; ++rx) {
      for (int rz = 0; rz < chunk_size; ++rz) {
         auto block_x = chunk_size * x + rx;
         auto block_z = chunk_size * z + rz;

         set_height_at(rx, rz, height_gen.at(block_x, block_z));
      }
   }

   population.prepare_chunk(height_map, x, z);

   std::copy(height_map.begin(), height_map.end(), orig_height_map.begin());

   NBT::CompoundContent empty_attribs;
   NBT::CompoundContent not_snowy;
   not_snowy["snowy"] = NBT::make_string("false");

   air_id = Block::encode_state("minecraft:air", empty_attribs);
   stone_id = Block::encode_state("minecraft:stone", empty_attribs);
   dirt_id = Block::encode_state("minecraft:dirt", empty_attribs);
   grass_id = Block::encode_state("minecraft:grass_block", not_snowy);
   sand_id = Block::encode_state("minecraft:sand", empty_attribs);
   water_id = Block::encode_state("minecraft:water", empty_attribs);
}

bool ChunkGenerator::section_empty(int sec) {
   for (int z = 0; z < chunk_size; ++z) {
      for (int x = 0; x < chunk_size; ++x) {
         if (height_at(x, z) + 1 > sec * chunk_size) {
            return false;
         }
      }
   }
   return true;
}

Section ChunkGenerator::generate_section(int sec) {
   SectionBuilder builder;
   builder.fill([this, sec](short x, short y, short z) -> int {
      auto block_y = chunk_size * sec + y;
      auto height = height_at(x, z);
      if (block_y > height) {
         if (block_y < 50) {
            return water_id;
         }

         auto placement = population.get_placement(this->x * chunk_size + x, this->z * chunk_size + z);
         if (placement.object_id >= 0) {
            spdlog::info("found placements {}", placement.object_id);
            auto &obj = pop_objects[placement.object_id];
            if (block_y >= placement.height && block_y < placement.height + obj->height()) {
               return obj->block_at(placement.x, block_y - placement.height, placement.z);
            }
         }

         return air_id;
      }

      auto cshape = cave_shape.at(Utils::Vec2(this->x * chunk_size + x, this->z * chunk_size + z) / 40.0);
      if (cshape > -0.06 && cshape < 0.06) {
         auto clevel = 40 + cave_level.at(Utils::Vec2(this->x * chunk_size + x, this->z * chunk_size + z) / 40.0) * 70;
         auto cave_height = 4.0 * (1.0 - 16.0 * std::abs(cshape));
//         auto cave_height = 5.0;
         if (std::abs(block_y - clevel) < cave_height) {
            return air_id;
         }
      }

      if (block_y == height) {
         if (block_y < 52) {
            return sand_id;
         }
         return grass_id;
      }
      if (height - block_y < 3) {
         if (block_y < 52) {
            return sand_id;
         }
         return dirt_id;
      }
      return stone_id;
   });
   return builder.build();
}

std::unique_ptr<Chunk> ChunkGenerator::generate() {
   auto result = std::make_unique<Chunk>(x, z, height_map);
   for (int i = 0; i < 8; ++i) {
      if (section_empty(i))
         break;
      result->put_section(i, generate_section(i));
   }
   return result;
}

constexpr short ChunkGenerator::height_at(const int x, const int z) {
   return height_map[x + z * chunk_size];
}

constexpr short ChunkGenerator::orig_height_at(int x, int z) {
   return orig_height_map[x + z * chunk_size];
}

constexpr void ChunkGenerator::set_height_at(int x, int z, short value) {
   height_map[x + z * chunk_size] = value;
}

}// namespace Game::WorldGen