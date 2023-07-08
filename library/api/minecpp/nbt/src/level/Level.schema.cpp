#include "level/Level.schema.h"
#include <minecpp/nbt/Exception.h>

namespace minecpp::nbt::level {

void Memories::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Int, "no_empty");
   w.write_int_content(no_empty);
   w.end_compound();
}

void Memories::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

Memories Memories::deserialize_no_header(minecpp::nbt::Reader &r) {
   Memories result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "no_empty") {
         ::minecpp::nbt::verify_tag("Memories", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.no_empty = r.read_int();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

Memories Memories::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return Memories::deserialize_no_header(r);
}

void Brain::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Compound, "memories");
   memories.serialize_no_header(w);
   w.end_compound();
}

void Brain::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

Brain Brain::deserialize_no_header(minecpp::nbt::Reader &r) {
   Brain result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "memories") {
         ::minecpp::nbt::verify_tag("Brain", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.memories = Memories::deserialize_no_header(r);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

Brain Brain::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return Brain::deserialize_no_header(r);
}

void Abilities::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Float, "flySpeed");
   w.write_float_content(fly_speed);
   w.write_header(minecpp::nbt::TagId::Byte, "flying");
   w.write_byte_content(static_cast<std::uint8_t>(flying));
   w.write_header(minecpp::nbt::TagId::Byte, "instabuild");
   w.write_byte_content(static_cast<std::uint8_t>(instabuild));
   w.write_header(minecpp::nbt::TagId::Byte, "invulnerable");
   w.write_byte_content(static_cast<std::uint8_t>(invulnerable));
   w.write_header(minecpp::nbt::TagId::Byte, "mayBuild");
   w.write_byte_content(static_cast<std::uint8_t>(may_build));
   w.write_header(minecpp::nbt::TagId::Byte, "mayfly");
   w.write_byte_content(static_cast<std::uint8_t>(mayfly));
   w.write_header(minecpp::nbt::TagId::Float, "walkSpeed");
   w.write_float_content(walk_speed);
   w.end_compound();
}

void Abilities::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

Abilities Abilities::deserialize_no_header(minecpp::nbt::Reader &r) {
   Abilities result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "flySpeed") {
         ::minecpp::nbt::verify_tag("Abilities", in_field_name, minecpp::nbt::TagId::Float, tagid);
         result.fly_speed = r.read_float32();
         continue;
      }
      if (in_field_name == "flying") {
         ::minecpp::nbt::verify_tag("Abilities", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.flying = r.read_byte();
         continue;
      }
      if (in_field_name == "instabuild") {
         ::minecpp::nbt::verify_tag("Abilities", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.instabuild = r.read_byte();
         continue;
      }
      if (in_field_name == "invulnerable") {
         ::minecpp::nbt::verify_tag("Abilities", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.invulnerable = r.read_byte();
         continue;
      }
      if (in_field_name == "mayBuild") {
         ::minecpp::nbt::verify_tag("Abilities", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.may_build = r.read_byte();
         continue;
      }
      if (in_field_name == "mayfly") {
         ::minecpp::nbt::verify_tag("Abilities", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.mayfly = r.read_byte();
         continue;
      }
      if (in_field_name == "walkSpeed") {
         ::minecpp::nbt::verify_tag("Abilities", in_field_name, minecpp::nbt::TagId::Float, tagid);
         result.walk_speed = r.read_float32();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

Abilities Abilities::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return Abilities::deserialize_no_header(r);
}

void RecipeBook::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Byte, "isBlastingFurnaceFilteringCraftable");
   w.write_byte_content(static_cast<std::uint8_t>(is_blasting_furnace_filtering_craftable));
   w.write_header(minecpp::nbt::TagId::Byte, "isBlastingFurnaceGuiOpen");
   w.write_byte_content(static_cast<std::uint8_t>(is_blasting_furnace_gui_open));
   w.write_header(minecpp::nbt::TagId::Byte, "isFilteringCraftable");
   w.write_byte_content(static_cast<std::uint8_t>(is_filtering_craftable));
   w.write_header(minecpp::nbt::TagId::Byte, "isFurnaceFilteringCraftable");
   w.write_byte_content(static_cast<std::uint8_t>(is_furnace_filtering_craftable));
   w.write_header(minecpp::nbt::TagId::Byte, "isFurnaceGuiOpen");
   w.write_byte_content(static_cast<std::uint8_t>(is_furnace_gui_open));
   w.write_header(minecpp::nbt::TagId::Byte, "isGuiOpen");
   w.write_byte_content(static_cast<std::uint8_t>(is_gui_open));
   w.write_header(minecpp::nbt::TagId::Byte, "isSmokerFilteringCraftable");
   w.write_byte_content(static_cast<std::uint8_t>(is_smoker_filtering_craftable));
   w.write_header(minecpp::nbt::TagId::Byte, "isSmokerGuiOpen");
   w.write_byte_content(static_cast<std::uint8_t>(is_smoker_gui_open));
   w.end_compound();
}

void RecipeBook::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

RecipeBook RecipeBook::deserialize_no_header(minecpp::nbt::Reader &r) {
   RecipeBook result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "isBlastingFurnaceFilteringCraftable") {
         ::minecpp::nbt::verify_tag("RecipeBook", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.is_blasting_furnace_filtering_craftable = r.read_byte();
         continue;
      }
      if (in_field_name == "isBlastingFurnaceGuiOpen") {
         ::minecpp::nbt::verify_tag("RecipeBook", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.is_blasting_furnace_gui_open = r.read_byte();
         continue;
      }
      if (in_field_name == "isFilteringCraftable") {
         ::minecpp::nbt::verify_tag("RecipeBook", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.is_filtering_craftable = r.read_byte();
         continue;
      }
      if (in_field_name == "isFurnaceFilteringCraftable") {
         ::minecpp::nbt::verify_tag("RecipeBook", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.is_furnace_filtering_craftable = r.read_byte();
         continue;
      }
      if (in_field_name == "isFurnaceGuiOpen") {
         ::minecpp::nbt::verify_tag("RecipeBook", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.is_furnace_gui_open = r.read_byte();
         continue;
      }
      if (in_field_name == "isGuiOpen") {
         ::minecpp::nbt::verify_tag("RecipeBook", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.is_gui_open = r.read_byte();
         continue;
      }
      if (in_field_name == "isSmokerFilteringCraftable") {
         ::minecpp::nbt::verify_tag("RecipeBook", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.is_smoker_filtering_craftable = r.read_byte();
         continue;
      }
      if (in_field_name == "isSmokerGuiOpen") {
         ::minecpp::nbt::verify_tag("RecipeBook", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.is_smoker_gui_open = r.read_byte();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

RecipeBook RecipeBook::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return RecipeBook::deserialize_no_header(r);
}

void Version::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Int, "Id");
   w.write_int_content(id);
   w.write_header(minecpp::nbt::TagId::String, "Name");
   w.write_string_content(name);
   w.write_header(minecpp::nbt::TagId::Byte, "Snapshot");
   w.write_byte_content(static_cast<std::uint8_t>(snapshot));
   w.end_compound();
}

void Version::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

Version Version::deserialize_no_header(minecpp::nbt::Reader &r) {
   Version result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "Id") {
         ::minecpp::nbt::verify_tag("Version", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.id = r.read_int();
         continue;
      }
      if (in_field_name == "Name") {
         ::minecpp::nbt::verify_tag("Version", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.name = r.read_str();
         continue;
      }
      if (in_field_name == "Snapshot") {
         ::minecpp::nbt::verify_tag("Version", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.snapshot = r.read_byte();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

Version Version::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return Version::deserialize_no_header(r);
}

void BiomeSource::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "preset");
   w.write_string_content(preset);
   w.write_header(minecpp::nbt::TagId::Byte, "large_biomes");
   w.write_byte_content(static_cast<std::uint8_t>(large_biomes));
   w.write_header(minecpp::nbt::TagId::Long, "seed");
   w.write_long_content(seed);
   w.write_header(minecpp::nbt::TagId::String, "type");
   w.write_string_content(type);
   w.end_compound();
}

void BiomeSource::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

BiomeSource BiomeSource::deserialize_no_header(minecpp::nbt::Reader &r) {
   BiomeSource result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "preset") {
         ::minecpp::nbt::verify_tag("BiomeSource", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.preset = r.read_str();
         continue;
      }
      if (in_field_name == "large_biomes") {
         ::minecpp::nbt::verify_tag("BiomeSource", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.large_biomes = r.read_byte();
         continue;
      }
      if (in_field_name == "seed") {
         ::minecpp::nbt::verify_tag("BiomeSource", in_field_name, minecpp::nbt::TagId::Long, tagid);
         result.seed = r.read_long();
         continue;
      }
      if (in_field_name == "type") {
         ::minecpp::nbt::verify_tag("BiomeSource", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.type = r.read_str();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

BiomeSource BiomeSource::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return BiomeSource::deserialize_no_header(r);
}

void Generator::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Compound, "biome_source");
   biome_source.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Long, "seed");
   w.write_long_content(seed);
   w.write_header(minecpp::nbt::TagId::String, "settings");
   w.write_string_content(settings);
   w.write_header(minecpp::nbt::TagId::String, "type");
   w.write_string_content(type);
   w.end_compound();
}

void Generator::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

Generator Generator::deserialize_no_header(minecpp::nbt::Reader &r) {
   Generator result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "biome_source") {
         ::minecpp::nbt::verify_tag("Generator", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.biome_source = BiomeSource::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "seed") {
         ::minecpp::nbt::verify_tag("Generator", in_field_name, minecpp::nbt::TagId::Long, tagid);
         result.seed = r.read_long();
         continue;
      }
      if (in_field_name == "settings") {
         ::minecpp::nbt::verify_tag("Generator", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.settings = r.read_str();
         continue;
      }
      if (in_field_name == "type") {
         ::minecpp::nbt::verify_tag("Generator", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.type = r.read_str();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

Generator Generator::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return Generator::deserialize_no_header(r);
}

void DimentionData::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Compound, "generator");
   generator.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::String, "type");
   w.write_string_content(type);
   w.end_compound();
}

void DimentionData::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

DimentionData DimentionData::deserialize_no_header(minecpp::nbt::Reader &r) {
   DimentionData result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "generator") {
         ::minecpp::nbt::verify_tag("DimentionData", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.generator = Generator::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "type") {
         ::minecpp::nbt::verify_tag("DimentionData", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.type = r.read_str();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

DimentionData DimentionData::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return DimentionData::deserialize_no_header(r);
}

void Dimentions::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Compound, "minecraft:overworld");
   overworld.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Compound, "minecraft:the_end");
   the_end.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Compound, "minecraft:the_nether");
   the_nether.serialize_no_header(w);
   w.end_compound();
}

void Dimentions::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

Dimentions Dimentions::deserialize_no_header(minecpp::nbt::Reader &r) {
   Dimentions result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "minecraft:overworld") {
         ::minecpp::nbt::verify_tag("Dimentions", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.overworld = DimentionData::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "minecraft:the_end") {
         ::minecpp::nbt::verify_tag("Dimentions", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.the_end = DimentionData::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "minecraft:the_nether") {
         ::minecpp::nbt::verify_tag("Dimentions", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.the_nether = DimentionData::deserialize_no_header(r);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

Dimentions Dimentions::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return Dimentions::deserialize_no_header(r);
}

void WorldGen::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Byte, "bonus_chest");
   w.write_byte_content(static_cast<std::uint8_t>(bonus_chest));
   w.write_header(minecpp::nbt::TagId::Compound, "dimensions");
   dimensions.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Byte, "generate_features");
   w.write_byte_content(static_cast<std::uint8_t>(generate_features));
   w.write_header(minecpp::nbt::TagId::Long, "seed");
   w.write_long_content(seed);
   w.end_compound();
}

void WorldGen::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

WorldGen WorldGen::deserialize_no_header(minecpp::nbt::Reader &r) {
   WorldGen result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "bonus_chest") {
         ::minecpp::nbt::verify_tag("WorldGen", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.bonus_chest = r.read_byte();
         continue;
      }
      if (in_field_name == "dimensions") {
         ::minecpp::nbt::verify_tag("WorldGen", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.dimensions = Dimentions::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "generate_features") {
         ::minecpp::nbt::verify_tag("WorldGen", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.generate_features = r.read_byte();
         continue;
      }
      if (in_field_name == "seed") {
         ::minecpp::nbt::verify_tag("WorldGen", in_field_name, minecpp::nbt::TagId::Long, tagid);
         result.seed = r.read_long();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

WorldGen WorldGen::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return WorldGen::deserialize_no_header(r);
}

void DataPacks::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::LongArray, "Disabled");
   w.write_longs_content(disabled);
   w.end_compound();
}

void DataPacks::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

DataPacks DataPacks::deserialize_no_header(minecpp::nbt::Reader &r) {
   DataPacks result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "Disabled") {
         ::minecpp::nbt::verify_tag("DataPacks", in_field_name, minecpp::nbt::TagId::LongArray, tagid);
         result.disabled = r.read_long_vec();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

DataPacks DataPacks::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return DataPacks::deserialize_no_header(r);
}

void DragonFight::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Byte, "DragonKilled");
   w.write_byte_content(static_cast<std::uint8_t>(dragon_killed));
   w.write_header(minecpp::nbt::TagId::Byte, "PreviouslyKilled");
   w.write_byte_content(static_cast<std::uint8_t>(previously_killed));
   w.end_compound();
}

void DragonFight::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

DragonFight DragonFight::deserialize_no_header(minecpp::nbt::Reader &r) {
   DragonFight result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "DragonKilled") {
         ::minecpp::nbt::verify_tag("DragonFight", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.dragon_killed = r.read_byte();
         continue;
      }
      if (in_field_name == "PreviouslyKilled") {
         ::minecpp::nbt::verify_tag("DragonFight", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.previously_killed = r.read_byte();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

DragonFight DragonFight::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return DragonFight::deserialize_no_header(r);
}

void CustomBossEvents::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Int, "no_empty");
   w.write_int_content(no_empty);
   w.end_compound();
}

void CustomBossEvents::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

CustomBossEvents CustomBossEvents::deserialize_no_header(minecpp::nbt::Reader &r) {
   CustomBossEvents result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "no_empty") {
         ::minecpp::nbt::verify_tag("CustomBossEvents", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.no_empty = r.read_int();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

CustomBossEvents CustomBossEvents::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return CustomBossEvents::deserialize_no_header(r);
}

void Player::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Float, "AbsorptionAmount");
   w.write_float_content(absorption_amount);
   w.write_header(minecpp::nbt::TagId::Short, "Air");
   w.write_short_content(air);
   w.write_header(minecpp::nbt::TagId::Compound, "Brain");
   brain.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Int, "DataVersion");
   w.write_int_content(data_version);
   w.write_header(minecpp::nbt::TagId::Short, "DeathTime");
   w.write_short_content(death_time);
   w.write_header(minecpp::nbt::TagId::String, "Dimension");
   w.write_string_content(dimension);
   w.write_header(minecpp::nbt::TagId::Float, "FallDistance");
   w.write_float_content(fall_distance);
   w.write_header(minecpp::nbt::TagId::Byte, "FallFlying");
   w.write_byte_content(static_cast<std::uint8_t>(fall_flying));
   w.write_header(minecpp::nbt::TagId::Short, "Fire");
   w.write_short_content(fire);
   w.write_header(minecpp::nbt::TagId::Float, "Health");
   w.write_float_content(health);
   w.write_header(minecpp::nbt::TagId::Int, "HurtByTimestamp");
   w.write_int_content(hurt_by_timestamp);
   w.write_header(minecpp::nbt::TagId::Short, "HurtTime");
   w.write_short_content(hurt_time);
   w.write_header(minecpp::nbt::TagId::Byte, "Invulnerable");
   w.write_byte_content(static_cast<std::uint8_t>(invulnerable));
   w.write_header(minecpp::nbt::TagId::Byte, "OnGround");
   w.write_byte_content(static_cast<std::uint8_t>(on_ground));
   w.write_header(minecpp::nbt::TagId::Int, "PortalCooldown");
   w.write_int_content(portal_cooldown);
   w.write_header(minecpp::nbt::TagId::Int, "Score");
   w.write_int_content(score);
   w.write_header(minecpp::nbt::TagId::Int, "SelectedItemSlot");
   w.write_int_content(selected_item_slot);
   w.write_header(minecpp::nbt::TagId::Short, "SleepTimer");
   w.write_short_content(sleep_timer);
   w.write_header(minecpp::nbt::TagId::IntArray, "UUID");
   w.write_ints_content(uuid);
   w.write_header(minecpp::nbt::TagId::Int, "XpLevel");
   w.write_int_content(xp_level);
   w.write_header(minecpp::nbt::TagId::Float, "XpP");
   w.write_float_content(xp_p);
   w.write_header(minecpp::nbt::TagId::Int, "XpSeed");
   w.write_int_content(xp_seed);
   w.write_header(minecpp::nbt::TagId::Int, "XpTotal");
   w.write_int_content(xp_total);
   w.write_header(minecpp::nbt::TagId::Compound, "abilities");
   abilities.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Float, "foodExhaustionLevel");
   w.write_float_content(food_exhaustion_level);
   w.write_header(minecpp::nbt::TagId::Int, "foodLevel");
   w.write_int_content(food_level);
   w.write_header(minecpp::nbt::TagId::Float, "foodSaturationLevel");
   w.write_float_content(food_saturation_level);
   w.write_header(minecpp::nbt::TagId::Int, "foodTickTimer");
   w.write_int_content(food_tick_timer);
   w.write_header(minecpp::nbt::TagId::Int, "playerGameType");
   w.write_int_content(player_game_type);
   w.write_header(minecpp::nbt::TagId::Int, "previousPlayerGameType");
   w.write_int_content(previous_player_game_type);
   w.write_header(minecpp::nbt::TagId::Compound, "recipeBook");
   recipe_book.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Byte, "seenCredits");
   w.write_byte_content(static_cast<std::uint8_t>(seen_credits));
   w.end_compound();
}

void Player::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

Player Player::deserialize_no_header(minecpp::nbt::Reader &r) {
   Player result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "AbsorptionAmount") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Float, tagid);
         result.absorption_amount = r.read_float32();
         continue;
      }
      if (in_field_name == "Air") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Short, tagid);
         result.air = r.read_short();
         continue;
      }
      if (in_field_name == "Brain") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.brain = Brain::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "DataVersion") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.data_version = r.read_int();
         continue;
      }
      if (in_field_name == "DeathTime") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Short, tagid);
         result.death_time = r.read_short();
         continue;
      }
      if (in_field_name == "Dimension") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.dimension = r.read_str();
         continue;
      }
      if (in_field_name == "FallDistance") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Float, tagid);
         result.fall_distance = r.read_float32();
         continue;
      }
      if (in_field_name == "FallFlying") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.fall_flying = r.read_byte();
         continue;
      }
      if (in_field_name == "Fire") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Short, tagid);
         result.fire = r.read_short();
         continue;
      }
      if (in_field_name == "Health") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Float, tagid);
         result.health = r.read_float32();
         continue;
      }
      if (in_field_name == "HurtByTimestamp") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.hurt_by_timestamp = r.read_int();
         continue;
      }
      if (in_field_name == "HurtTime") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Short, tagid);
         result.hurt_time = r.read_short();
         continue;
      }
      if (in_field_name == "Invulnerable") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.invulnerable = r.read_byte();
         continue;
      }
      if (in_field_name == "OnGround") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.on_ground = r.read_byte();
         continue;
      }
      if (in_field_name == "PortalCooldown") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.portal_cooldown = r.read_int();
         continue;
      }
      if (in_field_name == "Score") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.score = r.read_int();
         continue;
      }
      if (in_field_name == "SelectedItemSlot") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.selected_item_slot = r.read_int();
         continue;
      }
      if (in_field_name == "SleepTimer") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Short, tagid);
         result.sleep_timer = r.read_short();
         continue;
      }
      if (in_field_name == "UUID") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::IntArray, tagid);
         result.uuid = r.read_int_vec();
         continue;
      }
      if (in_field_name == "XpLevel") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.xp_level = r.read_int();
         continue;
      }
      if (in_field_name == "XpP") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Float, tagid);
         result.xp_p = r.read_float32();
         continue;
      }
      if (in_field_name == "XpSeed") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.xp_seed = r.read_int();
         continue;
      }
      if (in_field_name == "XpTotal") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.xp_total = r.read_int();
         continue;
      }
      if (in_field_name == "abilities") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.abilities = Abilities::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "foodExhaustionLevel") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Float, tagid);
         result.food_exhaustion_level = r.read_float32();
         continue;
      }
      if (in_field_name == "foodLevel") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.food_level = r.read_int();
         continue;
      }
      if (in_field_name == "foodSaturationLevel") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Float, tagid);
         result.food_saturation_level = r.read_float32();
         continue;
      }
      if (in_field_name == "foodTickTimer") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.food_tick_timer = r.read_int();
         continue;
      }
      if (in_field_name == "playerGameType") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.player_game_type = r.read_int();
         continue;
      }
      if (in_field_name == "previousPlayerGameType") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.previous_player_game_type = r.read_int();
         continue;
      }
      if (in_field_name == "recipeBook") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.recipe_book = RecipeBook::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "seenCredits") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.seen_credits = r.read_byte();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

Player Player::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return Player::deserialize_no_header(r);
}

void GameRules::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "announceAdvancements");
   w.write_string_content(announce_advancements);
   w.write_header(minecpp::nbt::TagId::String, "commandBlockOutput");
   w.write_string_content(command_block_output);
   w.write_header(minecpp::nbt::TagId::String, "disableElytraMovementCheck");
   w.write_string_content(disable_elytra_movement_check);
   w.write_header(minecpp::nbt::TagId::String, "disableRaids");
   w.write_string_content(disable_raids);
   w.write_header(minecpp::nbt::TagId::String, "doDaylightCycle");
   w.write_string_content(do_daylight_cycle);
   w.write_header(minecpp::nbt::TagId::String, "doEntityDrops");
   w.write_string_content(do_entity_drops);
   w.write_header(minecpp::nbt::TagId::String, "doFireTick");
   w.write_string_content(do_fire_tick);
   w.write_header(minecpp::nbt::TagId::String, "doImmediateRespawn");
   w.write_string_content(do_immediate_respawn);
   w.write_header(minecpp::nbt::TagId::String, "doInsomnia");
   w.write_string_content(do_insomnia);
   w.write_header(minecpp::nbt::TagId::String, "doLimitedCrafting");
   w.write_string_content(do_limited_crafting);
   w.write_header(minecpp::nbt::TagId::String, "doMobLoot");
   w.write_string_content(do_mob_loot);
   w.write_header(minecpp::nbt::TagId::String, "doMobSpawning");
   w.write_string_content(do_mob_spawning);
   w.write_header(minecpp::nbt::TagId::String, "doPatrolSpawning");
   w.write_string_content(do_patrol_spawning);
   w.write_header(minecpp::nbt::TagId::String, "doTileDrops");
   w.write_string_content(do_tile_drops);
   w.write_header(minecpp::nbt::TagId::String, "doTraderSpawning");
   w.write_string_content(do_trader_spawning);
   w.write_header(minecpp::nbt::TagId::String, "doWeatherCycle");
   w.write_string_content(do_weather_cycle);
   w.write_header(minecpp::nbt::TagId::String, "drowningDamage");
   w.write_string_content(drowning_damage);
   w.write_header(minecpp::nbt::TagId::String, "fallDamage");
   w.write_string_content(fall_damage);
   w.write_header(minecpp::nbt::TagId::String, "fireDamage");
   w.write_string_content(fire_damage);
   w.write_header(minecpp::nbt::TagId::String, "forgiveDeadPlayers");
   w.write_string_content(forgive_dead_players);
   w.write_header(minecpp::nbt::TagId::String, "keepInventory");
   w.write_string_content(keep_inventory);
   w.write_header(minecpp::nbt::TagId::String, "logAdminCommands");
   w.write_string_content(log_admin_commands);
   w.write_header(minecpp::nbt::TagId::String, "maxCommandChainLength");
   w.write_string_content(max_command_chain_length);
   w.write_header(minecpp::nbt::TagId::String, "maxEntityCramming");
   w.write_string_content(max_entity_cramming);
   w.write_header(minecpp::nbt::TagId::String, "mobGriefing");
   w.write_string_content(mob_griefing);
   w.write_header(minecpp::nbt::TagId::String, "naturalRegeneration");
   w.write_string_content(natural_regeneration);
   w.write_header(minecpp::nbt::TagId::String, "randomTickSpeed");
   w.write_string_content(random_tick_speed);
   w.write_header(minecpp::nbt::TagId::String, "reducedDebugInfo");
   w.write_string_content(reduced_debug_info);
   w.write_header(minecpp::nbt::TagId::String, "sendCommandFeedback");
   w.write_string_content(send_command_feedback);
   w.write_header(minecpp::nbt::TagId::String, "showDeathMessages");
   w.write_string_content(show_death_messages);
   w.write_header(minecpp::nbt::TagId::String, "spawnRadius");
   w.write_string_content(spawn_radius);
   w.write_header(minecpp::nbt::TagId::String, "spectatorsGenerateChunks");
   w.write_string_content(spectators_generate_chunks);
   w.write_header(minecpp::nbt::TagId::String, "universalAnger");
   w.write_string_content(universal_anger);
   w.end_compound();
}

void GameRules::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

GameRules GameRules::deserialize_no_header(minecpp::nbt::Reader &r) {
   GameRules result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "announceAdvancements") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.announce_advancements = r.read_str();
         continue;
      }
      if (in_field_name == "commandBlockOutput") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.command_block_output = r.read_str();
         continue;
      }
      if (in_field_name == "disableElytraMovementCheck") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.disable_elytra_movement_check = r.read_str();
         continue;
      }
      if (in_field_name == "disableRaids") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.disable_raids = r.read_str();
         continue;
      }
      if (in_field_name == "doDaylightCycle") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.do_daylight_cycle = r.read_str();
         continue;
      }
      if (in_field_name == "doEntityDrops") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.do_entity_drops = r.read_str();
         continue;
      }
      if (in_field_name == "doFireTick") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.do_fire_tick = r.read_str();
         continue;
      }
      if (in_field_name == "doImmediateRespawn") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.do_immediate_respawn = r.read_str();
         continue;
      }
      if (in_field_name == "doInsomnia") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.do_insomnia = r.read_str();
         continue;
      }
      if (in_field_name == "doLimitedCrafting") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.do_limited_crafting = r.read_str();
         continue;
      }
      if (in_field_name == "doMobLoot") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.do_mob_loot = r.read_str();
         continue;
      }
      if (in_field_name == "doMobSpawning") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.do_mob_spawning = r.read_str();
         continue;
      }
      if (in_field_name == "doPatrolSpawning") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.do_patrol_spawning = r.read_str();
         continue;
      }
      if (in_field_name == "doTileDrops") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.do_tile_drops = r.read_str();
         continue;
      }
      if (in_field_name == "doTraderSpawning") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.do_trader_spawning = r.read_str();
         continue;
      }
      if (in_field_name == "doWeatherCycle") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.do_weather_cycle = r.read_str();
         continue;
      }
      if (in_field_name == "drowningDamage") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.drowning_damage = r.read_str();
         continue;
      }
      if (in_field_name == "fallDamage") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.fall_damage = r.read_str();
         continue;
      }
      if (in_field_name == "fireDamage") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.fire_damage = r.read_str();
         continue;
      }
      if (in_field_name == "forgiveDeadPlayers") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.forgive_dead_players = r.read_str();
         continue;
      }
      if (in_field_name == "keepInventory") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.keep_inventory = r.read_str();
         continue;
      }
      if (in_field_name == "logAdminCommands") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.log_admin_commands = r.read_str();
         continue;
      }
      if (in_field_name == "maxCommandChainLength") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.max_command_chain_length = r.read_str();
         continue;
      }
      if (in_field_name == "maxEntityCramming") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.max_entity_cramming = r.read_str();
         continue;
      }
      if (in_field_name == "mobGriefing") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.mob_griefing = r.read_str();
         continue;
      }
      if (in_field_name == "naturalRegeneration") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.natural_regeneration = r.read_str();
         continue;
      }
      if (in_field_name == "randomTickSpeed") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.random_tick_speed = r.read_str();
         continue;
      }
      if (in_field_name == "reducedDebugInfo") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.reduced_debug_info = r.read_str();
         continue;
      }
      if (in_field_name == "sendCommandFeedback") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.send_command_feedback = r.read_str();
         continue;
      }
      if (in_field_name == "showDeathMessages") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.show_death_messages = r.read_str();
         continue;
      }
      if (in_field_name == "spawnRadius") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.spawn_radius = r.read_str();
         continue;
      }
      if (in_field_name == "spectatorsGenerateChunks") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.spectators_generate_chunks = r.read_str();
         continue;
      }
      if (in_field_name == "universalAnger") {
         ::minecpp::nbt::verify_tag("GameRules", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.universal_anger = r.read_str();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

GameRules GameRules::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return GameRules::deserialize_no_header(r);
}

void LevelData::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Double, "BorderCenterX");
   w.write_double_content(border_center_x);
   w.write_header(minecpp::nbt::TagId::Double, "BorderCenterZ");
   w.write_double_content(border_center_z);
   w.write_header(minecpp::nbt::TagId::Double, "BorderDamagePerBlock");
   w.write_double_content(border_damage_per_block);
   w.write_header(minecpp::nbt::TagId::Double, "BorderSafeZone");
   w.write_double_content(border_safe_zone);
   w.write_header(minecpp::nbt::TagId::Double, "BorderSize");
   w.write_double_content(border_size);
   w.write_header(minecpp::nbt::TagId::Double, "BorderSizeLerpTarget");
   w.write_double_content(border_size_lerp_target);
   w.write_header(minecpp::nbt::TagId::Long, "BorderSizeLerpTime");
   w.write_long_content(border_size_lerp_time);
   w.write_header(minecpp::nbt::TagId::Double, "BorderWarningBlocks");
   w.write_double_content(border_warning_blocks);
   w.write_header(minecpp::nbt::TagId::Double, "BorderWarningTime");
   w.write_double_content(border_warning_time);
   w.write_header(minecpp::nbt::TagId::Compound, "CustomBossEvents");
   custom_boss_events.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Compound, "DataPacks");
   data_packs.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Int, "DataVersion");
   w.write_int_content(data_version);
   w.write_header(minecpp::nbt::TagId::Long, "DayTime");
   w.write_long_content(day_time);
   w.write_header(minecpp::nbt::TagId::Byte, "Difficulty");
   w.write_byte_content(static_cast<std::uint8_t>(difficulty));
   w.write_header(minecpp::nbt::TagId::Byte, "DifficultyLocked");
   w.write_byte_content(static_cast<std::uint8_t>(difficulty_locked));
   w.write_header(minecpp::nbt::TagId::Compound, "DragonFight");
   dragon_fight.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Compound, "GameRules");
   game_rules.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Int, "GameType");
   w.write_int_content(game_type);
   w.write_header(minecpp::nbt::TagId::Long, "LastPlayed");
   w.write_long_content(last_played);
   w.write_header(minecpp::nbt::TagId::String, "LevelName");
   w.write_string_content(level_name);
   w.write_header(minecpp::nbt::TagId::Compound, "Player");
   player.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Int, "SpawnX");
   w.write_int_content(spawn_x);
   w.write_header(minecpp::nbt::TagId::Int, "SpawnY");
   w.write_int_content(spawn_y);
   w.write_header(minecpp::nbt::TagId::Int, "SpawnZ");
   w.write_int_content(spawn_z);
   w.write_header(minecpp::nbt::TagId::Long, "Time");
   w.write_long_content(time);
   w.write_header(minecpp::nbt::TagId::Compound, "Version");
   version.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Int, "WanderingTraderSpawnChance");
   w.write_int_content(wandering_trader_spawn_chance);
   w.write_header(minecpp::nbt::TagId::Int, "WanderingTraderSpawnDelay");
   w.write_int_content(wandering_trader_spawn_delay);
   w.write_header(minecpp::nbt::TagId::Byte, "WasModded");
   w.write_byte_content(static_cast<std::uint8_t>(was_modded));
   w.write_header(minecpp::nbt::TagId::Compound, "WorldGenSettings");
   world_gen_settings.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Byte, "allowCommands");
   w.write_byte_content(static_cast<std::uint8_t>(allow_commands));
   w.write_header(minecpp::nbt::TagId::Int, "clearWeatherTime");
   w.write_int_content(clear_weather_time);
   w.write_header(minecpp::nbt::TagId::Byte, "hardcore");
   w.write_byte_content(static_cast<std::uint8_t>(hardcore));
   w.write_header(minecpp::nbt::TagId::Byte, "initialized");
   w.write_byte_content(static_cast<std::uint8_t>(initialized));
   w.write_header(minecpp::nbt::TagId::Int, "rainTime");
   w.write_int_content(rain_time);
   w.write_header(minecpp::nbt::TagId::Byte, "raining");
   w.write_byte_content(static_cast<std::uint8_t>(raining));
   w.write_header(minecpp::nbt::TagId::Int, "thunderTime");
   w.write_int_content(thunder_time);
   w.write_header(minecpp::nbt::TagId::Byte, "thundering");
   w.write_byte_content(static_cast<std::uint8_t>(thundering));
   w.write_header(minecpp::nbt::TagId::Int, "version2");
   w.write_int_content(version2);
   w.end_compound();
}

void LevelData::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

LevelData LevelData::deserialize_no_header(minecpp::nbt::Reader &r) {
   LevelData result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "BorderCenterX") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Double, tagid);
         result.border_center_x = r.read_float64();
         continue;
      }
      if (in_field_name == "BorderCenterZ") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Double, tagid);
         result.border_center_z = r.read_float64();
         continue;
      }
      if (in_field_name == "BorderDamagePerBlock") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Double, tagid);
         result.border_damage_per_block = r.read_float64();
         continue;
      }
      if (in_field_name == "BorderSafeZone") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Double, tagid);
         result.border_safe_zone = r.read_float64();
         continue;
      }
      if (in_field_name == "BorderSize") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Double, tagid);
         result.border_size = r.read_float64();
         continue;
      }
      if (in_field_name == "BorderSizeLerpTarget") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Double, tagid);
         result.border_size_lerp_target = r.read_float64();
         continue;
      }
      if (in_field_name == "BorderSizeLerpTime") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Long, tagid);
         result.border_size_lerp_time = r.read_long();
         continue;
      }
      if (in_field_name == "BorderWarningBlocks") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Double, tagid);
         result.border_warning_blocks = r.read_float64();
         continue;
      }
      if (in_field_name == "BorderWarningTime") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Double, tagid);
         result.border_warning_time = r.read_float64();
         continue;
      }
      if (in_field_name == "CustomBossEvents") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.custom_boss_events = CustomBossEvents::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "DataPacks") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.data_packs = DataPacks::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "DataVersion") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.data_version = r.read_int();
         continue;
      }
      if (in_field_name == "DayTime") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Long, tagid);
         result.day_time = r.read_long();
         continue;
      }
      if (in_field_name == "Difficulty") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.difficulty = r.read_byte();
         continue;
      }
      if (in_field_name == "DifficultyLocked") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.difficulty_locked = r.read_byte();
         continue;
      }
      if (in_field_name == "DragonFight") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.dragon_fight = DragonFight::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "GameRules") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.game_rules = GameRules::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "GameType") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.game_type = r.read_int();
         continue;
      }
      if (in_field_name == "LastPlayed") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Long, tagid);
         result.last_played = r.read_long();
         continue;
      }
      if (in_field_name == "LevelName") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.level_name = r.read_str();
         continue;
      }
      if (in_field_name == "Player") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.player = Player::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "SpawnX") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.spawn_x = r.read_int();
         continue;
      }
      if (in_field_name == "SpawnY") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.spawn_y = r.read_int();
         continue;
      }
      if (in_field_name == "SpawnZ") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.spawn_z = r.read_int();
         continue;
      }
      if (in_field_name == "Time") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Long, tagid);
         result.time = r.read_long();
         continue;
      }
      if (in_field_name == "Version") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.version = Version::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "WanderingTraderSpawnChance") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.wandering_trader_spawn_chance = r.read_int();
         continue;
      }
      if (in_field_name == "WanderingTraderSpawnDelay") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.wandering_trader_spawn_delay = r.read_int();
         continue;
      }
      if (in_field_name == "WasModded") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.was_modded = r.read_byte();
         continue;
      }
      if (in_field_name == "WorldGenSettings") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.world_gen_settings = WorldGen::deserialize_no_header(r);
         continue;
      }
      if (in_field_name == "allowCommands") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.allow_commands = r.read_byte();
         continue;
      }
      if (in_field_name == "clearWeatherTime") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.clear_weather_time = r.read_int();
         continue;
      }
      if (in_field_name == "hardcore") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.hardcore = r.read_byte();
         continue;
      }
      if (in_field_name == "initialized") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.initialized = r.read_byte();
         continue;
      }
      if (in_field_name == "rainTime") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.rain_time = r.read_int();
         continue;
      }
      if (in_field_name == "raining") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.raining = r.read_byte();
         continue;
      }
      if (in_field_name == "thunderTime") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.thunder_time = r.read_int();
         continue;
      }
      if (in_field_name == "thundering") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.thundering = r.read_byte();
         continue;
      }
      if (in_field_name == "version2") {
         ::minecpp::nbt::verify_tag("LevelData", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.version2 = r.read_int();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

LevelData LevelData::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return LevelData::deserialize_no_header(r);
}

void Level::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Compound, "Data");
   data.serialize_no_header(w);
   w.end_compound();
}

void Level::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

Level Level::deserialize_no_header(minecpp::nbt::Reader &r) {
   Level result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "Data") {
         ::minecpp::nbt::verify_tag("Level", in_field_name, minecpp::nbt::TagId::Compound, tagid);
         result.data = LevelData::deserialize_no_header(r);
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

Level Level::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return Level::deserialize_no_header(r);
}

}