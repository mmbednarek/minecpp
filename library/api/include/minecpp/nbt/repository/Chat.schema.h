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

class ChatDecorationStyle {
 public:
   std::string color{};
   std::int8_t italic{};
   std::int8_t bold{};
   ChatDecorationStyle() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static ChatDecorationStyle deserialize_no_header(minecpp::nbt::Reader &r);
   static ChatDecorationStyle deserialize(std::istream &in);
};

class ChatDetails {
 public:
   std::vector<std::string> parameters{};
   std::optional<ChatDecorationStyle> style{};
   std::string translation_key{};
   ChatDetails() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static ChatDetails deserialize_no_header(minecpp::nbt::Reader &r);
   static ChatDetails deserialize(std::istream &in);
};

class ChatTypeDescription {
 public:
   ChatDetails chat{};
   ChatDetails narration{};
   ChatTypeDescription() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static ChatTypeDescription deserialize_no_header(minecpp::nbt::Reader &r);
   static ChatTypeDescription deserialize(std::istream &in);
};

class ChatTypeEntry {
 public:
   std::string name{};
   std::int32_t id{};
   ChatTypeDescription element{};
   ChatTypeEntry() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static ChatTypeEntry deserialize_no_header(minecpp::nbt::Reader &r);
   static ChatTypeEntry deserialize(std::istream &in);
};

class ChatTypes {
 public:
   std::string type{};
   std::vector<ChatTypeEntry> value{};
   ChatTypes() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static ChatTypes deserialize_no_header(minecpp::nbt::Reader &r);
   static ChatTypes deserialize(std::istream &in);
};

}
