#include "generator.h"
#include "game/worldgen/terrain/terrain.h"

namespace Game::WorldGen {

Generator::Generator(Chunks &provider, std::uint64_t seed) : m_seed(seed), m_chunks(provider), m_population(provider, seed) {
}

void Generator::generate_chunk(int x, int z) {
   auto curr_state = m_chunks.get_chunk_state(x, z).unwrap(ChunkState::ABSENT);
   if (curr_state == ChunkState::COMPLETE) {
      return; // ok, already generated
   }

   if (curr_state == ChunkState::ABSENT) {
      generate_terrain(x, z);
   }

   populate_chunk(x, z);
}

void Generator::generate_terrain(int x, int z) {
   Terrain::Terrain gen(m_seed, x, z);
   auto chunk = gen.generate();
   m_chunks.put_chunk(x, z, std::move(chunk));
}

void Generator::populate_chunk(int x, int z) {
   m_population.populate_chunk(Block::ChunkPos(x, z));
}

}