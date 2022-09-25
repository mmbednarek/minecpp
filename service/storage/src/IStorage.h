#pragma once
#include <minecpp/game/Game.h>
#include <minecpp/proto/chunk/v1/Chunk.pb.h>
#include <minecpp/proto/service/storage/v1/Storage.pb.h>
#include <optional>

namespace minecpp::service::storage {

namespace proto_chunk = proto::chunk::v1;
namespace proto_storage = proto::service::storage::v1;

class IStorage
{
 public:
   virtual ~IStorage() noexcept = default;

   virtual bool write_chunk(const proto_chunk::Chunk &chunk)                                 = 0;
   virtual std::optional<proto_chunk::Chunk> read_chunk(game::ChunkPosition position)        = 0;
   virtual bool update_chunk(game::ChunkPosition position,
                             const std::function<void(proto_chunk::Chunk &chunk)> &callback) = 0;

   virtual bool add_chunk_subscription(game::ChunkPosition position, const proto_storage::ClientId &client_id) = 0;
};

}// namespace minecpp::service::storage
