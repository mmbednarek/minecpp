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

class MonsterSpawnLightLevelValue {
 public:
   std::int32_t max_inclusive{};
   std::int32_t min_inclusive{};
   MonsterSpawnLightLevelValue() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static MonsterSpawnLightLevelValue deserialize_no_header(minecpp::nbt::Reader &r);
   static MonsterSpawnLightLevelValue deserialize(std::istream &in);
};

class MonsterSpawnLightLevel {
 public:
   std::string type{};
   MonsterSpawnLightLevelValue value{};
   MonsterSpawnLightLevel() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static MonsterSpawnLightLevel deserialize_no_header(minecpp::nbt::Reader &r);
   static MonsterSpawnLightLevel deserialize(std::istream &in);
};

class DimensionTypeDescription {
 public:
   std::int8_t piglin_safe{};
   std::int8_t has_raids{};
   std::int32_t monster_spawn_block_light_limit{};
   std::variant<MonsterSpawnLightLevel, std::int32_t> monster_spawn_light_level{};
   std::int8_t natural{};
   float ambient_light{};
   std::optional<std::int64_t> fixed_time{};
   std::string infiniburn{};
   std::int8_t respawn_anchor_works{};
   std::int8_t has_skylight{};
   std::int8_t bed_works{};
   std::string effects{};
   std::int32_t min_y{};
   std::int32_t height{};
   std::int32_t logical_height{};
   double coordinate_scale{};
   std::int8_t ultrawarm{};
   std::int8_t has_ceiling{};
   DimensionTypeDescription() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static DimensionTypeDescription deserialize_no_header(minecpp::nbt::Reader &r);
   static DimensionTypeDescription deserialize(std::istream &in);
};

class DimensionTypeEntry {
 public:
   std::string name{};
   std::int32_t id{};
   DimensionTypeDescription element{};
   DimensionTypeEntry() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static DimensionTypeEntry deserialize_no_header(minecpp::nbt::Reader &r);
   static DimensionTypeEntry deserialize(std::istream &in);
};

class DimensionTypes {
 public:
   std::string type{};
   std::vector<DimensionTypeEntry> value{};
   DimensionTypes() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static DimensionTypes deserialize_no_header(minecpp::nbt::Reader &r);
   static DimensionTypes deserialize(std::istream &in);
};

}
