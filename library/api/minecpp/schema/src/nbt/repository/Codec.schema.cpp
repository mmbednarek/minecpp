#include "nbt/repository/Codec.schema.h"
#include <minecpp/nbt/Exception.h>

namespace minecpp::nbt::repository {

void MonsterSpawnLightLevelValue::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Int, "max_inclusive");
   w.write_int_content(max_inclusive);
   w.write_header(minecpp::nbt::TagId::Int, "min_inclusive");
   w.write_int_content(min_inclusive);
   w.end_compound();
}

void MonsterSpawnLightLevelValue::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

MonsterSpawnLightLevelValue MonsterSpawnLightLevelValue::deserialize_no_header(minecpp::nbt::Reader &r) {
   MonsterSpawnLightLevelValue result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "max_inclusive") {
         ::minecpp::nbt::verify_tag("MonsterSpawnLightLevelValue", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.max_inclusive = r.read_int();
         continue;
      }
      if (in_field_name == "min_inclusive") {
         ::minecpp::nbt::verify_tag("MonsterSpawnLightLevelValue", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.min_inclusive = r.read_int();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

MonsterSpawnLightLevelValue MonsterSpawnLightLevelValue::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return MonsterSpawnLightLevelValue::deserialize_no_header(r);
}

void MonsterSpawnLightLevel::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "type");
   w.write_string_content(type);
   w.write_header(minecpp::nbt::TagId::Compound, "value");
   value.serialize_no_header(w);
   w.end_compound();
}

void MonsterSpawnLightLevel::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

MonsterSpawnLightLevel MonsterSpawnLightLevel::deserialize_no_header(minecpp::nbt::Reader &r) {
   MonsterSpawnLightLevel result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "type") {
         ::minecpp::nbt::verify_tag("MonsterSpawnLightLevel", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.type = r.read_str();
         continue;
      }
      if (in_field_name == "value") {
         ::minecpp::nbt::verify_tag("MonsterSpawnLightLevel", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.value = MonsterSpawnLightLevelValue::deserialize_no_header(r);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

MonsterSpawnLightLevel MonsterSpawnLightLevel::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return MonsterSpawnLightLevel::deserialize_no_header(r);
}

void DimensionTypeDescription::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Byte, "piglin_safe");
   w.write_byte_content(static_cast<std::uint8_t>(piglin_safe));
   w.write_header(minecpp::nbt::TagId::Byte, "has_raids");
   w.write_byte_content(static_cast<std::uint8_t>(has_raids));
   w.write_header(minecpp::nbt::TagId::Int, "monster_spawn_block_light_limit");
   w.write_int_content(monster_spawn_block_light_limit);
   if (std::holds_alternative<MonsterSpawnLightLevel>(monster_spawn_light_level)) {
      w.write_header(minecpp::nbt::TagId::Compound, "monster_spawn_light_level");
      std::get<MonsterSpawnLightLevel>(monster_spawn_light_level).serialize_no_header(w);
   } else if (std::holds_alternative<std::int32_t>(monster_spawn_light_level)) {
      w.write_header(minecpp::nbt::TagId::Int, "monster_spawn_light_level");
      w.write_int_content(std::get<std::int32_t>(monster_spawn_light_level));
   }
   w.write_header(minecpp::nbt::TagId::Byte, "natural");
   w.write_byte_content(static_cast<std::uint8_t>(natural));
   w.write_header(minecpp::nbt::TagId::Float, "ambient_light");
   w.write_float_content(ambient_light);
   if (fixed_time.has_value()) {
      w.write_header(minecpp::nbt::TagId::Long, "fixed_time");
      w.write_long_content(*fixed_time);
   }
   w.write_header(minecpp::nbt::TagId::String, "infiniburn");
   w.write_string_content(infiniburn);
   w.write_header(minecpp::nbt::TagId::Byte, "respawn_anchor_works");
   w.write_byte_content(static_cast<std::uint8_t>(respawn_anchor_works));
   w.write_header(minecpp::nbt::TagId::Byte, "has_skylight");
   w.write_byte_content(static_cast<std::uint8_t>(has_skylight));
   w.write_header(minecpp::nbt::TagId::Byte, "bed_works");
   w.write_byte_content(static_cast<std::uint8_t>(bed_works));
   w.write_header(minecpp::nbt::TagId::String, "effects");
   w.write_string_content(effects);
   w.write_header(minecpp::nbt::TagId::Int, "min_y");
   w.write_int_content(min_y);
   w.write_header(minecpp::nbt::TagId::Int, "height");
   w.write_int_content(height);
   w.write_header(minecpp::nbt::TagId::Int, "logical_height");
   w.write_int_content(logical_height);
   w.write_header(minecpp::nbt::TagId::Double, "coordinate_scale");
   w.write_double_content(coordinate_scale);
   w.write_header(minecpp::nbt::TagId::Byte, "ultrawarm");
   w.write_byte_content(static_cast<std::uint8_t>(ultrawarm));
   w.write_header(minecpp::nbt::TagId::Byte, "has_ceiling");
   w.write_byte_content(static_cast<std::uint8_t>(has_ceiling));
   w.end_compound();
}

void DimensionTypeDescription::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

DimensionTypeDescription DimensionTypeDescription::deserialize_no_header(minecpp::nbt::Reader &r) {
   DimensionTypeDescription result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "piglin_safe") {
         ::minecpp::nbt::verify_tag("DimensionTypeDescription", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.piglin_safe = r.read_byte();
         continue;
      }
      if (in_field_name == "has_raids") {
         ::minecpp::nbt::verify_tag("DimensionTypeDescription", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.has_raids = r.read_byte();
         continue;
      }
      if (in_field_name == "monster_spawn_block_light_limit") {
         ::minecpp::nbt::verify_tag("DimensionTypeDescription", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.monster_spawn_block_light_limit = r.read_int();
         continue;
      }
      if (in_field_name == "monster_spawn_light_level") {
         std::variant<MonsterSpawnLightLevel, std::int32_t> result_variant;
         if (tagid == minecpp::nbt::TagId::Compound) {
            result_variant = MonsterSpawnLightLevel::deserialize_no_header(r);
         } else if (tagid == minecpp::nbt::TagId::Int) {
            result_variant = r.read_int();
         }
         result.monster_spawn_light_level = std::move(result_variant);
         continue;
      }
      if (in_field_name == "natural") {
         ::minecpp::nbt::verify_tag("DimensionTypeDescription", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.natural = r.read_byte();
         continue;
      }
      if (in_field_name == "ambient_light") {
         ::minecpp::nbt::verify_tag("DimensionTypeDescription", in_field_name, minecpp::nbt::TagId::Float, tagid);
         result.ambient_light = r.read_float32();
         continue;
      }
      if (in_field_name == "fixed_time") {
         ::minecpp::nbt::verify_tag("DimensionTypeDescription", in_field_name, minecpp::nbt::TagId::Long, tagid);
         result.fixed_time = r.read_long();
         continue;
      }
      if (in_field_name == "infiniburn") {
         ::minecpp::nbt::verify_tag("DimensionTypeDescription", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.infiniburn = r.read_str();
         continue;
      }
      if (in_field_name == "respawn_anchor_works") {
         ::minecpp::nbt::verify_tag("DimensionTypeDescription", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.respawn_anchor_works = r.read_byte();
         continue;
      }
      if (in_field_name == "has_skylight") {
         ::minecpp::nbt::verify_tag("DimensionTypeDescription", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.has_skylight = r.read_byte();
         continue;
      }
      if (in_field_name == "bed_works") {
         ::minecpp::nbt::verify_tag("DimensionTypeDescription", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.bed_works = r.read_byte();
         continue;
      }
      if (in_field_name == "effects") {
         ::minecpp::nbt::verify_tag("DimensionTypeDescription", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.effects = r.read_str();
         continue;
      }
      if (in_field_name == "min_y") {
         ::minecpp::nbt::verify_tag("DimensionTypeDescription", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.min_y = r.read_int();
         continue;
      }
      if (in_field_name == "height") {
         ::minecpp::nbt::verify_tag("DimensionTypeDescription", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.height = r.read_int();
         continue;
      }
      if (in_field_name == "logical_height") {
         ::minecpp::nbt::verify_tag("DimensionTypeDescription", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.logical_height = r.read_int();
         continue;
      }
      if (in_field_name == "coordinate_scale") {
         ::minecpp::nbt::verify_tag("DimensionTypeDescription", in_field_name, minecpp::nbt::TagId::Double, tagid);
         result.coordinate_scale = r.read_float64();
         continue;
      }
      if (in_field_name == "ultrawarm") {
         ::minecpp::nbt::verify_tag("DimensionTypeDescription", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.ultrawarm = r.read_byte();
         continue;
      }
      if (in_field_name == "has_ceiling") {
         ::minecpp::nbt::verify_tag("DimensionTypeDescription", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.has_ceiling = r.read_byte();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

DimensionTypeDescription DimensionTypeDescription::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return DimensionTypeDescription::deserialize_no_header(r);
}

void DimensionTypeEntry::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "name");
   w.write_string_content(name);
   w.write_header(minecpp::nbt::TagId::Int, "id");
   w.write_int_content(id);
   w.write_header(minecpp::nbt::TagId::Compound, "element");
   element.serialize_no_header(w);
   w.end_compound();
}

void DimensionTypeEntry::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

DimensionTypeEntry DimensionTypeEntry::deserialize_no_header(minecpp::nbt::Reader &r) {
   DimensionTypeEntry result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "name") {
         ::minecpp::nbt::verify_tag("DimensionTypeEntry", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.name = r.read_str();
         continue;
      }
      if (in_field_name == "id") {
         ::minecpp::nbt::verify_tag("DimensionTypeEntry", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.id = r.read_int();
         continue;
      }
      if (in_field_name == "element") {
         ::minecpp::nbt::verify_tag("DimensionTypeEntry", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.element = DimensionTypeDescription::deserialize_no_header(r);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

DimensionTypeEntry DimensionTypeEntry::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return DimensionTypeEntry::deserialize_no_header(r);
}

void DimensionTypes::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "type");
   w.write_string_content(type);
   w.write_header(minecpp::nbt::TagId::List, "value");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, value.size());
   for (const auto &list_item_0 : value) {
      list_item_0.serialize_no_header(w);
   }
   w.end_compound();
}

void DimensionTypes::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

DimensionTypes DimensionTypes::deserialize_no_header(minecpp::nbt::Reader &r) {
   DimensionTypes result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "type") {
         ::minecpp::nbt::verify_tag("DimensionTypes", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.type = r.read_str();
         continue;
      }
      if (in_field_name == "value") {
         ::minecpp::nbt::verify_tag("DimensionTypes", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<DimensionTypeEntry> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return DimensionTypeEntry::deserialize_no_header(r);
         });
         result.value = std::move(list);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

DimensionTypes DimensionTypes::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return DimensionTypes::deserialize_no_header(r);
}

void BiomeMusic::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Byte, "replace_current_music");
   w.write_byte_content(static_cast<std::uint8_t>(replace_current_music));
   w.write_header(minecpp::nbt::TagId::String, "sound");
   w.write_string_content(sound);
   w.write_header(minecpp::nbt::TagId::Int, "max_delay");
   w.write_int_content(max_delay);
   w.write_header(minecpp::nbt::TagId::Int, "min_delay");
   w.write_int_content(min_delay);
   w.end_compound();
}

void BiomeMusic::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

BiomeMusic BiomeMusic::deserialize_no_header(minecpp::nbt::Reader &r) {
   BiomeMusic result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "replace_current_music") {
         ::minecpp::nbt::verify_tag("BiomeMusic", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.replace_current_music = r.read_byte();
         continue;
      }
      if (in_field_name == "sound") {
         ::minecpp::nbt::verify_tag("BiomeMusic", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.sound = r.read_str();
         continue;
      }
      if (in_field_name == "max_delay") {
         ::minecpp::nbt::verify_tag("BiomeMusic", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.max_delay = r.read_int();
         continue;
      }
      if (in_field_name == "min_delay") {
         ::minecpp::nbt::verify_tag("BiomeMusic", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.min_delay = r.read_int();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

BiomeMusic BiomeMusic::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return BiomeMusic::deserialize_no_header(r);
}

void BiomeAdditionsSound::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "sound");
   w.write_string_content(sound);
   w.write_header(minecpp::nbt::TagId::Double, "tick_chance");
   w.write_double_content(tick_chance);
   w.end_compound();
}

void BiomeAdditionsSound::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

BiomeAdditionsSound BiomeAdditionsSound::deserialize_no_header(minecpp::nbt::Reader &r) {
   BiomeAdditionsSound result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "sound") {
         ::minecpp::nbt::verify_tag("BiomeAdditionsSound", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.sound = r.read_str();
         continue;
      }
      if (in_field_name == "tick_chance") {
         ::minecpp::nbt::verify_tag("BiomeAdditionsSound", in_field_name, minecpp::nbt::TagId::Double, tagid);
         result.tick_chance = r.read_float64();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

BiomeAdditionsSound BiomeAdditionsSound::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return BiomeAdditionsSound::deserialize_no_header(r);
}

void BiomeMoodSound::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "sound");
   w.write_string_content(sound);
   w.write_header(minecpp::nbt::TagId::Int, "tick_delay");
   w.write_int_content(tick_delay);
   w.write_header(minecpp::nbt::TagId::Double, "offset");
   w.write_double_content(offset);
   w.write_header(minecpp::nbt::TagId::Int, "block_search_extent");
   w.write_int_content(block_search_extent);
   w.end_compound();
}

void BiomeMoodSound::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

BiomeMoodSound BiomeMoodSound::deserialize_no_header(minecpp::nbt::Reader &r) {
   BiomeMoodSound result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "sound") {
         ::minecpp::nbt::verify_tag("BiomeMoodSound", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.sound = r.read_str();
         continue;
      }
      if (in_field_name == "tick_delay") {
         ::minecpp::nbt::verify_tag("BiomeMoodSound", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.tick_delay = r.read_int();
         continue;
      }
      if (in_field_name == "offset") {
         ::minecpp::nbt::verify_tag("BiomeMoodSound", in_field_name, minecpp::nbt::TagId::Double, tagid);
         result.offset = r.read_float64();
         continue;
      }
      if (in_field_name == "block_search_extent") {
         ::minecpp::nbt::verify_tag("BiomeMoodSound", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.block_search_extent = r.read_int();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

BiomeMoodSound BiomeMoodSound::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return BiomeMoodSound::deserialize_no_header(r);
}

void BiomeParticleOptions::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "type");
   w.write_string_content(type);
   w.end_compound();
}

void BiomeParticleOptions::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

BiomeParticleOptions BiomeParticleOptions::deserialize_no_header(minecpp::nbt::Reader &r) {
   BiomeParticleOptions result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "type") {
         ::minecpp::nbt::verify_tag("BiomeParticleOptions", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.type = r.read_str();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

BiomeParticleOptions BiomeParticleOptions::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return BiomeParticleOptions::deserialize_no_header(r);
}

void BiomeParticle::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Float, "probability");
   w.write_float_content(probability);
   w.write_header(minecpp::nbt::TagId::Compound, "type");
   type.serialize_no_header(w);
   w.end_compound();
}

void BiomeParticle::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

BiomeParticle BiomeParticle::deserialize_no_header(minecpp::nbt::Reader &r) {
   BiomeParticle result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "probability") {
         ::minecpp::nbt::verify_tag("BiomeParticle", in_field_name, minecpp::nbt::TagId::Float, tagid);
         result.probability = r.read_float32();
         continue;
      }
      if (in_field_name == "type") {
         ::minecpp::nbt::verify_tag("BiomeParticle", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.type = BiomeParticleOptions::deserialize_no_header(r);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

BiomeParticle BiomeParticle::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return BiomeParticle::deserialize_no_header(r);
}

void BiomeEffects::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Int, "sky_color");
   w.write_int_content(sky_color);
   w.write_header(minecpp::nbt::TagId::Int, "water_fog_color");
   w.write_int_content(water_fog_color);
   w.write_header(minecpp::nbt::TagId::Int, "fog_color");
   w.write_int_content(fog_color);
   w.write_header(minecpp::nbt::TagId::Int, "water_color");
   w.write_int_content(water_color);
   if (foliage_color.has_value()) {
      w.write_header(minecpp::nbt::TagId::Int, "foliage_color");
      w.write_int_content(*foliage_color);
   }
   if (grass_color.has_value()) {
      w.write_header(minecpp::nbt::TagId::Int, "grass_color");
      w.write_int_content(*grass_color);
   }
   if (grass_color_modifier.has_value()) {
      w.write_header(minecpp::nbt::TagId::String, "grass_color_modifier");
      w.write_string_content(*grass_color_modifier);
   }
   if (music.has_value()) {
      w.write_header(minecpp::nbt::TagId::Compound, "music");
      music->serialize_no_header(w);
   }
   if (ambient_sound.has_value()) {
      w.write_header(minecpp::nbt::TagId::String, "ambient_sound");
      w.write_string_content(*ambient_sound);
   }
   if (additions_sound.has_value()) {
      w.write_header(minecpp::nbt::TagId::Compound, "additions_sound");
      additions_sound->serialize_no_header(w);
   }
   if (mood_sound.has_value()) {
      w.write_header(minecpp::nbt::TagId::Compound, "mood_sound");
      mood_sound->serialize_no_header(w);
   }
   if (particle.has_value()) {
      w.write_header(minecpp::nbt::TagId::Compound, "particle");
      particle->serialize_no_header(w);
   }
   w.end_compound();
}

void BiomeEffects::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

BiomeEffects BiomeEffects::deserialize_no_header(minecpp::nbt::Reader &r) {
   BiomeEffects result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "sky_color") {
         ::minecpp::nbt::verify_tag("BiomeEffects", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.sky_color = r.read_int();
         continue;
      }
      if (in_field_name == "water_fog_color") {
         ::minecpp::nbt::verify_tag("BiomeEffects", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.water_fog_color = r.read_int();
         continue;
      }
      if (in_field_name == "fog_color") {
         ::minecpp::nbt::verify_tag("BiomeEffects", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.fog_color = r.read_int();
         continue;
      }
      if (in_field_name == "water_color") {
         ::minecpp::nbt::verify_tag("BiomeEffects", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.water_color = r.read_int();
         continue;
      }
      if (in_field_name == "foliage_color") {
         ::minecpp::nbt::verify_tag("BiomeEffects", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.foliage_color = r.read_int();
         continue;
      }
      if (in_field_name == "grass_color") {
         ::minecpp::nbt::verify_tag("BiomeEffects", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.grass_color = r.read_int();
         continue;
      }
      if (in_field_name == "grass_color_modifier") {
         ::minecpp::nbt::verify_tag("BiomeEffects", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.grass_color_modifier = r.read_str();
         continue;
      }
      if (in_field_name == "music") {
         ::minecpp::nbt::verify_tag("BiomeEffects", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.music = BiomeMusic::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "ambient_sound") {
         ::minecpp::nbt::verify_tag("BiomeEffects", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.ambient_sound = r.read_str();
         continue;
      }
      if (in_field_name == "additions_sound") {
         ::minecpp::nbt::verify_tag("BiomeEffects", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.additions_sound = BiomeAdditionsSound::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "mood_sound") {
         ::minecpp::nbt::verify_tag("BiomeEffects", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.mood_sound = BiomeMoodSound::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "particle") {
         ::minecpp::nbt::verify_tag("BiomeEffects", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.particle = BiomeParticle::deserialize_no_header(r);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

BiomeEffects BiomeEffects::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return BiomeEffects::deserialize_no_header(r);
}

void BiomeDescription::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "precipitation");
   w.write_string_content(precipitation);
   w.write_header(minecpp::nbt::TagId::Float, "depth");
   w.write_float_content(depth);
   w.write_header(minecpp::nbt::TagId::Float, "temperature");
   w.write_float_content(temperature);
   w.write_header(minecpp::nbt::TagId::Float, "scale");
   w.write_float_content(scale);
   w.write_header(minecpp::nbt::TagId::Float, "downfall");
   w.write_float_content(downfall);
   w.write_header(minecpp::nbt::TagId::String, "category");
   w.write_string_content(category);
   if (temperature_modifier.has_value()) {
      w.write_header(minecpp::nbt::TagId::String, "temperature_modifier");
      w.write_string_content(*temperature_modifier);
   }
   w.write_header(minecpp::nbt::TagId::Compound, "effects");
   effects.serialize_no_header(w);
   w.end_compound();
}

void BiomeDescription::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

BiomeDescription BiomeDescription::deserialize_no_header(minecpp::nbt::Reader &r) {
   BiomeDescription result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "precipitation") {
         ::minecpp::nbt::verify_tag("BiomeDescription", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.precipitation = r.read_str();
         continue;
      }
      if (in_field_name == "depth") {
         ::minecpp::nbt::verify_tag("BiomeDescription", in_field_name, minecpp::nbt::TagId::Float, tagid);
         result.depth = r.read_float32();
         continue;
      }
      if (in_field_name == "temperature") {
         ::minecpp::nbt::verify_tag("BiomeDescription", in_field_name, minecpp::nbt::TagId::Float, tagid);
         result.temperature = r.read_float32();
         continue;
      }
      if (in_field_name == "scale") {
         ::minecpp::nbt::verify_tag("BiomeDescription", in_field_name, minecpp::nbt::TagId::Float, tagid);
         result.scale = r.read_float32();
         continue;
      }
      if (in_field_name == "downfall") {
         ::minecpp::nbt::verify_tag("BiomeDescription", in_field_name, minecpp::nbt::TagId::Float, tagid);
         result.downfall = r.read_float32();
         continue;
      }
      if (in_field_name == "category") {
         ::minecpp::nbt::verify_tag("BiomeDescription", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.category = r.read_str();
         continue;
      }
      if (in_field_name == "temperature_modifier") {
         ::minecpp::nbt::verify_tag("BiomeDescription", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.temperature_modifier = r.read_str();
         continue;
      }
      if (in_field_name == "effects") {
         ::minecpp::nbt::verify_tag("BiomeDescription", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.effects = BiomeEffects::deserialize_no_header(r);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

BiomeDescription BiomeDescription::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return BiomeDescription::deserialize_no_header(r);
}

void BiomeEntry::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "name");
   w.write_string_content(name);
   w.write_header(minecpp::nbt::TagId::Int, "id");
   w.write_int_content(id);
   w.write_header(minecpp::nbt::TagId::Compound, "element");
   element.serialize_no_header(w);
   w.end_compound();
}

void BiomeEntry::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

BiomeEntry BiomeEntry::deserialize_no_header(minecpp::nbt::Reader &r) {
   BiomeEntry result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "name") {
         ::minecpp::nbt::verify_tag("BiomeEntry", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.name = r.read_str();
         continue;
      }
      if (in_field_name == "id") {
         ::minecpp::nbt::verify_tag("BiomeEntry", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.id = r.read_int();
         continue;
      }
      if (in_field_name == "element") {
         ::minecpp::nbt::verify_tag("BiomeEntry", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.element = BiomeDescription::deserialize_no_header(r);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

BiomeEntry BiomeEntry::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return BiomeEntry::deserialize_no_header(r);
}

void Biomes::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "type");
   w.write_string_content(type);
   w.write_header(minecpp::nbt::TagId::List, "value");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, value.size());
   for (const auto &list_item_0 : value) {
      list_item_0.serialize_no_header(w);
   }
   w.end_compound();
}

void Biomes::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

Biomes Biomes::deserialize_no_header(minecpp::nbt::Reader &r) {
   Biomes result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "type") {
         ::minecpp::nbt::verify_tag("Biomes", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.type = r.read_str();
         continue;
      }
      if (in_field_name == "value") {
         ::minecpp::nbt::verify_tag("Biomes", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<BiomeEntry> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return BiomeEntry::deserialize_no_header(r);
         });
         result.value = std::move(list);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

Biomes Biomes::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return Biomes::deserialize_no_header(r);
}

void ChatDecorationStyle::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "color");
   w.write_string_content(color);
   w.write_header(minecpp::nbt::TagId::Byte, "italic");
   w.write_byte_content(static_cast<std::uint8_t>(italic));
   w.write_header(minecpp::nbt::TagId::Byte, "bold");
   w.write_byte_content(static_cast<std::uint8_t>(bold));
   w.end_compound();
}

void ChatDecorationStyle::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

ChatDecorationStyle ChatDecorationStyle::deserialize_no_header(minecpp::nbt::Reader &r) {
   ChatDecorationStyle result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "color") {
         ::minecpp::nbt::verify_tag("ChatDecorationStyle", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.color = r.read_str();
         continue;
      }
      if (in_field_name == "italic") {
         ::minecpp::nbt::verify_tag("ChatDecorationStyle", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.italic = r.read_byte();
         continue;
      }
      if (in_field_name == "bold") {
         ::minecpp::nbt::verify_tag("ChatDecorationStyle", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.bold = r.read_byte();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

ChatDecorationStyle ChatDecorationStyle::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return ChatDecorationStyle::deserialize_no_header(r);
}

void ChatDetails::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::List, "parameters");
   w.begin_list_no_header(minecpp::nbt::TagId::String, parameters.size());
   for (const auto &list_item_0 : parameters) {
      w.write_string_content(list_item_0);
   }
   if (style.has_value()) {
      w.write_header(minecpp::nbt::TagId::Compound, "style");
      style->serialize_no_header(w);
   }
   w.write_header(minecpp::nbt::TagId::String, "translation_key");
   w.write_string_content(translation_key);
   w.end_compound();
}

void ChatDetails::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

ChatDetails ChatDetails::deserialize_no_header(minecpp::nbt::Reader &r) {
   ChatDetails result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "parameters") {
         ::minecpp::nbt::verify_tag("ChatDetails", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<std::string> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return r.read_str();
         });
         result.parameters = std::move(list);
         continue;
      }
      if (in_field_name == "style") {
         ::minecpp::nbt::verify_tag("ChatDetails", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.style = ChatDecorationStyle::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "translation_key") {
         ::minecpp::nbt::verify_tag("ChatDetails", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.translation_key = r.read_str();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

ChatDetails ChatDetails::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return ChatDetails::deserialize_no_header(r);
}

void ChatTypeDescription::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Compound, "chat");
   chat.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Compound, "narration");
   narration.serialize_no_header(w);
   w.end_compound();
}

void ChatTypeDescription::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

ChatTypeDescription ChatTypeDescription::deserialize_no_header(minecpp::nbt::Reader &r) {
   ChatTypeDescription result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "chat") {
         ::minecpp::nbt::verify_tag("ChatTypeDescription", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.chat = ChatDetails::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "narration") {
         ::minecpp::nbt::verify_tag("ChatTypeDescription", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.narration = ChatDetails::deserialize_no_header(r);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

ChatTypeDescription ChatTypeDescription::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return ChatTypeDescription::deserialize_no_header(r);
}

void ChatTypeEntry::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "name");
   w.write_string_content(name);
   w.write_header(minecpp::nbt::TagId::Int, "id");
   w.write_int_content(id);
   w.write_header(minecpp::nbt::TagId::Compound, "element");
   element.serialize_no_header(w);
   w.end_compound();
}

void ChatTypeEntry::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

ChatTypeEntry ChatTypeEntry::deserialize_no_header(minecpp::nbt::Reader &r) {
   ChatTypeEntry result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "name") {
         ::minecpp::nbt::verify_tag("ChatTypeEntry", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.name = r.read_str();
         continue;
      }
      if (in_field_name == "id") {
         ::minecpp::nbt::verify_tag("ChatTypeEntry", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.id = r.read_int();
         continue;
      }
      if (in_field_name == "element") {
         ::minecpp::nbt::verify_tag("ChatTypeEntry", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.element = ChatTypeDescription::deserialize_no_header(r);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

ChatTypeEntry ChatTypeEntry::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return ChatTypeEntry::deserialize_no_header(r);
}

void ChatTypes::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "type");
   w.write_string_content(type);
   w.write_header(minecpp::nbt::TagId::List, "value");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, value.size());
   for (const auto &list_item_0 : value) {
      list_item_0.serialize_no_header(w);
   }
   w.end_compound();
}

void ChatTypes::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

ChatTypes ChatTypes::deserialize_no_header(minecpp::nbt::Reader &r) {
   ChatTypes result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "type") {
         ::minecpp::nbt::verify_tag("ChatTypes", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.type = r.read_str();
         continue;
      }
      if (in_field_name == "value") {
         ::minecpp::nbt::verify_tag("ChatTypes", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<ChatTypeEntry> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return ChatTypeEntry::deserialize_no_header(r);
         });
         result.value = std::move(list);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

ChatTypes ChatTypes::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return ChatTypes::deserialize_no_header(r);
}

void Registry::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Compound, "minecraft:dimension_type");
   dimension_types.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Compound, "minecraft:worldgen/biome");
   biomes.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Compound, "minecraft:chat_type");
   chat_types.serialize_no_header(w);
   w.end_compound();
}

void Registry::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

Registry Registry::deserialize_no_header(minecpp::nbt::Reader &r) {
   Registry result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "minecraft:dimension_type") {
         ::minecpp::nbt::verify_tag("Registry", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.dimension_types = DimensionTypes::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "minecraft:worldgen/biome") {
         ::minecpp::nbt::verify_tag("Registry", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.biomes = Biomes::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "minecraft:chat_type") {
         ::minecpp::nbt::verify_tag("Registry", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.chat_types = ChatTypes::deserialize_no_header(r);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

Registry Registry::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return Registry::deserialize_no_header(r);
}

}