#pragma once

#include "minecpp/container/PalettedVector.h"
#include "minecpp/game/Light.h"
#include "minecpp/net/play/Clientbound.schema.h"

namespace minecpp::world {
class Chunk;
class Section;

class ChunkSerializer
{
 public:
   explicit ChunkSerializer(Chunk &chunk);

   void write_update_light(net::play::cb::UpdateLight &update_light, game::LightType light_type,
                           int min_section, int max_section) const;
   void write_light_data(net::LightData &light_data, game::LightType light_type, int min_section,
                         int max_section) const;

   void write_chunk_data(net::ChunkData &out_chunk_data) const;
   void write_chunk(net::Chunk &out_chunk) const;

 private:
   void write_section(net::Section &out_section, const Section &in_section) const;
   void write_empty_section(net::Section &out_section) const;
   void write_paletted_data(net::PalettedContainer &out_paletted_data,
                            const container::PalettedVector<game::BlockStateId, 9> &in_vector) const;
   void write_empty_section(net::PalettedContainer &out_paletted_data) const;

   [[maybe_unused]] Chunk &m_chunk;
};

}// namespace minecpp::world