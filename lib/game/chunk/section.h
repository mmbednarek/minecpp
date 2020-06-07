#pragma once
#include <nbt/reader.h>
#include <variant>

namespace Game {

struct PaletteItem {
   std::string tag_name;
   NBT::TagMap properties;

   explicit PaletteItem(NBT::Reader &r);
   uint32_t to_state_id();
};

class Section {
   typedef std::vector<uint8_t> BlockVec8;
   typedef std::vector<uint16_t> BlockVec16;

 public:
   std::array<uint8_t, 2048> light;
   std::variant<BlockVec8, BlockVec16> blocks;
   std::vector<PaletteItem> palette;
   std::vector<uint8_t> sky_light;
   uint8_t y;

   Section();
   explicit Section(NBT::Reader &r);
   std::string_view block_at(int x, int y, int z);
   bool empty() const;
};

} // namespace Game
