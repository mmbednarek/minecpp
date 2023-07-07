#pragma once
#include <minecpp/game/ChunkPosition.h>
#include <minecpp/proto/chunk/Chunk.pb.h>
#include <minecpp/proto/service/storage/Storage.pb.h>
#include <optional>

namespace minecpp::service::storage {

namespace proto_chunk   = proto::chunk;
namespace proto_storage = proto::service::storage;

class IStorage
{
 public:
   virtual ~IStorage() noexcept = default;

   virtual bool write_chunk(const proto_chunk::Chunk &chunk)                                 = 0;
   virtual std::optional<proto_chunk::Chunk> read_chunk(game::ChunkPosition position)        = 0;
   virtual bool update_chunk(game::ChunkPosition position,
                             const std::function<void(proto_chunk::Chunk &chunk)> &callback) = 0;

   virtual bool add_chunk_subscription(game::ChunkPosition position,
                                       const proto_storage::ClientId &client_id) = 0;
};

}// namespace minecpp::service::storage
