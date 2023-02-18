#include "ChunkSystem.h"
#include "job/GenerateChunk.h"
#include "JobSystem.h"
#include <spdlog/spdlog.h>

namespace minecpp::service::engine {

ChunkSystem::ChunkSystem(JobSystem &job_system, storage::StorageClient &storage_client, mb::u64 world_seed) :
    m_job_system(job_system),
    m_storage_client(storage_client),
    m_generator(*this, world_seed)
{
}

world::Chunk *ChunkSystem::chunk_at(const game::ChunkPosition &position)
{
   auto find_result = m_chunks.find(position.hash());
   if (find_result == m_chunks.end())
      return nullptr;

   return find_result->second.chunk;
}

SubscriptionState ChunkSystem::subscription_state(const game::ChunkPosition &position)
{
   auto find_result = m_chunks.find(position.hash());
   if (find_result == m_chunks.end())
      return SubscriptionState::Unsubscribed;
   return find_result->second.subscription_state;
}

void ChunkSystem::subscribe_chunk(const game::ChunkPosition &position)
{
   m_storage_client.subscribe_chunk(position);
}

void ChunkSystem::handle_chunk_data(const storage::ResponseChunkData &chunk)
{
   auto *new_chunk = m_chunk_pool.construct();
   new_chunk->read_from_proto(chunk.chunk_data());
   m_chunks.emplace(game::ChunkPosition::from_proto(chunk.chunk_data().position()).hash(),
                    ChunkMeta{SubscriptionState::Subscribed, world::ChunkState::COMPLETE, new_chunk});

   m_job_system.process_awaiting_tickets();
}

void ChunkSystem::handle_empty_chunk(const storage::ResponseEmptyChunk &chunk)
{
   spdlog::debug("chunk system: handling empty chunk");
   auto position = game::ChunkPosition::from_proto(chunk.position());
   m_job_system.create_job<job::GenerateChunk>(m_generator, position);
}

world::Chunk *ChunkSystem::create_empty_chunk_at(const game::ChunkPosition &position)
{
   auto *new_chunk = m_chunk_pool.construct(position.x(), position.z(), std::array<short, 256>{});
   m_chunks.emplace(position.hash(),
                    ChunkMeta{SubscriptionState::Subscribed, world::ChunkState::EMPTY, new_chunk});
   return new_chunk;
}

world::ChunkState ChunkSystem::chunk_state_at(const game::ChunkPosition &position)
{
   auto find_result = m_chunks.find(position.hash());
   if (find_result == m_chunks.end())
      return world::ChunkState::ABSENT;
   return find_result->second.chunk_state;
}

void ChunkSystem::set_chunk_state_at(const game::ChunkPosition &position, world::ChunkState state)
{
   auto find_result = m_chunks.find(position.hash());
   if (find_result == m_chunks.end())
      return;
   find_result->second.chunk_state = state;
}

world::Chunk *ChunkSystem::create_chunk_with_terrain_at(const game::ChunkPosition &position)
{
   m_generator.generate_terrain(position);
   return chunk_at(position);
}

void ChunkSystem::save_chunk_at(const game::ChunkPosition &position)
{
   m_storage_client.push_chunk(this->chunk_at(position));
}

}// namespace minecpp::service::engine