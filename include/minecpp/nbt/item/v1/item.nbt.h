#ifndef MINECPP_NBT_ITEM_V1_ITEM_H
#define MINECPP_NBT_ITEM_V1_ITEM_H
#include <iostream>
#include <map>
#include <mb/int.h>
#include <mb/result.h>
#include <minecpp/nbt/reader.h>
#include <minecpp/nbt/writer.h>
#include <string>
#include <vector>

namespace minecpp::nbt::item::v1 {

#ifndef MINECPP_NBT_ITEM_V1_ITEM_H_OFFSET_CLASS
#define MINECPP_NBT_ITEM_V1_ITEM_H_OFFSET_CLASS

class __nbt_idl_offset
{
 public:
   mb::size offset{};
   mb::size size{};
   int id{};
};
#endif//MINECPP_NBT_ITEM_V1_ITEM_H_OFFSET_CLASS

class Item
{

   template<typename T>
   void __xx_put(const std::string &name, T &&value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::int32_t>) {
         if (name == "MaxItemStack") {
            this->max_item_stack = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int8_t>) {
         if (name == "IsBlock") {
            this->is_block = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (name == "CorrespondingBlockTag") {
            this->corresponding_block_tag = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   std::int8_t is_block{};
   std::string corresponding_block_tag{};
   std::int32_t max_item_stack{};
   Item() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static Item deserialize_no_header(minecpp::nbt::Reader &r);
   static Item deserialize(std::istream &in);
};

}// namespace minecpp::nbt::item::v1
#endif//MINECPP_NBT_ITEM_V1_ITEM_H
