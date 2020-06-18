#pragma once
#include <cstdint>
#include <nbt/reader.h>
#include <string_view>

namespace Game {

struct InventoryItem {
   uint8_t count;
   uint8_t slot;
   std::string_view id;
   NBT::TagMap tag;

   explicit InventoryItem(NBT::Reader &r);
};

} // namespace Game