#include "chunk.h"
#include <game/chunk/utils.h>
#include <nbt/writer.h>
#include <sstream>

namespace MineNet::Message {

constexpr int air_global_id = 0;

void write_chunk(Writer &w, const minecpp::chunk::NetChunk &chunk) {
   w.write_big_endian(chunk.pos_x());
   w.write_big_endian(chunk.pos_z());
   w.write_byte(chunk.full());

   size_t buff_size = 0;

   uint32_t available_sections = 0;
   for (const auto &sec : chunk.sections()) {
      if (sec.data_size() > 0) {
         available_sections |= 1u << (uint32_t)sec.y();
         buff_size += sizeof(short) + 1 + w.len_varint(sec.palette_size());
         for (auto item : sec.palette()) {
            buff_size += w.len_varint(item);
         }
         buff_size += w.len_varint(sec.data_size()) + sec.data_size() * 8;
      }
   }
   w.write_varint(available_sections);

   NBT::Writer height_maps(w.raw_stream());
   height_maps.begin_compound("");
   {
      auto mb = chunk.hm_motion_blocking();
      height_maps.write_long_array("MOTION_BLOCKING", mb.data(), mb.size());
      auto ws = chunk.hm_world_surface();
      height_maps.write_long_array("WORLD_SURFACE", ws.data(), ws.size());
   }
   height_maps.end_compound();

   for (auto biome : chunk.biomes()) {
      w.write_big_endian(biome);
   }

   w.write_varint(buff_size);

   for (const auto &sec : chunk.sections()) {
      if (sec.data_size() == 0) {
         continue;
      }

      w.write_big_endian<short>(sec.ref_count());
      w.write_byte(sec.bits());

      // write palette
      w.write_varint(sec.palette_size());
      for (auto item : sec.palette()) {
         w.write_varint(item);
      }

      // write data
      w.write_big_endian_array(sec.data().data(), sec.data_size());
   }

   // tile entities, left for now
   w.write_varint(0);
}

} // namespace MineNet::Message
