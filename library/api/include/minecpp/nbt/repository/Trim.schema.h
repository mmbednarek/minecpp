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

class TrimMaterialDescription {
 public:
   static constexpr auto object_name = "TrimMaterialDescription";
   std::string color{};
   std::string translate{};
   TrimMaterialDescription() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static TrimMaterialDescription deserialize_no_header(minecpp::nbt::Reader &r);
   static TrimMaterialDescription deserialize(std::istream &in);
};

class TrimMaterialInfo {
 public:
   static constexpr auto object_name = "TrimMaterialInfo";
   std::string asset_name{};
   TrimMaterialDescription description{};
   std::string ingredient{};
   float item_model_index{};
   ::minecpp::nbt::CompoundContent override_armor_materials{};
   TrimMaterialInfo() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static TrimMaterialInfo deserialize_no_header(minecpp::nbt::Reader &r);
   static TrimMaterialInfo deserialize(std::istream &in);
};

class TrimMaterialEntry {
 public:
   static constexpr auto object_name = "TrimMaterialEntry";
   TrimMaterialInfo element{};
   std::int32_t id{};
   std::string name{};
   TrimMaterialEntry() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static TrimMaterialEntry deserialize_no_header(minecpp::nbt::Reader &r);
   static TrimMaterialEntry deserialize(std::istream &in);
};

class TrimMaterialTypes {
 public:
   static constexpr auto object_name = "TrimMaterialTypes";
   std::string type{};
   std::vector<TrimMaterialEntry> value{};
   TrimMaterialTypes() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static TrimMaterialTypes deserialize_no_header(minecpp::nbt::Reader &r);
   static TrimMaterialTypes deserialize(std::istream &in);
};

class TrimPatternDescription {
 public:
   static constexpr auto object_name = "TrimPatternDescription";
   std::string translate{};
   TrimPatternDescription() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static TrimPatternDescription deserialize_no_header(minecpp::nbt::Reader &r);
   static TrimPatternDescription deserialize(std::istream &in);
};

class TrimPatternInfo {
 public:
   static constexpr auto object_name = "TrimPatternInfo";
   std::string asset_id{};
   TrimPatternDescription description{};
   std::string template_item{};
   TrimPatternInfo() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static TrimPatternInfo deserialize_no_header(minecpp::nbt::Reader &r);
   static TrimPatternInfo deserialize(std::istream &in);
};

class TrimPatternEntry {
 public:
   static constexpr auto object_name = "TrimPatternEntry";
   TrimPatternInfo element{};
   std::int32_t id{};
   std::string name{};
   TrimPatternEntry() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static TrimPatternEntry deserialize_no_header(minecpp::nbt::Reader &r);
   static TrimPatternEntry deserialize(std::istream &in);
};

class TrimPatternTypes {
 public:
   static constexpr auto object_name = "TrimPatternTypes";
   std::string type{};
   std::vector<TrimPatternEntry> value{};
   TrimPatternTypes() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static TrimPatternTypes deserialize_no_header(minecpp::nbt::Reader &r);
   static TrimPatternTypes deserialize(std::istream &in);
};

}
