#include "chunk.h"
#include <stdexcept>
#include <vector>

namespace Game {

inline int expected_data_version = 2230;

Chunk::PaletteItem::PaletteItem(NBT::Reader &r) {
   r.read_compound([this](NBT::Reader &r, NBT::TagID type, std::string key) {
      if (key == "Name" && type == NBT::String) {
         tag_name = r.read_payload<NBT::String>();
         return;
      }
      // TODO: Read properties
      r.skip_payload(type); // ignore properties for now
   });
}

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
         r.read_list([this](NBT::Reader &r) { read_section(r); });
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
   if (type != NBT::LongArray)
      [[unlikely]] {
         throw std::runtime_error("height map must be long array type");
      }

   int size = r.read_payload<NBT::Int>();
   if (size != 36)
      [[unlikely]] {
         throw std::runtime_error("height map's length must be 36");
      }

   HeightMap result;

   auto i = r.read_packed_ints<9>(result, 36);
   assert(i == 256);

   return result;
}

void Chunk::read_section(NBT::Reader &r) {
   auto *section = new Chunk::Section();
   uint8_t y = 0;
   r.read_compound([this, section, &y](NBT::Reader &r, NBT::TagID type,
                                       const std::string &key) {
      if (type == NBT::Byte && key == "Y") {
         y = r.read_payload<NBT::Byte>();
         return;
      }
      if (y == 255) {
         if (type == NBT::ByteArray && key == "SkyLight") {
            sky_light = r.read_array<2048>();
            return;
         }
         throw std::runtime_error("unexpected nbt tag");
      }
      if (type == NBT::ByteArray) {
         if (key == "BlockLight") {
            section->light = r.read_array<2048>();
            return;
         }
         if (key == "SkyLight") {
            section->sky_light = r.read_array<2048>();
            return;
         }
         r.skip_payload(NBT::ByteArray);
         return;
      }
      if (type == NBT::List && key == "Palette") {
         r.read_list([section](NBT::Reader &r) { // TODO: Preallocate the array
            section->palette.emplace_back(PaletteItem(r));
         });
         return;
      }
      if (type == NBT::LongArray && key == "BlockStates") {
         auto size = r.read_payload<NBT::Int>();

         size_t i;
         switch (size * 64 / 4096) {
         case 1:
            i = r.read_packed_ints<1>(section->block, size);
            break;
         case 2:
            i = r.read_packed_ints<2>(section->block, size);
            break;
         case 3:
            i = r.read_packed_ints<3>(section->block, size);
            break;
         case 4:
            i = r.read_packed_ints<4>(section->block, size);
            break;
         case 5:
            i = r.read_packed_ints<5>(section->block, size);
            break;
         case 6:
            i = r.read_packed_ints<6>(section->block, size);
            break;
         case 7:
            i = r.read_packed_ints<7>(section->block, size);
            break;
         case 8:
            i = r.read_packed_ints<8>(section->block, size);
            break;
         case 9:
            i = r.read_packed_ints<9>(section->block, size);
            break;
         case 10:
            i = r.read_packed_ints<10>(section->block, size);
            break;
         default:
            throw std::runtime_error("chunk section with too many items");
         }

         assert(i == 4096);
         return;
      }
      throw std::runtime_error("unexpected nbt tag");
   });
   if (y > 15)
      return;
   sections[y] = std::shared_ptr<Section>(section);
}

} // namespace Game
