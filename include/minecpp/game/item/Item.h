#pragma once
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace minecpp::game::item {

typedef int ItemId;

enum ItemGroup
{
   BuildingBlocks,
   Decorations,
   RedStone,
   Transportation,
   Search,// ?
   Misc,
   Food,
   Tools,
   Combat,
   Brewing,
};

inline ItemGroup Materials = Misc;

struct ItemStack
{
   ItemId id;
   uint8_t amount;
};

typedef std::vector<ItemStack> StackVariants;

class Item
{
 public:
   struct Details
   {
      std::string_view tag{};
      ItemGroup group{};
      int max_stack_size{};
      bool is_block{};
      std::string_view corresponding_block_tag{};
   };

   explicit Item(Details details);

   [[nodiscard]] constexpr const std::string &tag() const
   {
      return m_tag;
   }

   [[nodiscard]] constexpr bool is_block() const
   {
      return m_is_block;
   }

   [[nodiscard]] constexpr const std::string &corresponding_block_tag() const
   {
      return m_corresponding_block_tag;
   }

 private:
   std::string m_tag;
   ItemGroup m_group;
   int m_max_stack_size;
   bool m_is_block;
   std::string m_corresponding_block_tag;
};

}// namespace minecpp::game::item
