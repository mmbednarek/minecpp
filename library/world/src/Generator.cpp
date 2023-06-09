#include <minecpp/game/ChunkPosition.h>
#include <minecpp/game/property/Direction.h>
#include <minecpp/game/property/Face.h>
#include <minecpp/world/BlockState.h>
#include <minecpp/world/Generator.h>
#include <minecpp/world/LightSystem.h>
#include <minecpp/world/terrain/Terrain.h>
#include <spdlog/spdlog.h>

namespace minecpp::world {

Generator::Generator(IChunkSystem &provider, std::uint64_t seed) :
    m_seed(seed),
    m_chunk_system(provider),
    m_temporary_world(provider),
    m_light_system(m_temporary_world),
    m_population(provider, seed)
{
}

void Generator::generate_chunk(game::ChunkPosition position)
{
   auto curr_state = m_chunk_system.chunk_state_at(position);
   if (curr_state == ChunkState::COMPLETE) {
      return;// ok, already generated
   }

   if (curr_state == ChunkState::ABSENT || curr_state == ChunkState::EMPTY) {
      generate_terrain(position);
   }

   populate_chunk(position);
   generate_light(position);

   m_chunk_system.set_chunk_state_at(position, ChunkState::COMPLETE);
   m_chunk_system.save_chunk_at(position);
}

void Generator::generate_terrain(game::ChunkPosition position)
{
   terrain::Terrain gen(m_seed, position.x(), position.z());

   world::Chunk *chunk{};
   if (m_chunk_system.chunk_state_at(position) == ChunkState::ABSENT) {
      chunk = m_chunk_system.create_empty_chunk_at(position);
   } else {
      chunk = m_chunk_system.chunk_at(position);
   }

   gen.write_terrain_to_chunk(chunk);
   m_chunk_system.set_chunk_state_at(position, world::ChunkState::TERRAIN);
}

void Generator::populate_chunk(game::ChunkPosition position)
{
   m_population.populate_chunk(position);
}

void Generator::generate_light(game::ChunkPosition position)
{
   auto *chunk = m_chunk_system.chunk_at(position);
   if (chunk == nullptr)
      return;

   for (int x = 0; x < 16; ++x) {
      for (int z = 0; z < 16; ++z) {
         auto height = chunk->height_at(game::HeightType::LightBlocking, {x, 0, z});
         for (int y = height + 1; y < 256; ++y) {
            chunk->set_light_value_at(game::LightType::Sky, {x, y, z}, 15);
         }
      }
   }

   //   return;

   for (int x = 0; x < 16; ++x) {
      for (int z = 0; z < 16; ++z) {
         auto block_pos = position.block_at(x, 0, z);
         auto max_y_res = m_temporary_world.height_at(game::HeightType::LightBlocking, block_pos);
         if (max_y_res.has_failed())
            continue;

         auto max_y = *max_y_res;
         auto min_y = max_y;

         for (auto dir_value : game::Direction::Values) {
            game::Direction dir{dir_value};
            auto nei_position = block_pos.neighbour_at(dir.to_face());
            auto height       = m_temporary_world.height_at(game::HeightType::LightBlocking, nei_position);
            if (height.has_failed())
               continue;

            if (min_y > *height) {
               min_y = *height;
            }
         }

         for (int y = min_y; y <= max_y; ++y) {
            auto block_pos_2 = position.block_at(x, y, z);
            auto block_state = m_temporary_world.block_at(block_pos_2);
            if (block_state.has_failed())
               continue;

            BlockState state{*block_state};
            m_light_system.recalculate_light(game::LightType::Sky, block_pos_2, state.solid_faces());
         }
      }
   }
}

}// namespace minecpp::world
