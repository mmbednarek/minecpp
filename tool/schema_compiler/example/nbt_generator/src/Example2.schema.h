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

namespace minecpp::example2 {

class Properties {
 public:
   std::string name{};
   double position{};
   std::int16_t count{};
   std::map<std::string, std::string> meta{};
   Properties() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Properties deserialize_no_header(minecpp::nbt::Reader &r);
   static Properties deserialize(std::istream &in);
};

}
