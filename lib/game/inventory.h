#pragma once
#include <cstdint>
#include <nbt/reader.h>
#include <nbt/tag.h>
#include <string_view>

namespace Game {

struct InventoryItem {
   uint8_t count;
   uint8_t slot;
   std::string_view id;
   NBT::CompoundContent tag;

   explicit InventoryItem(NBT::Reader &r);
};

} // namespace Game