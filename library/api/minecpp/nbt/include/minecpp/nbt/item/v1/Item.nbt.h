#ifndef MINECPP_NBT_ITEM_V1_ITEM_H
#define MINECPP_NBT_ITEM_V1_ITEM_H
#include <iostream>
#include <map>
#include <mb/int.h>
#include <mb/result.h>
#include <minecpp/nbt/Reader.h>
#include <minecpp/nbt/Writer.h>
#include <optional>
#include <string>
#include <vector>

namespace minecpp::nbt::item::v1 {

class Item
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::int32_t>) {
         if (in_field_name == "MaxItemStack") {
            this->max_item_stack = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int8_t>) {
         if (in_field_name == "IsBlock") {
            this->is_block = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (in_field_name == "CorrespondingBlockTag") {
            this->corresponding_block_tag = std::forward<T>(in_value);
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
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Item deserialize_no_header(minecpp::nbt::Reader &r);
   static Item deserialize(std::istream &in);
};

}// namespace minecpp::nbt::item::v1
#endif//MINECPP_NBT_ITEM_V1_ITEM_H
