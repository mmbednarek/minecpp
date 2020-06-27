#include "netchunk.h"
#include <game/chunk/utils.h>
#include <game/items/registry.h>
#include <mineutils/packed.h>
#include <stdexcept>
#include <vector>

namespace Game {

inline int expected_data_version = 2230;

NetChunk::NetChunk(NBT::Reader &r) {
   r.read_compound([this](NBT::Reader &r, NBT::TagID tagid,
                          const std::string &name) { load(r, tagid, name); });
}

void NetChunk::load(NBT::Reader &r, NBT::TagID tagid, const std::string &name) {
   switch (tagid) {
   case NBT::String:
      if (name == "Status") {
         if (auto status = r.read_payload<NBT::String>(); status == "full") {
            full = true;
         }
         return;
      }

      r.skip_payload(NBT::String);
      return;
   case NBT::Int:
      if (name == "xPos") {
         pos_x = r.read_payload<NBT::Int>();
         return;
      }
      if (name == "zPos") {
         pos_z = r.read_payload<NBT::Int>();
         return;
      }
      r.skip_payload(NBT::Int);
      return;
   case NBT::Compound:
      if (name == "Heightmaps") {
         r.read_compound(
             [this](NBT::Reader &r, NBT::TagID tagid, const std::string &name) {
                if (tagid != NBT::LongArray)
                   throw std::runtime_error(
                       "height map expected to be a long array");

                if (name == "MOTION_BLOCKING") {
                   hm_motion_blocking = r.read_long_array<36>();
                   return;
                }
                if (name == "WORLD_SURFACE") {
                   hm_world_surface = r.read_long_array<36>();
                   return;
                }

                r.skip_payload(tagid);
             });
         return;
      }
      r.skip_payload(tagid);
      return;
   case NBT::IntArray:
      if (name == "Biomes") {
         biomes = r.read_int_array<1024>();
         return;
      }
      r.skip_payload(NBT::IntArray);
      return;
   case NBT::List:
      if (name == "Sections") {
         r.read_list([this](NBT::Reader &r) {
            int8_t y = 0;
            std::vector<long long> data;
            std::vector<uint8_t> block_light;
            std::vector<uint8_t> sky_light;
            std::vector<int> palette;
            r.read_compound([&y, &data, &palette, &block_light,
                             &sky_light](NBT::Reader &r, NBT::TagID tag_id,
                                         const std::string &name) {
               if (tag_id == NBT::Byte && name == "Y") {
                  y = r.read_payload<NBT::Byte>();
                  return;
               }
               if (tag_id == NBT::ByteArray) {
                  if (name == "BlockLight") {
                     block_light = r.read_payload<NBT::ByteArray>();
                     return;
                  }
                  if (name == "SkyLight") {
                     sky_light = r.read_payload<NBT::ByteArray>();
                     return;
                  }
               }
               if (tag_id == NBT::LongArray && name == "BlockStates") {
                  data = r.read_payload<NBT::LongArray>();
                  return;
               }
               if (tag_id == NBT::List && name == "Palette") {
                  r.read_list([&palette](NBT::Reader &r) {
                     palette.emplace_back(PaletteItem(r).to_state_id());
                  });
                  return;
               }
               r.skip_payload(tag_id);
            });

            uint8_t bits = data.size() * 64 / 4096;
            int ref_count = Game::calculate_ref_count(data, palette);

            sections[y] = NetSection{
                .bits = bits,
                .ref_count = ref_count,
                .palette = std::move(palette),
                .data = std::move(data),
                .block_light = std::move(block_light),
                .sky_light = std::move(sky_light),
            };
         });
         return;
      }
      r.skip_payload(NBT::List);
      return;
   case NBT::Long:
      r.skip_payload(NBT::Long);
      return;
   case NBT::Byte:
      r.skip_payload(NBT::Byte);
      return;
   default:
      throw std::runtime_error("invalid tag");
   }
}

void NetChunk::as_proto(minecpp::chunk::NetChunk *chunk) {
   chunk->set_pos_x(pos_x);
   chunk->set_pos_z(pos_z);
   chunk->set_full(full);
   if (full) {
      *chunk->mutable_biomes() = {biomes.begin(), biomes.end()};
   }
   *chunk->mutable_hm_motion_blocking() = {hm_motion_blocking.begin(),
                                           hm_motion_blocking.end()};

   *chunk->mutable_hm_world_surface() = {hm_world_surface.begin(),
                                         hm_world_surface.end()};

   for (auto const &sec : sections) {
      auto *out_sec = chunk->add_sections();
      out_sec->set_y(sec.first);
      out_sec->set_bits(sec.second.bits);
      out_sec->set_ref_count(sec.second.ref_count);
      *out_sec->mutable_palette() = {sec.second.palette.begin(),
                                     sec.second.palette.end()};
      *out_sec->mutable_data() = {sec.second.data.begin(),
                                  sec.second.data.end()};
      *out_sec->mutable_block_light() = {sec.second.block_light.begin(),
                                         sec.second.block_light.end()};
      *out_sec->mutable_sky_light() = {sec.second.sky_light.begin(),
                                       sec.second.sky_light.end()};
   }
}

constexpr uint32_t coord_to_offset(int x, int y, int z) {
   return (y & 15) * 16 * 16 + (z & 15) * 16 + (x & 15);
}

void NetChunk::create_empty_section(int8_t sec) {
   Game::NetSection section;
   section.bits = 4; // start with 4 bits
   section.data = std::vector<long long>(4096 * 4 / 64);
   section.ref_count = 4096;
   section.palette.emplace_back(0);
   sections[sec] = std::move(section);
}

void NetChunk::set_block(int x, int y, int z, uint32_t state) {
   int8_t sec = y / 16;
   auto iter = sections.find(sec);
   if (iter == sections.end()) {
      create_empty_section(sec);
      iter = sections.find(sec);
   }

   auto &section = iter->second;
   auto index =
       std::find(section.palette.begin(), section.palette.end(), state);
   int value;
   if (index == section.palette.end()) {
      value = section.palette.size();
      section.palette.emplace_back(state);
      if (value >= section.bits) {
         Utils::resize_pack(section.data, section.bits, section.bits + 1);
         ++section.bits;
      }
   } else {
      value = *index;
   }

   Utils::set_packed(section.data, section.bits, coord_to_offset(x, y, z),
                     value);

   set_block_light(x, y, z, 15);
   set_sky_light(x, y, z, 15);
}

uint8_t NetChunk::get_block_light(int x, int y, int z) {
   int8_t sec = y / 16;
   auto iter = sections.find(sec);
   if (iter == sections.end()) {
      return 0;
   }

   if (iter->second.block_light.empty()) {
      return 0;
   }

   auto index = coord_to_offset(x, y, z);

   if (index % 2 == 0) {
      return iter->second.block_light[index / 2] & 15;
   } else {
      return iter->second.block_light[index / 2] >> 4;
   }
}

static void set_light_value(std::vector<uint8_t> &light, int x, int y, int z,
                            uint8_t value) {
   if (light.empty()) {
      return;
   }

   int index = coord_to_offset(x, y, z);

   auto pack = light[index / 2];
   if (index % 2 == 0) {
      pack &= 240;
      pack |= value & 15;
   } else {
      pack &= 15;
      pack |= (value & 15) << 4;
   }
   light[index / 2] = pack;
}

void NetChunk::set_block_light(int x, int y, int z, uint8_t value) {
   int8_t sec = y / 16;
   auto iter = sections.find(sec);
   if (iter == sections.end()) {
      return;
   }
   set_light_value(iter->second.block_light, x, y, z, value);
}

void NetChunk::set_sky_light(int x, int y, int z, uint8_t value) {
   int8_t sec = y / 16;
   auto iter = sections.find(sec);
   if (iter == sections.end()) {
      return;
   }
   set_light_value(iter->second.sky_light, x, y, z, value);
}

} // namespace Game
