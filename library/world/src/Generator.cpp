#include <minecpp/world/BlockState.h>
#include <minecpp/world/Generator.h>
#include <minecpp/world/LightSystem.h>
#include <minecpp/world/terrain/Terrain.h>
#include <queue>

namespace minecpp::world {

Generator::Generator(Chunks &provider, std::uint64_t seed) :
    m_seed(seed),
    m_chunks(provider),
    m_population(provider, seed)
{
}

void Generator::generate_chunk(game::ChunkPosition position)
{
   auto curr_state = m_chunks.get_chunk_state(position).unwrap(ChunkState::ABSENT);
   if (curr_state == ChunkState::COMPLETE) {
      return;// ok, already generated
   }

   if (curr_state == ChunkState::ABSENT) {
      generate_terrain(position);
   }

   populate_chunk(position);
   generate_light(position);
}

void Generator::generate_terrain(game::ChunkPosition position)
{
   terrain::Terrain gen(m_seed, position.x, position.z);
   auto chunk = gen.generate();
   m_chunks.put_chunk(position, std::move(chunk));
}

void Generator::populate_chunk(game::ChunkPosition position)
{
   m_population.populate_chunk(position);
}

void Generator::generate_light(game::ChunkPosition position)
{
   auto &chunk = m_chunks.get_incomplete_chunk(position.x, position.z);
   for (int x = 0; x < 16; ++x) {
      for (int z = 0; z < 16; ++z) {
         auto height = chunk.height_at(game::HeightType::LightBlocking, {x, 0, z});
         for (int y = height + 1; y < 256; ++y) {
            chunk.set_light(game::LightType::Sky, {x, y, z}, 15);
         }
      }
   }

   LightSystem::recalculate_light_for_chunk(game::LightType::Sky, chunk);
}

}// namespace minecpp::world
