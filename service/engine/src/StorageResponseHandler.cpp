#include "StorageResponseHandler.h"
#include "ChunkSystem.h"
#include "JobSystem.h"
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

void StorageResponseHandler::on_reply_empty_chunk(int a, const net::storage::cb::ReplyEmptyChunk &message)
{
   spdlog::info("storage-response-handler: handling empty chunk at {} {}", message.position.x(), message.position.y());
   m_job_system.run([this, message]() {
      assert(m_chunk_system);
      m_chunk_system->handle_empty_chunk(game::ChunkPosition(message.position));
   });
}

void StorageResponseHandler::on_reply_chunk(int a, const net::storage::cb::ReplyChunk &message)
{
   spdlog::info("storage-response-handler: handling chunk data at {} {}", message.chunk.position.x(), message.chunk.position.y());
   m_job_system.run([this, message]() {
      assert(m_chunk_system);
      m_chunk_system->handle_chunk_data(message.chunk);
   });
}

void StorageResponseHandler::on_failure(int a, std::uint8_t msg_code)
{
   spdlog::warn("storage-response-handler: invalid message, msg_code: {}", msg_code);
}

}// namespace minecpp::service::engine
