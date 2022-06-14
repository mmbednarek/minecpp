#include <minecpp/nbt/repository/v1/codec.nbt.h>

namespace minecpp::nbt::repository::v1 {

void DimensionTypeDescription::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Byte, "piglin_safe");
   w.write_byte_content(piglin_safe);
   w.write_header(minecpp::nbt::TagId::Byte, "has_raids");
   w.write_byte_content(has_raids);
   w.write_header(minecpp::nbt::TagId::Int, "monster_spawn_light_level");
   w.write_int_content(monster_spawn_light_level);
   w.write_header(minecpp::nbt::TagId::Int, "monster_spawn_block_light_limit");
   w.write_int_content(monster_spawn_block_light_limit);
   w.write_header(minecpp::nbt::TagId::Byte, "natural");
   w.write_byte_content(natural);
   w.write_header(minecpp::nbt::TagId::Float, "ambient_light");
   w.write_float_content(ambient_light);
   if (fixed_time.has_value()) {
      w.write_header(minecpp::nbt::TagId::Long, "fixed_time");
      w.write_long_content(*fixed_time);
   }
   w.write_header(minecpp::nbt::TagId::String, "infiniburn");
   w.write_string_content(infiniburn);
   w.write_header(minecpp::nbt::TagId::Byte, "respawn_anchor_works");
   w.write_byte_content(respawn_anchor_works);
   w.write_header(minecpp::nbt::TagId::Byte, "has_skylight");
   w.write_byte_content(has_skylight);
   w.write_header(minecpp::nbt::TagId::Byte, "bed_works");
   w.write_byte_content(bed_works);
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
   w.write_byte_content(ultrawarm);
   w.write_header(minecpp::nbt::TagId::Byte, "has_ceiling");
   w.write_byte_content(has_ceiling);
   w.end_compound();
}

void DimensionTypeDescription::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

DimensionTypeDescription DimensionTypeDescription::deserialize_no_header(minecpp::nbt::Reader &r) {
   DimensionTypeDescription res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Byte:
         res.__xx_put(name, r.read_byte());
         return;
      case minecpp::nbt::TagId::Int:
         res.__xx_put(name, r.read_int());
         return;
      case minecpp::nbt::TagId::Long:
         res.__xx_put(name, r.read_long());
         return;
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      case minecpp::nbt::TagId::Float:
         res.__xx_put(name, r.read_float32());
         return;
      case minecpp::nbt::TagId::Double:
         res.__xx_put(name, r.read_float64());
         return;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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

void DimensionTypeEntry::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

DimensionTypeEntry DimensionTypeEntry::deserialize_no_header(minecpp::nbt::Reader &r) {
   DimensionTypeEntry res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Int:
         res.__xx_put(name, r.read_int());
         return;
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      case minecpp::nbt::TagId::Compound:
         if (name == "element") {
            res.__xx_put(name, DimensionTypeDescription::deserialize_no_header(r));
            return;
         }
         break;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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
   std::for_each(value.begin(), value.end(), [&w](const auto &value) {
      value.serialize_no_header(w);
   });
   w.end_compound();
}

void DimensionTypes::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

DimensionTypes DimensionTypes::deserialize_no_header(minecpp::nbt::Reader &r) {
   DimensionTypes res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      case minecpp::nbt::TagId::List: {
         auto list_info0 = r.peek_list();
         if (list_info0.size > 0) {
            switch (list_info0.tagid) {
            case minecpp::nbt::TagId::Compound: {
               if (name == "value") {
                  std::vector<DimensionTypeEntry> ls(list_info0.size);
                  std::generate(ls.begin(), ls.end(), [&r]() {
                     return DimensionTypeEntry::deserialize_no_header(r);
                  });
                  res.__xx_put(name, ls);
                  return;
               }
               break;
            }
            default: 
               break;
            }
            for (mb::size i = 0; i < list_info0.size; ++i) {
               r.skip_payload(list_info0.tagid);
            }
         }
         return;
      }
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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
   w.write_byte_content(replace_current_music);
   w.write_header(minecpp::nbt::TagId::String, "sound");
   w.write_string_content(sound);
   w.write_header(minecpp::nbt::TagId::Int, "max_delay");
   w.write_int_content(max_delay);
   w.write_header(minecpp::nbt::TagId::Int, "min_delay");
   w.write_int_content(min_delay);
   w.end_compound();
}

void BiomeMusic::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

BiomeMusic BiomeMusic::deserialize_no_header(minecpp::nbt::Reader &r) {
   BiomeMusic res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Byte:
         res.__xx_put(name, r.read_byte());
         return;
      case minecpp::nbt::TagId::Int:
         res.__xx_put(name, r.read_int());
         return;
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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

void BiomeAdditionsSound::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

BiomeAdditionsSound BiomeAdditionsSound::deserialize_no_header(minecpp::nbt::Reader &r) {
   BiomeAdditionsSound res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      case minecpp::nbt::TagId::Double:
         res.__xx_put(name, r.read_float64());
         return;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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
   w.write_header(minecpp::nbt::TagId::Double, "tick_delay");
   w.write_double_content(tick_delay);
   w.write_header(minecpp::nbt::TagId::Double, "offset");
   w.write_double_content(offset);
   w.write_header(minecpp::nbt::TagId::Double, "block_search_extent");
   w.write_double_content(block_search_extent);
   w.end_compound();
}

void BiomeMoodSound::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

BiomeMoodSound BiomeMoodSound::deserialize_no_header(minecpp::nbt::Reader &r) {
   BiomeMoodSound res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      case minecpp::nbt::TagId::Double:
         res.__xx_put(name, r.read_float64());
         return;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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

void BiomeParticleOptions::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

BiomeParticleOptions BiomeParticleOptions::deserialize_no_header(minecpp::nbt::Reader &r) {
   BiomeParticleOptions res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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

void BiomeParticle::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

BiomeParticle BiomeParticle::deserialize_no_header(minecpp::nbt::Reader &r) {
   BiomeParticle res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Float:
         res.__xx_put(name, r.read_float32());
         return;
      case minecpp::nbt::TagId::Compound:
         if (name == "type") {
            res.__xx_put(name, BiomeParticleOptions::deserialize_no_header(r));
            return;
         }
         break;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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

void BiomeEffects::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

BiomeEffects BiomeEffects::deserialize_no_header(minecpp::nbt::Reader &r) {
   BiomeEffects res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Int:
         res.__xx_put(name, r.read_int());
         return;
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      case minecpp::nbt::TagId::Compound:
         if (name == "music") {
            res.__xx_put(name, BiomeMusic::deserialize_no_header(r));
            return;
         }
         if (name == "additions_sound") {
            res.__xx_put(name, BiomeAdditionsSound::deserialize_no_header(r));
            return;
         }
         if (name == "mood_sound") {
            res.__xx_put(name, BiomeMoodSound::deserialize_no_header(r));
            return;
         }
         if (name == "particle") {
            res.__xx_put(name, BiomeParticle::deserialize_no_header(r));
            return;
         }
         break;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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

void BiomeDescription::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

BiomeDescription BiomeDescription::deserialize_no_header(minecpp::nbt::Reader &r) {
   BiomeDescription res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      case minecpp::nbt::TagId::Float:
         res.__xx_put(name, r.read_float32());
         return;
      case minecpp::nbt::TagId::Compound:
         if (name == "effects") {
            res.__xx_put(name, BiomeEffects::deserialize_no_header(r));
            return;
         }
         break;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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

void BiomeEntry::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

BiomeEntry BiomeEntry::deserialize_no_header(minecpp::nbt::Reader &r) {
   BiomeEntry res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Int:
         res.__xx_put(name, r.read_int());
         return;
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      case minecpp::nbt::TagId::Compound:
         if (name == "element") {
            res.__xx_put(name, BiomeDescription::deserialize_no_header(r));
            return;
         }
         break;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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
   std::for_each(value.begin(), value.end(), [&w](const auto &value) {
      value.serialize_no_header(w);
   });
   w.end_compound();
}

void Biomes::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Biomes Biomes::deserialize_no_header(minecpp::nbt::Reader &r) {
   Biomes res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      case minecpp::nbt::TagId::List: {
         auto list_info0 = r.peek_list();
         if (list_info0.size > 0) {
            switch (list_info0.tagid) {
            case minecpp::nbt::TagId::Compound: {
               if (name == "value") {
                  std::vector<BiomeEntry> ls(list_info0.size);
                  std::generate(ls.begin(), ls.end(), [&r]() {
                     return BiomeEntry::deserialize_no_header(r);
                  });
                  res.__xx_put(name, ls);
                  return;
               }
               break;
            }
            default: 
               break;
            }
            for (mb::size i = 0; i < list_info0.size; ++i) {
               r.skip_payload(list_info0.tagid);
            }
         }
         return;
      }
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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
   w.write_byte_content(italic);
   w.write_header(minecpp::nbt::TagId::Byte, "bold");
   w.write_byte_content(bold);
   w.end_compound();
}

void ChatDecorationStyle::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

ChatDecorationStyle ChatDecorationStyle::deserialize_no_header(minecpp::nbt::Reader &r) {
   ChatDecorationStyle res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Byte:
         res.__xx_put(name, r.read_byte());
         return;
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
}

ChatDecorationStyle ChatDecorationStyle::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return ChatDecorationStyle::deserialize_no_header(r);
}

void ChatDecoration::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::List, "parameters");
   w.begin_list_no_header(minecpp::nbt::TagId::String, parameters.size());
   std::for_each(parameters.begin(), parameters.end(), [&w](const auto &value) {
      w.write_string_content(value);
   });
   w.write_header(minecpp::nbt::TagId::Compound, "style");
   style.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::String, "translation_key");
   w.write_string_content(translation_key);
   w.end_compound();
}

void ChatDecoration::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

ChatDecoration ChatDecoration::deserialize_no_header(minecpp::nbt::Reader &r) {
   ChatDecoration res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      case minecpp::nbt::TagId::Compound:
         if (name == "style") {
            res.__xx_put(name, ChatDecorationStyle::deserialize_no_header(r));
            return;
         }
         break;
      case minecpp::nbt::TagId::List: {
         auto list_info0 = r.peek_list();
         if (list_info0.size > 0) {
            switch (list_info0.tagid) {
            case minecpp::nbt::TagId::String: {
               std::vector<std::string> ls(list_info0.size);
               std::generate(ls.begin(), ls.end(), [&r]() {
                  return r.read_str();
               });
               res.__xx_put(name, ls);
               return;
            }
            default: 
               break;
            }
            for (mb::size i = 0; i < list_info0.size; ++i) {
               r.skip_payload(list_info0.tagid);
            }
         }
         return;
      }
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
}

ChatDecoration ChatDecoration::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return ChatDecoration::deserialize_no_header(r);
}

void ChatNarration::serialize_no_header(minecpp::nbt::Writer &w) const {
   if (decoration.has_value()) {
      w.write_header(minecpp::nbt::TagId::Compound, "decoration");
      decoration->serialize_no_header(w);
   }
   w.write_header(minecpp::nbt::TagId::String, "priority");
   w.write_string_content(priority);
   w.end_compound();
}

void ChatNarration::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

ChatNarration ChatNarration::deserialize_no_header(minecpp::nbt::Reader &r) {
   ChatNarration res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      case minecpp::nbt::TagId::Compound:
         if (name == "decoration") {
            res.__xx_put(name, ChatDecoration::deserialize_no_header(r));
            return;
         }
         break;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
}

ChatNarration ChatNarration::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return ChatNarration::deserialize_no_header(r);
}

void ChatDetails::serialize_no_header(minecpp::nbt::Writer &w) const {
   if (decoration.has_value()) {
      w.write_header(minecpp::nbt::TagId::Compound, "decoration");
      decoration->serialize_no_header(w);
   }
   w.end_compound();
}

void ChatDetails::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

ChatDetails ChatDetails::deserialize_no_header(minecpp::nbt::Reader &r) {
   ChatDetails res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Compound:
         if (name == "decoration") {
            res.__xx_put(name, ChatDecoration::deserialize_no_header(r));
            return;
         }
         break;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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

void ChatTypeDescription::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

ChatTypeDescription ChatTypeDescription::deserialize_no_header(minecpp::nbt::Reader &r) {
   ChatTypeDescription res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Compound:
         if (name == "chat") {
            res.__xx_put(name, ChatDetails::deserialize_no_header(r));
            return;
         }
         if (name == "narration") {
            res.__xx_put(name, ChatNarration::deserialize_no_header(r));
            return;
         }
         break;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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

void ChatTypeEntry::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

ChatTypeEntry ChatTypeEntry::deserialize_no_header(minecpp::nbt::Reader &r) {
   ChatTypeEntry res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Int:
         res.__xx_put(name, r.read_int());
         return;
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      case minecpp::nbt::TagId::Compound:
         if (name == "element") {
            res.__xx_put(name, ChatTypeDescription::deserialize_no_header(r));
            return;
         }
         break;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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
   std::for_each(value.begin(), value.end(), [&w](const auto &value) {
      value.serialize_no_header(w);
   });
   w.end_compound();
}

void ChatTypes::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

ChatTypes ChatTypes::deserialize_no_header(minecpp::nbt::Reader &r) {
   ChatTypes res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      case minecpp::nbt::TagId::List: {
         auto list_info0 = r.peek_list();
         if (list_info0.size > 0) {
            switch (list_info0.tagid) {
            case minecpp::nbt::TagId::Compound: {
               if (name == "value") {
                  std::vector<ChatTypeEntry> ls(list_info0.size);
                  std::generate(ls.begin(), ls.end(), [&r]() {
                     return ChatTypeEntry::deserialize_no_header(r);
                  });
                  res.__xx_put(name, ls);
                  return;
               }
               break;
            }
            default: 
               break;
            }
            for (mb::size i = 0; i < list_info0.size; ++i) {
               r.skip_payload(list_info0.tagid);
            }
         }
         return;
      }
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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

void Registry::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Registry Registry::deserialize_no_header(minecpp::nbt::Reader &r) {
   Registry res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Compound:
         if (name == "minecraft:dimension_type") {
            res.__xx_put(name, DimensionTypes::deserialize_no_header(r));
            return;
         }
         if (name == "minecraft:worldgen/biome") {
            res.__xx_put(name, Biomes::deserialize_no_header(r));
            return;
         }
         if (name == "minecraft:chat_type") {
            res.__xx_put(name, ChatTypes::deserialize_no_header(r));
            return;
         }
         break;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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