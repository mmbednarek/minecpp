#pragma once
#include "Chunk.h"
#include <mb/result.h>

namespace minecpp::world {

enum ChunkState
{
   ABSENT   = 0,
   TERRAIN  = 1,
   COMPLETE = 2,
};

class Chunks
{
 public:
   virtual ~Chunks() noexcept = default;

   virtual Chunk &get_incomplete_chunk(int x, int z)                                   = 0;
   virtual mb::result<mb::empty> put_chunk(int x, int z, std::unique_ptr<Chunk> chunk) = 0;
   virtual mb::result<ChunkState> get_chunk_state(int x, int z)                        = 0;
};

}// namespace minecpp::world