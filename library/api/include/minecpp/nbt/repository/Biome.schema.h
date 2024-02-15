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

class BiomeMusic {
 public:
   static constexpr auto object_name = "BiomeMusic";
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
   static constexpr auto object_name = "BiomeAdditionsSound";
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
   static constexpr auto object_name = "BiomeMoodSound";
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
   static constexpr auto object_name = "BiomeParticleOptions";
   std::string type{};
   BiomeParticleOptions() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static BiomeParticleOptions deserialize_no_header(minecpp::nbt::Reader &r);
   static BiomeParticleOptions deserialize(std::istream &in);
};

class BiomeParticle {
 public:
   static constexpr auto object_name = "BiomeParticle";
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
   static constexpr auto object_name = "BiomeEffects";
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
   static constexpr auto object_name = "BiomeDescription";
   std::string precipitation{};
   float depth{};
   float temperature{};
   float scale{};
   float downfall{};
   std::string category{};
   std::optional<std::string> temperature_modifier{};
   BiomeEffects effects{};
   std::int8_t has_precipitation{};
   BiomeDescription() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static BiomeDescription deserialize_no_header(minecpp::nbt::Reader &r);
   static BiomeDescription deserialize(std::istream &in);
};

class BiomeEntry {
 public:
   static constexpr auto object_name = "BiomeEntry";
   std::string name{};
   std::int32_t id{};
   BiomeDescription element{};
   BiomeEntry() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static BiomeEntry deserialize_no_header(minecpp::nbt::Reader &r);
   static BiomeEntry deserialize(std::istream &in);
};

class BiomeTypes {
 public:
   static constexpr auto object_name = "BiomeTypes";
   std::string type{};
   std::vector<BiomeEntry> value{};
   BiomeTypes() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static BiomeTypes deserialize_no_header(minecpp::nbt::Reader &r);
   static BiomeTypes deserialize(std::istream &in);
};

}
