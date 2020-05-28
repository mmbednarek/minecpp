//
// Created by ego on 5/22/20.
//

#include "section.h"

namespace Game {

Section::Section() : light{}, y(0xFF) {}

Section::Section(NBT::Reader &r) : light{} {
   r.read_compound(
       [this](NBT::Reader &r, NBT::TagID type, const std::string &key) {
          if (type == NBT::Byte && key == "Y") {
             y = r.read_payload<NBT::Byte>();
             return;
          }
          if (type == NBT::ByteArray) {
             if (key == "BlockLight") {
                light = r.read_array<2048>();
                return;
             }
             if (key == "SkyLight") {
                sky_light = r.read_payload<NBT::ByteArray>();
                return;
             }
             r.skip_payload(NBT::ByteArray);
             return;
          }
          if (type == NBT::List && key == "Palette") {
             r.read_list([this](NBT::Reader &r) { // TODO: Preallocate the array
                palette.emplace_back(PaletteItem(r));
             });
             return;
          }
          if (type == NBT::LongArray && key == "BlockStates") {
             auto size = r.read_payload<NBT::Int>();
             auto bits = size * 64 / 4096;
             if (bits > 8) {
                blocks = std::vector<uint16_t>(4096);
                r.read_packed_ints(get<BlockVec16>(blocks), bits, size);
             } else {
                blocks = std::vector<uint8_t>(4096);
                r.read_packed_ints(get<BlockVec8>(blocks), bits, size);
             }
             return;
          }
          throw std::runtime_error("unexpected nbt tag");
       });
   if (y > 15)
      return;
}

std::string_view Section::block_at(int x, int y, int z) {
   if (std::holds_alternative<BlockVec8>(blocks)) {
      return palette[std::get<BlockVec8>(blocks)[y * 256 + z * 16 + x]]
          .tag_name;
   }
   return palette[std::get<BlockVec16>(blocks)[y * 256 + z * 16 + x]].tag_name;
}

bool Section::empty() const { return palette.empty(); }

PaletteItem::PaletteItem(NBT::Reader &r) {
   r.read_compound([this](NBT::Reader &r, NBT::TagID type, std::string key) {
      if (key == "Name" && type == NBT::String) {
         tag_name = r.read_payload<NBT::String>();
         return;
      }
      // TODO: Read properties
      r.skip_payload(type); // ignore properties for now
   });
}

} // namespace Game
