#include "ChunkSerializer.h"
#include "minecpp/world/Chunk.h"

namespace minecpp::service::engine {

ChunkSerializer::ChunkSerializer(const world::Chunk &chunk) :
   m_chunk{chunk}
{
}

void ChunkSerializer::write_light_data(const net::play::cb::UpdateLight &update_light, int min_section, int max_section)
{
}

}
