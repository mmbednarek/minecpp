#pragma once

#include "minecpp/net/play/Clientbound.schema.h"

namespace minecpp::world {
class Chunk;
}

namespace minecpp::service::engine {

class ChunkSerializer {
 public:
   explicit ChunkSerializer(const world::Chunk &chunk);

   void write_light_data(const net::play::cb::UpdateLight &update_light, int min_section, int max_section);

  private:
   [[maybe_unused]] const world::Chunk &m_chunk;
};

}