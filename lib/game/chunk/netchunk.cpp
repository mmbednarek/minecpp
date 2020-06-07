#include "netchunk.h"
#include <game/chunk/utils.h>
#include <game/items/registry.h>
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
            uint8_t y = 0xFF;
            int ref_count = 0;
            std::vector<long long> data;
            std::vector<int> palette;
            r.read_compound([&y, &data, &palette,
                             &ref_count](NBT::Reader &r, NBT::TagID tag_id,
                                         const std::string &name) {
               if (name == "Y" && tag_id == NBT::Byte) {
                  y = r.read_payload<NBT::Byte>();
                  return;
               }
               if (name == "BlockStates" && tag_id == NBT::LongArray) {
                  data = r.read_payload<NBT::LongArray>();
                  return;
               }
               if (name == "Palette" && tag_id == NBT::List) {
                  r.read_list([&palette](NBT::Reader &r) {
                     palette.emplace_back(PaletteItem(r).to_state_id());
                  });
                  return;
               }
               r.skip_payload(tag_id);
            });
            if (y < 16) {
               sections[y] = NetSection{
                   .bits = static_cast<uint8_t>(data.size() * 64 / 4096),
                   .ref_count = Game::calculate_ref_count(data, palette),
                   .palette = palette,
                   .data = data,
               };
            }
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
   }
}

} // namespace Game
