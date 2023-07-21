#include "nbt/repository/Dimension.schema.h"
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

}