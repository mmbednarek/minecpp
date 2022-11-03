#pragma once
#include <minecpp/game/Game.h>
#include <minecpp/service/storage/Storage.h>
#include <minecpp/util/Pool.h>
#include <minecpp/world/Chunk.h>

namespace minecpp::service::engine {

class JobSystem;

enum class SubscriptionState
{
   Unsubscribed,
   SubscriptionIssued,
   Subscribed,
};

struct ChunkMeta
{
   SubscriptionState state;
   world::Chunk *chunk;
};

class ChunkSystem : public storage::IResponseHandler
{
 public:
   ChunkSystem(JobSystem &job_system, storage::StorageClient &storage_client);

   [[nodiscard]] world::Chunk *chunk_at(const game::ChunkPosition &position);
   SubscriptionState chunk_state(const game::ChunkPosition &position);
   void subscribe_chunk(const game::ChunkPosition &position);
   void handle_chunk_data(const storage::ResponseChunkData &chunk) override;

 private:
   JobSystem &m_job_system;
   std::map<game::ChunkHash, ChunkMeta> m_chunks;
   util::AtomicPool<world::Chunk> m_chunk_pool;
   storage::StorageClient &m_storage_client;
};

}// namespace minecpp::service::engine
