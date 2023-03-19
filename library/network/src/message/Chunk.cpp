#include <minecpp/nbt/Writer.h>
#include <minecpp/network/message/Chunk.h>
#include <minecpp/util/Packed.h>
#include <minecpp/world/Section.h>
#include <spdlog/spdlog.h>

namespace minecpp::network::message {

using minecpp::proto::chunk::v1::Chunk;

Writer get_chunk_data(const Chunk &chunk);
void write_light_data(Writer &w, const Chunk &chunk);

void write_chunk(Writer &w, const Chunk &chunk)
{
   // chunk position
   w.write_big_endian(chunk.position().x());
   w.write_big_endian(chunk.position().z());

   // write height maps
   nbt::Writer height_maps(w.raw_stream());
   height_maps.begin_compound("");
   {
      const auto &mb = chunk.hm_motion_blocking();
      height_maps.write_long_array("MOTION_BLOCKING", mb.data(), static_cast<std::size_t>(mb.size()));
      const auto &ws = chunk.hm_world_surface();
      height_maps.write_long_array("WORLD_SURFACE", ws.data(), static_cast<std::size_t>(ws.size()));
   }
   height_maps.end_compound();

   auto chunk_data_writer = get_chunk_data(chunk);
   w.write_varint(static_cast<std::uint32_t>(chunk_data_writer.peek_size()));
   w.write_from(chunk_data_writer);

   // tile entity, left for now
   w.write_varint(0);

   write_light_data(w, chunk);
}

void write_light(Writer &w, const Chunk &chunk)
{
   w.write_varint(static_cast<std::uint32_t>(chunk.position().x()));
   w.write_varint(static_cast<std::uint32_t>(chunk.position().z()));
   write_light_data(w, chunk);
}

void write_light_data(Writer &w, const Chunk &chunk)
{
   uint32_t sky_light_count   = 0;
   uint32_t block_light_count = 0;

   uint32_t sky_update_mask   = 0;
   uint32_t block_update_mask = 0;
   uint32_t sky_reset_mask    = 0;
   uint32_t block_reset_mask  = 0;

   for (auto const &sec : chunk.sections()) {
      auto place = static_cast<char>(sec.y()) + 1;
      if (sec.sky_light().empty()) {
         sky_reset_mask |= 1u << place;
      } else {
         ++sky_light_count;
         sky_update_mask |= 1u << place;
      }
      if (sec.block_light().empty()) {
         block_reset_mask |= 1u << place;
      } else {
         ++block_light_count;
         block_update_mask |= 1u << place;
      }
   }

   w.write_byte(1);// Trust edges
   w.write_varint(1);
   w.write_long(sky_update_mask);
   w.write_varint(1);
   w.write_long(block_update_mask);
   w.write_varint(1);
   w.write_long(sky_reset_mask);
   w.write_varint(1);
   w.write_long(block_reset_mask);

   w.write_varint(sky_light_count);

   for (auto const &sec : chunk.sections()) {
      if (!sec.sky_light().empty()) {
         if (sec.sky_light().size() != 2048) {
            spdlog::error("shiitt");
         }
         w.write_varint(static_cast<std::uint32_t>(sec.sky_light().size()));
         w.write_bytes(sec.sky_light().data(), sec.sky_light().size());
      }
   }

   w.write_varint(block_light_count);

   for (auto const &sec : chunk.sections()) {
      if (!sec.block_light().empty()) {
         if (sec.block_light().size() != 2048) {
            spdlog::error("shiitt");
         }
         w.write_varint(static_cast<std::uint32_t>(sec.block_light().size()));
         w.write_bytes(sec.block_light().data(), sec.block_light().size());
      }
   }
}

Writer get_chunk_data(const Chunk &chunk)
{
   Writer chunk_data_writer;
   int index = 0;
   for (const auto &sec : chunk.sections()) {
      auto section = world::Section::from_proto(sec);

      chunk_data_writer.write_big_endian<short>(static_cast<short>(sec.ref_count()));

      if (section.data().indices().raw().empty()) {
         section.data().set(4095, 0);
      }

      if (section.data().indices().bits() <= 4) {
         section.data().indices().set_bits(5);
      }

      // write palette
      chunk_data_writer.write_byte(static_cast<uint8_t>(section.data().indices().bits()));
      chunk_data_writer.write_varint(static_cast<uint32_t>(section.data().palette().size()));
      for (auto item : section.data().palette()) {
         chunk_data_writer.write_varint(static_cast<uint32_t>(item));
      }


      // write data
      chunk_data_writer.write_big_endian_array(section.data().indices().raw().data(),
                                               static_cast<size_t>(section.data().indices().raw().size()));

      // write biomes
      chunk_data_writer.write_byte(6);// ignore palette

      auto biome_data = util::generate_packed(
              6, 64, [it = chunk.biomes().begin(), end = chunk.biomes().end()]() mutable {
                 if (it == end)
                    return 0;
                 return *(it++);
              });

      // write data
      chunk_data_writer.write_big_endian_array(biome_data.data(), biome_data.size());

      ++index;
   }

   for (int i = index; i < 16; ++i) {
      chunk_data_writer.write_big_endian<short>(0);

      // TODO: Abstract palatalized containers

      // write palette
      chunk_data_writer.write_byte(0);
      chunk_data_writer.write_varint(0);// AIR

      // write data
      chunk_data_writer.write_big_endian_array<uint64_t>(nullptr, 0);

      // write biomes
      chunk_data_writer.write_byte(0);  // ignore palette
      chunk_data_writer.write_varint(1);// default biome

      chunk_data_writer.write_big_endian_array<uint64_t>(nullptr, 0);
   }

   return chunk_data_writer;
}

}// namespace minecpp::network::message
