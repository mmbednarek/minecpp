#include "GenerateChunk.h"
#include <spdlog/spdlog.h>

namespace minecpp::service::engine::job {

GenerateChunk::GenerateChunk(world::Generator &generator, const game::ChunkPosition &position) :
    m_generator(generator),
    m_position(position)
{
}

void GenerateChunk::run()
{
   spdlog::debug("generating chunk at {}, {}", m_position.x(), m_position.z());
   m_generator.generate_chunk(m_position);
}

}// namespace minecpp::service::engine::job
