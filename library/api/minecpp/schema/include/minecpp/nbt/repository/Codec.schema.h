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

class BiomeMusic {
 public:
   std::int8_t replace_current_music{};
   std::string sound{};
   std::int32_t max_delay{};
   std::int32_t min_delay{};
   BiomeMusic() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static BiomeMusic deserialize_no_header(minecpp::nbt::Reader &r);
   static BiomeMusic deserialize(std::istream &in);
};

class BiomeAdditionsSound {
 public:
   std::string sound{};
   double tick_chance{};
   BiomeAdditionsSound() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static BiomeAdditionsSound deserialize_no_header(minecpp::nbt::Reader &r);
   static BiomeAdditionsSound deserialize(std::istream &in);
};

class BiomeMoodSound {
 public:
   std::string sound{};
   std::int32_t tick_delay{};
   double offset{};
   std::int32_t block_search_extent{};
   BiomeMoodSound() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static BiomeMoodSound deserialize_no_header(minecpp::nbt::Reader &r);
   static BiomeMoodSound deserialize(std::istream &in);
};

class BiomeParticleOptions {
 public:
   std::string type{};
   BiomeParticleOptions() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static BiomeParticleOptions deserialize_no_header(minecpp::nbt::Reader &r);
   static BiomeParticleOptions deserialize(std::istream &in);
};

class BiomeParticle {
 public:
   float probability{};
   BiomeParticleOptions type{};
   BiomeParticle() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static BiomeParticle deserialize_no_header(minecpp::nbt::Reader &r);
   static BiomeParticle deserialize(std::istream &in);
};

class BiomeEffects {
 public:
   std::int32_t sky_color{};
   std::int32_t water_fog_color{};
   std::int32_t fog_color{};
   std::int32_t water_color{};
   std::optional<std::int32_t> foliage_color{};
   std::optional<std::int32_t> grass_color{};
   std::optional<std::string> grass_color_modifier{};
   std::optional<BiomeMusic> music{};
   std::optional<std::string> ambient_sound{};
   std::optional<BiomeAdditionsSound> additions_sound{};
   std::optional<BiomeMoodSound> mood_sound{};
   std::optional<BiomeParticle> particle{};
   BiomeEffects() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static BiomeEffects deserialize_no_header(minecpp::nbt::Reader &r);
   static BiomeEffects deserialize(std::istream &in);
};

class BiomeDescription {
 public:
   std::string precipitation{};
   float depth{};
   float temperature{};
   float scale{};
   float downfall{};
   std::string category{};
   std::optional<std::string> temperature_modifier{};
   BiomeEffects effects{};
   BiomeDescription() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static BiomeDescription deserialize_no_header(minecpp::nbt::Reader &r);
   static BiomeDescription deserialize(std::istream &in);
};

class BiomeEntry {
 public:
   std::string name{};
   std::int32_t id{};
   BiomeDescription element{};
   BiomeEntry() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static BiomeEntry deserialize_no_header(minecpp::nbt::Reader &r);
   static BiomeEntry deserialize(std::istream &in);
};

class Biomes {
 public:
   std::string type{};
   std::vector<BiomeEntry> value{};
   Biomes() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Biomes deserialize_no_header(minecpp::nbt::Reader &r);
   static Biomes deserialize(std::istream &in);
};

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

class Registry {
 public:
   DimensionTypes dimension_types{};
   Biomes biomes{};
   ChatTypes chat_types{};
   Registry() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Registry deserialize_no_header(minecpp::nbt::Reader &r);
   static Registry deserialize(std::istream &in);
};

}
