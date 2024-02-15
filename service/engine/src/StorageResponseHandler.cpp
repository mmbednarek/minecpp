#include "StorageResponseHandler.h"
#include "ChunkSystem.h"
#include "JobSystem.h"

#include "minecpp/debug/TraceManager.h"

#include <spdlog/spdlog.h>

namespace minecpp::service::engine {

StorageResponseHandler::StorageResponseHandler(JobSystem &job_system) :
    m_job_system(job_system)
{
}

void StorageResponseHandler::set_chunk_system(ChunkSystem *chunk_system)
{
   m_chunk_system = chunk_system;
}

void StorageResponseHandler::on_reply_empty_chunk(util::Context &ctx,
                                                  const net::storage::cb::ReplyEmptyChunk &message)
{
   MCPP_TRACE(HandlingEmptyChunk, _.chunk_x = message.position.x(), _.chunk_z = message.position.y());

   m_job_system.run([this, message]() {
      assert(m_chunk_system);
      m_chunk_system->handle_empty_chunk(game::ChunkPosition(message.position));
   });
}

void StorageResponseHandler::on_reply_chunk(util::Context &ctx, const net::storage::cb::ReplyChunk &message)
{
   MCPP_TRACE(HandlingChunkData, _.chunk_x = message.chunk.position.x(),
              _.chunk_z = message.chunk.position.y());

   m_job_system.run([this, message]() {
      assert(m_chunk_system);

      MCPP_TRACE(PreHandlingChunkDataJob, _.chunk_x = message.chunk.position.x(),
                 _.chunk_z = message.chunk.position.y());

      m_chunk_system->handle_chunk_data(message.chunk);

      MCPP_TRACE(PostHandlingChunkDataJob, _.chunk_x = message.chunk.position.x(),
                 _.chunk_z = message.chunk.position.y());
   });
}

void StorageResponseHandler::on_failure(util::Context &ctx, std::uint8_t msg_code)
{
   spdlog::warn("storage-response-handler: invalid message, msg_code: {}", msg_code);
}

}// namespace minecpp::service::engine
