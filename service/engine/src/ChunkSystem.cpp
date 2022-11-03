#include "ChunkSystem.h"
#include "JobSystem.h"
#include <spdlog/spdlog.h>

namespace minecpp::service::engine {

ChunkSystem::ChunkSystem(JobSystem &job_system, storage::StorageClient &storage_client) :
    m_job_system(job_system),
    m_storage_client(storage_client)
{
}

world::Chunk *ChunkSystem::chunk_at(const game::ChunkPosition &position)
{
   auto find_result = m_chunks.find(position.hash());
   if (find_result == m_chunks.end())
      return nullptr;

   return find_result->second.chunk;
}

SubscriptionState ChunkSystem::chunk_state(const game::ChunkPosition &position)
{
   auto find_result = m_chunks.find(position.hash());
   if (find_result == m_chunks.end())
      return SubscriptionState::Unsubscribed;
   return find_result->second.state;
}

void ChunkSystem::subscribe_chunk(const game::ChunkPosition &position)
{
   m_storage_client.subscribe_chunk(position);
}

void ChunkSystem::handle_chunk_data(const storage::ResponseChunkData &chunk)
{
   spdlog::info("storing chunk at {} {}", chunk.chunk_data().position().x(),
                chunk.chunk_data().position().z());
   auto *new_chunk = m_chunk_pool.construct();
   new_chunk->read_from_proto(chunk.chunk_data());
   m_chunks.emplace(game::ChunkPosition::from_proto(chunk.chunk_data().position()).hash(),
                    ChunkMeta{SubscriptionState::Subscribed, new_chunk});

   m_job_system.process_awaiting_tickets();
}

}// namespace minecpp::service::engine