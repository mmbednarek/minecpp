#include <minecpp/random/JavaRandom.h>
#include <minecpp/repository/Block.h>
#include <minecpp/world/terrain/Terrain.h>
#include <spdlog/spdlog.h>

namespace minecpp::world::terrain {

constexpr auto g_sea_level  = 63;
constexpr auto g_sand_level = 64;

Terrain::Terrain(uint64_t seed, int x, int z) :
    m_height_gen(seed),
    m_rand(seed)
{
   for (int rx = 0; rx < g_chunk_size; ++rx) {
      for (int rz = 0; rz < g_chunk_size; ++rz) {
         auto block_x = g_chunk_size * x + rx;
         auto block_z = g_chunk_size * z + rz;

         set_height_at(rx, rz, m_height_gen.at(block_x, block_z));
      }
   }

   std::copy(m_height_map.begin(), m_height_map.end(), m_orig_height_map.begin());

   m_air_id   = repository::encode_block_by_tag("minecraft:air");
   m_stone_id = repository::encode_block_by_tag("minecraft:stone");
   m_dirt_id  = repository::encode_block_by_tag("minecraft:dirt");
   m_grass_id = repository::encode_block_by_tag("minecraft:grass_block", std::make_pair("snowy", "false"));
   m_sand_id  = repository::encode_block_by_tag("minecraft:sand");
   m_water_id = repository::encode_block_by_tag("minecraft:water");
   m_snow_id  = repository::encode_block_by_tag("minecraft:snow");
   m_snow_block_id = repository::encode_block_by_tag("minecraft:snow_block");
}

bool Terrain::section_empty(int sec)
{
   if (sec * g_chunk_size < g_sea_level) {
      return false;
   }
   for (int z = 0; z < g_chunk_size; ++z) {
      for (int x = 0; x < g_chunk_size; ++x) {
         if (height_at(x, z) + 1 > sec * g_chunk_size) {
            return false;
         }
      }
   }
   return true;
}

Section Terrain::generate_section(int sec)
{
   SectionBuilder builder;
   builder.fill([this, sec](short x, short y, short z) -> game::BlockStateId {
      auto block_y = g_chunk_size * sec + y;
      auto height  = height_at(x, z);
      if (block_y > height) {
         if (block_y < g_sea_level) {
            return m_water_id;
         }

         if (block_y == height + 1) {
            if (block_y >= 95) {
               return m_snow_id;
            }
         }

         return m_air_id;
      }

      if (block_y == height) {
         if (block_y < 62) {
            return m_dirt_id;
         }
         if (block_y < g_sand_level) {
            return m_sand_id;
         }
         if (block_y > 130) {
            return m_snow_block_id;
         }
         if (block_y > 110) {
            if (m_rand.next_int(2) == 0) {
               return m_snow_block_id;
            }
            return m_stone_id;
         }
         if (block_y > 100) {
            return m_stone_id;
         }
         if (block_y > 86) {
            if (m_rand.next_int(2) == 0) {
               return m_stone_id;
            }
            return m_grass_id;
         }
         return m_grass_id;
      }
      if (height - block_y < 3) {
         if (block_y < 62) {
            return m_dirt_id;
         }
         if (block_y < g_sand_level) {
            return m_sand_id;
         }
         if (block_y > 110) {
            return m_snow_block_id;
         }
         if (block_y > 100) {
            return m_stone_id;
         }
         return m_dirt_id;
      }
      if (block_y > 130) {
         return m_snow_block_id;
      }
      return m_stone_id;
   });
   return builder.build();
}

void Terrain::write_terrain_to_chunk(Chunk *chunk)
{
   chunk->set_height_map(game::HeightType::WorldSurface, m_height_map);
   chunk->set_height_map(game::HeightType::MotionBlocking, m_height_map);
   chunk->set_height_map(game::HeightType::LightBlocking, m_height_map);

   for (int i = 0; i < 16; ++i) {
      if (section_empty(i))
         break;
      chunk->put_section(static_cast<mb::i8>(i), generate_section(i));
   }
}

constexpr short Terrain::height_at(const int x, const int z)
{
   const auto index = x + z * g_chunk_size;
   return m_height_map[static_cast<std::size_t>(index)];
}

constexpr void Terrain::set_height_at(int x, int z, short value)
{
   const auto index                              = x + z * g_chunk_size;
   m_height_map[static_cast<std::size_t>(index)] = value;
}

}// namespace minecpp::world::terrain