#include "chunk.h"
#include <stdexcept>
#include <vector>

namespace Game {

inline int expected_data_version = 2230;

Chunk::Chunk(NBT::Reader &r) {
   r.read_compound([this](NBT::Reader &r, NBT::TagID tagid,
                          const std::string &name) { load(r, tagid, name); });
}

void Chunk::load(NBT::Reader &r, NBT::TagID tagid, const std::string &name) {
   switch (tagid) {
   case NBT::String:
      if (name == "Status") {
         status = r.read_payload<NBT::String>();
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
                auto map = read_height_map(r, tagid);
                if (name == "MOTION_BLOCKING") {
                   hm_motion_blocking = map;
                   return;
                }
                if (name == "MOTION_BLOCKING_NO_LEAVES") {
                   hm_motion_blocking_no_leaves = map;
                   return;
                }
                if (name == "OCEAN_FLOOR") {
                   hm_motion_ocean_floor = map;
                   return;
                }
                if (name == "WORLD_SURFACE") {
                   hm_world_surface = map;
                   return;
                }

                throw std::runtime_error(
                    Utils::format("unknown height map {}", name));
             });
         return;
      }
      r.skip_payload(tagid);
      return;
   case NBT::IntArray:
      if (name == "Biomes") {
         biomes = r.read_payload<NBT::IntArray>();
         return;
      }
      r.skip_payload(NBT::IntArray);
      return;
   case NBT::List:
      if (name == "Sections") {
         r.read_list([this](NBT::Reader &r) {
            auto section = Section(r);
            sections[section.y] = section;
         });
         return;
      }
      if (name == "Entities") {
         // TODO: Read entities
         r.skip_payload(NBT::List);
         return;
      }
      if (name == "LiquidTicks") {
         // TODO: Read liquid ticks
         r.skip_payload(NBT::List);
         return;
      }
      if (name == "PostProcessing") {
         // TODO: Read post processing
         r.skip_payload(NBT::List);
         return;
      }
      r.skip_payload(NBT::List);
      return;
   case NBT::Long:
      if (name == "InhabitedTime") {
         inhabited_time = r.read_payload<NBT::Long>();
         return;
      }
      if (name == "LastUpdate") {
         last_update = r.read_payload<NBT::Long>();
         return;
      }
      r.skip_payload(NBT::Long);
      return;
   case NBT::Byte:
      if (name == "isLightOn") {
         light_on = r.read_payload<NBT::Byte>();
         return;
      }
      r.skip_payload(NBT::Byte);
      return;
   default:
      throw std::runtime_error("invalid tag");
   }
}

Chunk::HeightMap Chunk::read_height_map(NBT::Reader &r, NBT::TagID type) {
   if (type != NBT::LongArray) [[unlikely]] {
      throw std::runtime_error("height map must be long array type");
   }

   int size = r.read_payload<NBT::Int>();
   if (size != 36) [[unlikely]] {
      throw std::runtime_error("height map's length must be 36");
   }

   HeightMap result;
   r.read_packed_ints(result, 9, 36);
   return result;
}

std::string_view Chunk::block_at(int x, int y, int z) {
   auto& s = sections[y / 16];
   if (s.empty()) {
      return "minecraft:air";
   }
   return s.block_at(x, y % 16, z);
}

} // namespace Game
