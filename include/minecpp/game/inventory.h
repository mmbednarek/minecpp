#pragma once
#include <cstdint>
#include <minecpp/nbt/reader.h>
#include <minecpp/nbt/tag.h>
#include <string_view>

namespace minecpp::game {

struct InventoryItem
{
   uint8_t count;
   uint8_t slot;
   std::string_view id;
   nbt::CompoundContent tag;

   explicit InventoryItem(nbt::Reader &r);
};

}// namespace minecpp::game