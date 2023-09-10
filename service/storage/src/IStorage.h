#pragma once

#include "minecpp/game/ChunkPosition.h"
#include "minecpp/net/Chunk.schema.h"

#include <optional>

namespace minecpp::service::storage {

class IStorage
{
 public:
   virtual ~IStorage() noexcept = default;

   virtual bool write_chunk(const net::Chunk &chunk)                                 = 0;
   virtual std::optional<net::Chunk> read_chunk(game::ChunkPosition position)        = 0;
   virtual bool update_chunk(game::ChunkPosition position,
                             const std::function<void(net::Chunk &chunk)> &callback) = 0;

   virtual bool add_chunk_subscription(game::ChunkPosition position, std::uint64_t client_id) = 0;
};

}// namespace minecpp::service::storage
