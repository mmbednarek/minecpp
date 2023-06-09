#pragma once

#include "minecpp/proto/service/storage/v1/Storage.pb.h"
#include "minecpp/util/Pool.h"
#include "minecpp/world/Chunk.h"
#include "minecpp/world/Generator.h"
#include "minecpp/world/IChunkSystem.h"

namespace minecpp::service::storage {

class StorageClient;

}

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
   SubscriptionState subscription_state;
   world::ChunkState chunk_state;
   world::Chunk *chunk;
};

class ChunkSystem : public world::IChunkSystem
{
 public:
   ChunkSystem(JobSystem &job_system, storage::StorageClient &storage_client, mb::u64 world_seed);

   SubscriptionState subscription_state(const game::ChunkPosition &position);
   void subscribe_chunk(const game::ChunkPosition &position);
   world::ChunkState chunk_state_at(const game::ChunkPosition &position) override;

   [[nodiscard]] world::Chunk *chunk_at(const game::ChunkPosition &position) override;
   world::Chunk *create_chunk_with_terrain_at(const game::ChunkPosition &position) override;
   world::Chunk *create_empty_chunk_at(const game::ChunkPosition &position) override;
   void set_chunk_state_at(const game::ChunkPosition &position, world::ChunkState state) override;

   void handle_chunk_data(const proto::service::storage::v1::ResponseChunkData &chunk);
   void handle_empty_chunk(const proto::service::storage::v1::ResponseEmptyChunk &chunk);

   void save_chunk_at(const game::ChunkPosition &position) override;

 private:
   JobSystem &m_job_system;
   std::map<game::ChunkHash, ChunkMeta> m_chunks;
   util::AtomicPool<world::Chunk> m_chunk_pool;
   storage::StorageClient &m_storage_client;
   world::Generator m_generator;
   std::shared_mutex m_chunk_mutex;
};

}// namespace minecpp::service::engine
