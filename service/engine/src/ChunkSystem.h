#pragma once

#include "minecpp/net/Chunk.schema.h"
#include "minecpp/signal/Delegate.hpp"
#include "minecpp/util/Pool.h"
#include "minecpp/world/Chunk.h"
#include "minecpp/world/Generator.h"
#include "minecpp/world/IChunkSystem.h"

namespace minecpp::service::storage {

class StorageClient;

}

namespace minecpp::service::engine {

class JobSystem;
class ChunkSystem;

enum class SubscriptionState
{
   Unsubscribed,
   SubscriptionIssued,
   Subscribed,
};

struct ChunkMeta
{
   SubscriptionState subscription_state;
   world::ChunkState chunk_state;
   world::Chunk *chunk;
};

using ChunkIsCompleteDel = signal::Delegate<game::ChunkPosition>;
using ChunkFunc          = std::function<void(world::Chunk *chunk)>;

class ChunkLoadTicket
{
 public:
   ChunkLoadTicket(ChunkSystem &chunk_system, game::ChunkPosition position, ChunkFunc callback);

   void on_chunk_is_complete(game::ChunkPosition position);

 private:
   ChunkFunc m_callback;
   game::ChunkPosition m_position;
   ChunkIsCompleteDel::OptSink<ChunkLoadTicket> m_sink;
   ChunkSystem &m_chunk_system;
   int m_call_count{};
   std::mutex m_mtx;
};

class ChunkSystem : public world::IChunkSystem
{
   friend ChunkLoadTicket;

 public:
   ChunkIsCompleteDel on_chunk_is_complete;

   ChunkSystem(JobSystem &job_system, storage::StorageClient &storage_client, mb::u64 world_seed);

   SubscriptionState subscription_state(const game::ChunkPosition &position);
   void subscribe_chunk(const game::ChunkPosition &position);
   world::ChunkState chunk_state_at(const game::ChunkPosition &position) override;

   [[nodiscard]] world::Chunk *chunk_at(const game::ChunkPosition &position) override;
   world::Chunk *create_chunk_with_terrain_at(const game::ChunkPosition &position) override;
   world::Chunk *create_empty_chunk_at(const game::ChunkPosition &position) override;
   void set_chunk_state_at(const game::ChunkPosition &position, world::ChunkState state) override;

   void handle_chunk_data(const net::Chunk &chunk);
   void handle_empty_chunk(const game::ChunkPosition &chunk_position);

   void save_chunk_at(const game::ChunkPosition &position) override;

   void access_chunk(const game::ChunkPosition &position, ChunkFunc &&function)
   {
      if (this->chunk_state_at(position) == world::ChunkState::COMPLETE) {
         function(this->chunk_at(position));
      } else {
         this->notify_on_chunk_complete(position, std::move(function));
         this->subscribe_chunk(position);
      }
   }

 private:
   ChunkLoadTicket *notify_on_chunk_complete(const game::ChunkPosition &position, const ChunkFunc &callback);
   void release_ticket(ChunkLoadTicket *ticket);

   JobSystem &m_job_system;
   std::map<game::ChunkHash, ChunkMeta> m_chunks;
   util::AtomicPool<world::Chunk> m_chunk_pool;
   util::AtomicPool<ChunkLoadTicket> m_ticket_pool;
   storage::StorageClient &m_storage_client;
   world::Generator m_generator;
   std::shared_mutex m_chunk_mutex;
};

}// namespace minecpp::service::engine
