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

namespace minecpp::nbt::block::v1 {

class EnumProperty {
 public:
   std::string name{};
   std::vector<std::string> values{};
   EnumProperty() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static EnumProperty deserialize_no_header(minecpp::nbt::Reader &r);
   static EnumProperty deserialize(std::istream &in);
};

class IntProperty {
 public:
   std::string name{};
   std::int32_t min_value{};
   std::int32_t max_value{};
   IntProperty() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static IntProperty deserialize_no_header(minecpp::nbt::Reader &r);
   static IntProperty deserialize(std::istream &in);
};

class BoolProperty {
 public:
   std::string name{};
   BoolProperty() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static BoolProperty deserialize_no_header(minecpp::nbt::Reader &r);
   static BoolProperty deserialize(std::istream &in);
};

class Block {
 public:
   std::vector<std::string> property_tags{};
   Block() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Block deserialize_no_header(minecpp::nbt::Reader &r);
   static Block deserialize(std::istream &in);
};

}
