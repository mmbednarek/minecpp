#include "chunk.h"
#include <game/chunk/utils.h>
#include <nbt/writer.h>
#include <sstream>

namespace MineNet::Message {

constexpr int air_global_id = 0;

static int get_air_id(const minecpp::chunk::NetChunk::Section &sec) {
   for (int id = 0; auto item : sec.palette()) {
      if (item == air_global_id) {
         return id;
      }
      ++id;
   }
   return -1;
}

void write_chunk(Writer &w, const minecpp::chunk::NetChunk &chunk) {
   w.write_big_endian(chunk.pos_x());
   w.write_big_endian(chunk.pos_z());
   w.write_byte(chunk.full());

   w.write_varint(({
      uint32_t available_sections = 0;
      for (const auto &sec : chunk.sections()) {
         available_sections |= 1u << (uint32_t)sec.y();
      }
      available_sections;
   }));

   NBT::Writer height_maps(w.raw_stream());
   height_maps.begin_compound("");
   {
      auto mb = chunk.hm_motion_blocking();
      height_maps.write_long_array("MOTION_BLOCKING", mb.data(), mb.size());
      auto ws = chunk.hm_world_surface();
      height_maps.write_long_array("WORLD_SURFACE", ws.data(), ws.size());
   }
   height_maps.end_compound();

   for (const auto &sec : chunk.sections()) {
      w.write_varint(Game::calculate_ref_count(
          get_air_id(sec), sec.data().data(), sec.data_size()));

      // write palette
      w.write_varint(sec.palette_size());
      for (auto item : sec.palette()) {
         w.write_varint(item);
      }

      // write data
      w.write_big_endian_array(sec.data().data(), sec.data_size());
   }

   // tile entities, left for now
   w.write_big_endian<short>(0);
}

} // namespace MineNet::Message
