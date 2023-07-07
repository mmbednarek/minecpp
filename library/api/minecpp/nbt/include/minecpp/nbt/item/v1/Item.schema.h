#pragma once
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

class Item {
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

}
