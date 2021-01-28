#pragma once
#include <cstdint>
#include <string_view>
#include <vector>

namespace minecpp::game {

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

   [[nodiscard]] std::string_view tag() const;
   [[nodiscard]] ItemId id() const;

 private:
   ItemId _id;
   std::string_view tag_name;
   ItemGroup group;
   int max_stack_size;
   int max_damage;
};

} // namespace minecpp::game
