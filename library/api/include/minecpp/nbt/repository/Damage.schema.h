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

namespace minecpp::nbt::repository {

class DamageTypeDescription {
 public:
   float exhaustion{};
   std::string message_id{};
   std::string scaling{};
   DamageTypeDescription() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static DamageTypeDescription deserialize_no_header(minecpp::nbt::Reader &r);
   static DamageTypeDescription deserialize(std::istream &in);
};

class DamageTypeEntry {
 public:
   DamageTypeDescription element{};
   std::int32_t id{};
   std::string name{};
   DamageTypeEntry() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static DamageTypeEntry deserialize_no_header(minecpp::nbt::Reader &r);
   static DamageTypeEntry deserialize(std::istream &in);
};

class DamageTypes {
 public:
   std::string type{};
   std::vector<DamageTypeEntry> value{};
   DamageTypes() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static DamageTypes deserialize_no_header(minecpp::nbt::Reader &r);
   static DamageTypes deserialize(std::istream &in);
};

}
