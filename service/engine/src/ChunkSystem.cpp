#include "ChunkSystem.h"
#include "job/GenerateChunk.h"
#include "JobSystem.h"

#include "minecpp/service/storage/Storage.h"

#include <spdlog/spdlog.h>

namespace minecpp::service::engine {

ChunkLoadTicket::ChunkLoadTicket(ChunkSystem &chunk_system, game::ChunkPosition position,
                                 ChunkFunc callback) :
    m_callback(std::move(callback)),
    m_position(position),
    m_chunk_system(chunk_system)
{
   chunk_system.on_chunk_is_complete.connect_to<&ChunkLoadTicket::on_chunk_is_complete>(m_sink, this);
}

void ChunkLoadTicket::on_chunk_is_complete(game::ChunkPosition position)
{
   if (position != m_position)
      return;

   std::unique_lock lk{m_mtx};

   //   assert(m_sink.has_value());
   //   ++m_call_count;
   //   assert(m_call_count < 2);

   auto *chunk = m_chunk_system.chunk_at(m_position);
   assert(chunk);
   m_callback(chunk);

   m_sink->disconnect();
   m_sink.reset();

   //   m_chunk_system.release_ticket(this);
}

ChunkSystem::ChunkSystem(JobSystem &job_system, storage::StorageClient &storage_client, mb::u64 world_seed) :
    m_job_system(job_system),
    m_storage_client(storage_client),
    m_generator(*this, world_seed)
{
}

world::Chunk *ChunkSystem::chunk_at(const game::ChunkPosition &position)
{
   std::shared_lock lk{m_chunk_mutex};

   auto find_result = m_chunks.find(position.hash());
   if (find_result == m_chunks.end())
      return nullptr;

   return find_result->second.chunk;
}

SubscriptionState ChunkSystem::subscription_state(const game::ChunkPosition &position)
{
   std::shared_lock lk{m_chunk_mutex};

   auto find_result = m_chunks.find(position.hash());
   if (find_result == m_chunks.end())
      return SubscriptionState::Unsubscribed;
   return find_result->second.subscription_state;
}

void ChunkSystem::subscribe_chunk(const game::ChunkPosition &position)
{
   m_storage_client.subscribe_chunk(position);
}

void ChunkSystem::handle_chunk_data(const net::Chunk &chunk)
{
   auto *new_chunk = m_chunk_pool.construct();
   new_chunk->read_net_chunk(chunk);

   {
      std::unique_lock lk{m_chunk_mutex};
      m_chunks.emplace(game::ChunkPosition(chunk.position).hash(),
                       ChunkMeta{SubscriptionState::Subscribed, world::ChunkState::COMPLETE, new_chunk});
   }

   this->on_chunk_is_complete.publish(game::ChunkPosition{chunk.position});
   m_job_system.process_awaiting_tickets();
}

void ChunkSystem::handle_empty_chunk(const game::ChunkPosition &chunk_position)
{
   util::Context ctx;
   m_job_system.create_job<job::GenerateChunk>(ctx, m_generator, chunk_position);
}

world::Chunk *ChunkSystem::create_empty_chunk_at(const game::ChunkPosition &position)
{
   auto *new_chunk = m_chunk_pool.construct(position.x(), position.z(), std::array<short, 256>{});
   {
      std::unique_lock lk{m_chunk_mutex};
      m_chunks.emplace(position.hash(),
                       ChunkMeta{SubscriptionState::Subscribed, world::ChunkState::EMPTY, new_chunk});
   }
   return new_chunk;
}

world::ChunkState ChunkSystem::chunk_state_at(const game::ChunkPosition &position)
{
   std::shared_lock lk{m_chunk_mutex};

   auto find_result = m_chunks.find(position.hash());
   if (find_result == m_chunks.end())
      return world::ChunkState::ABSENT;

   return find_result->second.chunk_state;
}

void ChunkSystem::set_chunk_state_at(const game::ChunkPosition &position, world::ChunkState state)
{
   std::shared_lock lk{m_chunk_mutex};

   auto find_result = m_chunks.find(position.hash());
   if (find_result == m_chunks.end())
      return;

   find_result->second.chunk_state = state;

   if (state == world::COMPLETE) {
      this->on_chunk_is_complete.publish(position);
   }
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

ChunkLoadTicket *ChunkSystem::notify_on_chunk_complete(const game::ChunkPosition &position,
                                                       const ChunkFunc &callback)
{
   return m_ticket_pool.construct(*this, position, callback);
}

void ChunkSystem::release_ticket(ChunkLoadTicket *ticket)
{
   ticket->~ChunkLoadTicket();
   m_ticket_pool.free(ticket);
}

}// namespace minecpp::service::engine