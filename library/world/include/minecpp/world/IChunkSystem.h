#pragma once
#include "Chunk.h"
#include <mb/result.h>

namespace minecpp::world {

enum ChunkState
{
   ABSENT   = 0,
   EMPTY    = 1,
   TERRAIN  = 2,
   COMPLETE = 3,
};

class IChunkSystem
{
 public:
   virtual ~IChunkSystem() noexcept = default;

   [[nodiscard]] virtual Chunk *create_empty_chunk_at(const game::ChunkPosition &position)        = 0;
   [[nodiscard]] virtual Chunk *create_chunk_with_terrain_at(const game::ChunkPosition &position) = 0;
   [[nodiscard]] virtual Chunk *chunk_at(const game::ChunkPosition &position)                     = 0;
   [[nodiscard]] virtual ChunkState chunk_state_at(const game::ChunkPosition &position)           = 0;
   virtual void set_chunk_state_at(const game::ChunkPosition &position, ChunkState state)         = 0;
   virtual void save_chunk_at(const game::ChunkPosition &position)                                = 0;
};

}// namespace minecpp::world