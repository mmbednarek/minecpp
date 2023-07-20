#include "nbt/repository/Biome.schema.h"
#include <minecpp/nbt/Exception.h>

namespace minecpp::nbt::repository {

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
   w.write_header(minecpp::nbt::TagId::Byte, "has_precipitation");
   w.write_byte_content(static_cast<std::uint8_t>(has_precipitation));
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
      if (in_field_name == "has_precipitation") {
         ::minecpp::nbt::verify_tag("BiomeDescription", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.has_precipitation = r.read_byte();
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

void BiomeTypes::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "type");
   w.write_string_content(type);
   w.write_header(minecpp::nbt::TagId::List, "value");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, value.size());
   for (const auto &list_item_0 : value) {
      list_item_0.serialize_no_header(w);
   }
   w.end_compound();
}

void BiomeTypes::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

BiomeTypes BiomeTypes::deserialize_no_header(minecpp::nbt::Reader &r) {
   BiomeTypes result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "type") {
         ::minecpp::nbt::verify_tag("BiomeTypes", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.type = r.read_str();
         continue;
      }
      if (in_field_name == "value") {
         ::minecpp::nbt::verify_tag("BiomeTypes", in_field_name, minecpp::nbt::TagId::List, tagid);
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

BiomeTypes BiomeTypes::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return BiomeTypes::deserialize_no_header(r);
}

}