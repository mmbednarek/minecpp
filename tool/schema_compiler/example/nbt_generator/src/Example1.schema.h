#pragma once
#include "./Example2.schema.h"
#include <iostream>
#include <map>
#include <mb/int.h>
#include <mb/result.h>
#include <minecpp/nbt/Reader.h>
#include <minecpp/nbt/Writer.h>
#include <optional>
#include <string>
#include <vector>

namespace minecpp::example1 {

class Item {
 public:
   std::string name{};
   std::int16_t count{};
   example2::Properties props{};
   Item() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Item deserialize_no_header(minecpp::nbt::Reader &r);
   static Item deserialize(std::istream &in);
};

class Person {
 public:
   std::string name{};
   std::string surname{};
   std::int32_t age{};
   std::vector<std::vector<Item>> inventory{};
   std::int32_t dimension_types{};
   std::variant<std::int32_t, std::string, std::int8_t> foo_type{};
   Person() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Person deserialize_no_header(minecpp::nbt::Reader &r);
   static Person deserialize(std::istream &in);
};

}
