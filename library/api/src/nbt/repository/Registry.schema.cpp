#include "nbt/repository/Registry.schema.h"
#include <minecpp/nbt/Exception.h>

namespace minecpp::nbt::repository {

void Registry::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Compound, "minecraft:chat_type");
   chat_types.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Compound, "minecraft:damage_type");
   damage_types.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Compound, "minecraft:dimension_type");
   dimension_types.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Compound, "minecraft:trim_material");
   trim_materials.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Compound, "minecraft:trim_pattern");
   trim_patterns.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Compound, "minecraft:worldgen/biome");
   biomes.serialize_no_header(w);
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
      if (in_field_name == "minecraft:chat_type") {
         ::minecpp::nbt::verify_tag("Registry", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.chat_types = ChatTypes::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "minecraft:damage_type") {
         ::minecpp::nbt::verify_tag("Registry", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.damage_types = DamageTypes::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "minecraft:dimension_type") {
         ::minecpp::nbt::verify_tag("Registry", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.dimension_types = DimensionTypes::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "minecraft:trim_material") {
         ::minecpp::nbt::verify_tag("Registry", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.trim_materials = TrimMaterialTypes::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "minecraft:trim_pattern") {
         ::minecpp::nbt::verify_tag("Registry", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.trim_patterns = TrimPatternTypes::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "minecraft:worldgen/biome") {
         ::minecpp::nbt::verify_tag("Registry", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.biomes = BiomeTypes::deserialize_no_header(r);
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