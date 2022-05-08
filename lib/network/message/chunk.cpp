#include <minecpp/game/chunk/utils.h>
#include <minecpp/nbt/writer.h>
#include <minecpp/network/message/chunk.h>
#include <minecpp/util/packed.h>

namespace minecpp::network::message {

using minecpp::proto::chunk::v1::Chunk;

Writer get_chunk_data(const Chunk &chunk);
void write_light_data(Writer &w, const Chunk &chunk);

void write_chunk(Writer &w, const Chunk &chunk) {
   // chunk position
   w.write_big_endian(chunk.pos_x());
   w.write_big_endian(chunk.pos_z());

   // write height maps
   nbt::Writer height_maps(w.raw_stream());
   height_maps.begin_compound("");
   {
      auto mb = chunk.hm_motion_blocking();
      height_maps.write_long_array("MOTION_BLOCKING", mb.data(), mb.size());
      auto ws = chunk.hm_world_surface();
      height_maps.write_long_array("WORLD_SURFACE", ws.data(), ws.size());
   }
   height_maps.end_compound();

   auto chunk_data_writer = get_chunk_data(chunk);
   w.write_varint(chunk_data_writer.peek_size());
   w.write_from(chunk_data_writer);

   // tile entity, left for now
   w.write_varint(0);

   write_light_data(w, chunk);
}

void write_light(Writer &w, const Chunk &chunk) {
   w.write_varint(chunk.pos_x());
   w.write_varint(chunk.pos_z());
   write_light_data(w, chunk);
}

void write_light_data(Writer &w, const Chunk &chunk) {
   uint32_t sky_light_count = 0;
   uint32_t block_light_count = 0;

   uint32_t skyUpdateMask = 0;
   uint32_t blockUpdateMask = 0;
   uint32_t skyResetMask = 0;
   uint32_t blockResetMask = 0;

   for (auto const &sec : chunk.sections()) {
      uint8_t place = static_cast<char>(sec.y()) + 1;
      if (sec.sky_light().empty()) {
         skyResetMask |= 1u << place;
      } else {
         ++sky_light_count;
         skyUpdateMask |= 1u << place;
      }
      if (sec.block_light().empty()) {
         blockResetMask |= 1u << place;
      } else {
         ++block_light_count;
         blockUpdateMask |= 1u << place;
      }
   }

   w.write_byte(1);// Trust edges
   w.write_varint(1);
   w.write_long(skyUpdateMask);
   w.write_varint(1);
   w.write_long(blockUpdateMask);
   w.write_varint(1);
   w.write_long(skyResetMask);
   w.write_varint(1);
   w.write_long(blockResetMask);

   w.write_varint(sky_light_count);

   for (auto const &sec : chunk.sections()) {
      if (!sec.sky_light().empty()) {
         w.write_varint(sec.sky_light().size());
         w.write_bytes(sec.sky_light().data(), sec.sky_light().size());
      }
   }

   w.write_varint(block_light_count);

   for (auto const &sec : chunk.sections()) {
      if (!sec.block_light().empty()) {
         w.write_varint(sec.block_light().size());
         w.write_bytes(sec.block_light().data(), sec.block_light().size());
      }
   }
}

Writer get_chunk_data(const Chunk &chunk) {
   Writer chunk_data_writer;
   int index = 0;
   for (const auto &sec : chunk.sections()) {
      chunk_data_writer.write_big_endian<short>(sec.ref_count());

      // write palette
      chunk_data_writer.write_byte(sec.bits());
      chunk_data_writer.write_varint(sec.palette_size());
      for (auto item : sec.palette()) {
         chunk_data_writer.write_varint(item);
      }

      // write data
      chunk_data_writer.write_big_endian_array(sec.data().data(), sec.data_size());

      // write biomes
      chunk_data_writer.write_byte(6); // ignore palette

      auto biome_data = util::generate_packed(6, 64, [it = chunk.biomes().begin(), end = chunk.biomes().end()]() mutable {
        if (it == end)
           return 0;
        return *(it++);
      });

      // write data
      chunk_data_writer.write_big_endian_array(biome_data.data(), biome_data.size());

      ++index;
   }

   for (int i = index; i < 16; ++i)  {
      chunk_data_writer.write_big_endian<short>(0);

      // TODO: Abstract palatalized containers

      // write palette
      chunk_data_writer.write_byte(0);
      chunk_data_writer.write_varint(0); // AIR

      // write data
      chunk_data_writer.write_big_endian_array<uint64_t>(nullptr, 0);

      // write biomes
      chunk_data_writer.write_byte(0); // ignore palette
      chunk_data_writer.write_varint(0); // default biome

      chunk_data_writer.write_big_endian_array<uint64_t>(nullptr, 0);
   }

   return chunk_data_writer;
}

}// namespace minecpp::network::message
