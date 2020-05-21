#pragma once
#include <cstdint>
#include <vector>
#include <string_view>

namespace Game {

typedef int ItemId;

enum ItemGroup {
   BuildingBlocks,
   Decorations,
   RedStone,
   Transportation,
   Search, // ?
   Misc,
   Food,
   Tools,
   Combat,
   Brewing,
};

inline ItemGroup Materials = Misc;

struct ItemStack {
   ItemId id;
   uint8_t amount;
};

typedef std::vector<ItemStack> StackVariants;

class Item {
 public:
   Item(ItemId id, std::string_view tag_name, ItemGroup group);

   std::string_view tag();
 private:
   ItemId id;
   std::string_view tag_name;
   ItemGroup group;
   int max_stack_size;
   int max_damage;
};

} // namespace Game
