#ifndef MINECPP_NBT_REPOSITORY_V1_CODEC_H
#define MINECPP_NBT_REPOSITORY_V1_CODEC_H
#include <iostream>
#include <map>
#include <mb/int.h>
#include <mb/result.h>
#include <minecpp/nbt/Reader.h>
#include <minecpp/nbt/Writer.h>
#include <optional>
#include <string>
#include <vector>

namespace minecpp::nbt::repository::v1 {

class DimensionTypeDescription {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, double>) {
         if (name == "coordinate_scale") {
            this->coordinate_scale = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, float>) {
         if (name == "ambient_light") {
            this->ambient_light = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int32_t>) {
         if (name == "monster_spawn_light_level") {
            this->monster_spawn_light_level = std::forward<T>(value);
            return;
         }
         if (name == "monster_spawn_block_light_limit") {
            this->monster_spawn_block_light_limit = std::forward<T>(value);
            return;
         }
         if (name == "min_y") {
            this->min_y = std::forward<T>(value);
            return;
         }
         if (name == "height") {
            this->height = std::forward<T>(value);
            return;
         }
         if (name == "logical_height") {
            this->logical_height = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int64_t>) {
         if (name == "fixed_time") {
            this->fixed_time = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int8_t>) {
         if (name == "piglin_safe") {
            this->piglin_safe = std::forward<T>(value);
            return;
         }
         if (name == "has_raids") {
            this->has_raids = std::forward<T>(value);
            return;
         }
         if (name == "natural") {
            this->natural = std::forward<T>(value);
            return;
         }
         if (name == "respawn_anchor_works") {
            this->respawn_anchor_works = std::forward<T>(value);
            return;
         }
         if (name == "has_skylight") {
            this->has_skylight = std::forward<T>(value);
            return;
         }
         if (name == "bed_works") {
            this->bed_works = std::forward<T>(value);
            return;
         }
         if (name == "ultrawarm") {
            this->ultrawarm = std::forward<T>(value);
            return;
         }
         if (name == "has_ceiling") {
            this->has_ceiling = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (name == "infiniburn") {
            this->infiniburn = std::forward<T>(value);
            return;
         }
         if (name == "effects") {
            this->effects = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   std::int8_t piglin_safe{};
   std::int8_t has_raids{};
   std::int32_t monster_spawn_light_level{};
   std::int32_t monster_spawn_block_light_limit{};
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
   void serialize(std::ostream &out, std::string_view name) const;
   static DimensionTypeDescription deserialize_no_header(minecpp::nbt::Reader &r);
   static DimensionTypeDescription deserialize(std::istream &in);
};

class DimensionTypeEntry {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, DimensionTypeDescription>) {
         if (name == "element") {
            this->element = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int32_t>) {
         if (name == "id") {
            this->id = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (name == "name") {
            this->name = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   std::string name{};
   std::int32_t id{};
   DimensionTypeDescription element{};
   DimensionTypeEntry() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static DimensionTypeEntry deserialize_no_header(minecpp::nbt::Reader &r);
   static DimensionTypeEntry deserialize(std::istream &in);
};

class DimensionTypes {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (name == "type") {
            this->type = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<DimensionTypeEntry>>) {
         if (name == "value") {
            this->value = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   std::string type{};
   std::vector<DimensionTypeEntry> value{};
   DimensionTypes() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static DimensionTypes deserialize_no_header(minecpp::nbt::Reader &r);
   static DimensionTypes deserialize(std::istream &in);
};

class BiomeMusic {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::int32_t>) {
         if (name == "max_delay") {
            this->max_delay = std::forward<T>(value);
            return;
         }
         if (name == "min_delay") {
            this->min_delay = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int8_t>) {
         if (name == "replace_current_music") {
            this->replace_current_music = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (name == "sound") {
            this->sound = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   std::int8_t replace_current_music{};
   std::string sound{};
   std::int32_t max_delay{};
   std::int32_t min_delay{};
   BiomeMusic() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static BiomeMusic deserialize_no_header(minecpp::nbt::Reader &r);
   static BiomeMusic deserialize(std::istream &in);
};

class BiomeAdditionsSound {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, double>) {
         if (name == "tick_chance") {
            this->tick_chance = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (name == "sound") {
            this->sound = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   std::string sound{};
   double tick_chance{};
   BiomeAdditionsSound() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static BiomeAdditionsSound deserialize_no_header(minecpp::nbt::Reader &r);
   static BiomeAdditionsSound deserialize(std::istream &in);
};

class BiomeMoodSound {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, double>) {
         if (name == "tick_delay") {
            this->tick_delay = std::forward<T>(value);
            return;
         }
         if (name == "offset") {
            this->offset = std::forward<T>(value);
            return;
         }
         if (name == "block_search_extent") {
            this->block_search_extent = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (name == "sound") {
            this->sound = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   std::string sound{};
   double tick_delay{};
   double offset{};
   double block_search_extent{};
   BiomeMoodSound() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static BiomeMoodSound deserialize_no_header(minecpp::nbt::Reader &r);
   static BiomeMoodSound deserialize(std::istream &in);
};

class BiomeParticleOptions {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (name == "type") {
            this->type = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   std::string type{};
   BiomeParticleOptions() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static BiomeParticleOptions deserialize_no_header(minecpp::nbt::Reader &r);
   static BiomeParticleOptions deserialize(std::istream &in);
};

class BiomeParticle {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, BiomeParticleOptions>) {
         if (name == "type") {
            this->type = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, float>) {
         if (name == "probability") {
            this->probability = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   float probability{};
   BiomeParticleOptions type{};
   BiomeParticle() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static BiomeParticle deserialize_no_header(minecpp::nbt::Reader &r);
   static BiomeParticle deserialize(std::istream &in);
};

class BiomeEffects {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, BiomeAdditionsSound>) {
         if (name == "additions_sound") {
            this->additions_sound = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, BiomeMoodSound>) {
         if (name == "mood_sound") {
            this->mood_sound = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, BiomeMusic>) {
         if (name == "music") {
            this->music = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, BiomeParticle>) {
         if (name == "particle") {
            this->particle = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int32_t>) {
         if (name == "sky_color") {
            this->sky_color = std::forward<T>(value);
            return;
         }
         if (name == "water_fog_color") {
            this->water_fog_color = std::forward<T>(value);
            return;
         }
         if (name == "fog_color") {
            this->fog_color = std::forward<T>(value);
            return;
         }
         if (name == "water_color") {
            this->water_color = std::forward<T>(value);
            return;
         }
         if (name == "foliage_color") {
            this->foliage_color = std::forward<T>(value);
            return;
         }
         if (name == "grass_color") {
            this->grass_color = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (name == "grass_color_modifier") {
            this->grass_color_modifier = std::forward<T>(value);
            return;
         }
         if (name == "ambient_sound") {
            this->ambient_sound = std::forward<T>(value);
            return;
         }
         return;
      }
   }

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
   void serialize(std::ostream &out, std::string_view name) const;
   static BiomeEffects deserialize_no_header(minecpp::nbt::Reader &r);
   static BiomeEffects deserialize(std::istream &in);
};

class BiomeDescription {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, BiomeEffects>) {
         if (name == "effects") {
            this->effects = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, float>) {
         if (name == "depth") {
            this->depth = std::forward<T>(value);
            return;
         }
         if (name == "temperature") {
            this->temperature = std::forward<T>(value);
            return;
         }
         if (name == "scale") {
            this->scale = std::forward<T>(value);
            return;
         }
         if (name == "downfall") {
            this->downfall = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (name == "precipitation") {
            this->precipitation = std::forward<T>(value);
            return;
         }
         if (name == "category") {
            this->category = std::forward<T>(value);
            return;
         }
         if (name == "temperature_modifier") {
            this->temperature_modifier = std::forward<T>(value);
            return;
         }
         return;
      }
   }

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
   void serialize(std::ostream &out, std::string_view name) const;
   static BiomeDescription deserialize_no_header(minecpp::nbt::Reader &r);
   static BiomeDescription deserialize(std::istream &in);
};

class BiomeEntry {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, BiomeDescription>) {
         if (name == "element") {
            this->element = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int32_t>) {
         if (name == "id") {
            this->id = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (name == "name") {
            this->name = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   std::string name{};
   std::int32_t id{};
   BiomeDescription element{};
   BiomeEntry() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static BiomeEntry deserialize_no_header(minecpp::nbt::Reader &r);
   static BiomeEntry deserialize(std::istream &in);
};

class Biomes {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (name == "type") {
            this->type = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<BiomeEntry>>) {
         if (name == "value") {
            this->value = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   std::string type{};
   std::vector<BiomeEntry> value{};
   Biomes() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static Biomes deserialize_no_header(minecpp::nbt::Reader &r);
   static Biomes deserialize(std::istream &in);
};

class ChatDecorationStyle {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::int8_t>) {
         if (name == "italic") {
            this->italic = std::forward<T>(value);
            return;
         }
         if (name == "bold") {
            this->bold = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (name == "color") {
            this->color = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   std::string color{};
   std::int8_t italic{};
   std::int8_t bold{};
   ChatDecorationStyle() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static ChatDecorationStyle deserialize_no_header(minecpp::nbt::Reader &r);
   static ChatDecorationStyle deserialize(std::istream &in);
};

class ChatDecoration {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, ChatDecorationStyle>) {
         if (name == "style") {
            this->style = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (name == "translation_key") {
            this->translation_key = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<std::string>>) {
         if (name == "parameters") {
            this->parameters = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   std::vector<std::string> parameters{};
   ChatDecorationStyle style{};
   std::string translation_key{};
   ChatDecoration() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static ChatDecoration deserialize_no_header(minecpp::nbt::Reader &r);
   static ChatDecoration deserialize(std::istream &in);
};

class ChatNarration {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, ChatDecoration>) {
         if (name == "decoration") {
            this->decoration = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (name == "priority") {
            this->priority = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   std::optional<ChatDecoration> decoration{};
   std::string priority{};
   ChatNarration() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static ChatNarration deserialize_no_header(minecpp::nbt::Reader &r);
   static ChatNarration deserialize(std::istream &in);
};

class ChatDetails {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, ChatDecoration>) {
         if (name == "decoration") {
            this->decoration = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   std::optional<ChatDecoration> decoration{};
   ChatDetails() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static ChatDetails deserialize_no_header(minecpp::nbt::Reader &r);
   static ChatDetails deserialize(std::istream &in);
};

class ChatTypeDescription {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, ChatDetails>) {
         if (name == "chat") {
            this->chat = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, ChatNarration>) {
         if (name == "narration") {
            this->narration = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   ChatDetails chat{};
   ChatNarration narration{};
   ChatTypeDescription() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static ChatTypeDescription deserialize_no_header(minecpp::nbt::Reader &r);
   static ChatTypeDescription deserialize(std::istream &in);
};

class ChatTypeEntry {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, ChatTypeDescription>) {
         if (name == "element") {
            this->element = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int32_t>) {
         if (name == "id") {
            this->id = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (name == "name") {
            this->name = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   std::string name{};
   std::int32_t id{};
   ChatTypeDescription element{};
   ChatTypeEntry() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static ChatTypeEntry deserialize_no_header(minecpp::nbt::Reader &r);
   static ChatTypeEntry deserialize(std::istream &in);
};

class ChatTypes {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (name == "type") {
            this->type = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<ChatTypeEntry>>) {
         if (name == "value") {
            this->value = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   std::string type{};
   std::vector<ChatTypeEntry> value{};
   ChatTypes() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static ChatTypes deserialize_no_header(minecpp::nbt::Reader &r);
   static ChatTypes deserialize(std::istream &in);
};

class Registry {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, Biomes>) {
         if (name == "minecraft:worldgen/biome") {
            this->biomes = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, ChatTypes>) {
         if (name == "minecraft:chat_type") {
            this->chat_types = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, DimensionTypes>) {
         if (name == "minecraft:dimension_type") {
            this->dimension_types = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   DimensionTypes dimension_types{};
   Biomes biomes{};
   ChatTypes chat_types{};
   Registry() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static Registry deserialize_no_header(minecpp::nbt::Reader &r);
   static Registry deserialize(std::istream &in);
};

}
#endif//MINECPP_NBT_REPOSITORY_V1_CODEC_H
