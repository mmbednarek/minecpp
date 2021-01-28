#pragma once
#include <minecpp/game/chunk/chunk.h>

namespace minecpp::game {

enum ChunkState {
   ABSENT = 0,
   TERRAIN = 1,
   COMPLETE = 2,
};

class Chunks {
 public:
   virtual game::Chunk &get_incomplete_chunk(int x, int z) = 0;
   virtual result<empty> put_chunk(int x, int z, std::unique_ptr<game::Chunk> chunk) = 0;
   virtual result<ChunkState> get_chunk_state(int x, int z) = 0;
};

}// namespace minecpp::game