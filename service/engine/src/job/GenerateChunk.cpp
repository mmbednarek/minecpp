#include "GenerateChunk.h"

#include "minecpp/debug/TraceManager.h"

namespace minecpp::service::engine::job {

GenerateChunk::GenerateChunk(const util::Context &ctx, world::Generator &generator,
                             const game::ChunkPosition &position) :
    IJob(ctx),
    m_generator(generator),
    m_position(position)
{
}

void GenerateChunk::run()
{
   MCPP_TRACE_CTX(GeneratingChunk, m_context, _.chunk_x = m_position.x(), _.chunk_z = m_position.z());
   m_generator.generate_chunk(m_position);
}

}// namespace minecpp::service::engine::job
