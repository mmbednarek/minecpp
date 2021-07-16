#include <minecpp/nbt/level/v1/level.nbt.h>

namespace minecpp::nbt::level::v1 {

void Memories::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.end_compound();
}

void Memories::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Memories Memories::deserialize_no_header(minecpp::nbt::Reader &r) {
   Memories res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      r.skip_payload(tagid);
   });
   return res;
}

Memories Memories::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Memories();
   }
   return Memories::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> Memories::__xx_offsets {
};

int Memories::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

void Brain::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Compound, "memories");
   memories.serialize_no_header(w);
   w.end_compound();
}

void Brain::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Brain Brain::deserialize_no_header(minecpp::nbt::Reader &r) {
   Brain res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Compound:
         switch (res.__xx_get_id(name)) {
         case 1:
            res.__xx_put(name, Memories::deserialize_no_header(r));
            return;
         }
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
}

Brain Brain::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Brain();
   }
   return Brain::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> Brain::__xx_offsets {
   {"memories", {offsetof(Brain, memories), sizeof(Brain::memories), 1}},
};

int Brain::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

void Abilities::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Float, "flySpeed");
   w.write_float_content(fly_speed);
   w.write_header(minecpp::nbt::TagId::Byte, "flying");
   w.write_byte_content(flying);
   w.write_header(minecpp::nbt::TagId::Byte, "instabuild");
   w.write_byte_content(instabuild);
   w.write_header(minecpp::nbt::TagId::Byte, "invulnerable");
   w.write_byte_content(invulnerable);
   w.write_header(minecpp::nbt::TagId::Byte, "mayBuild");
   w.write_byte_content(may_build);
   w.write_header(minecpp::nbt::TagId::Byte, "mayfly");
   w.write_byte_content(mayfly);
   w.write_header(minecpp::nbt::TagId::Float, "walkSpeed");
   w.write_float_content(walk_speed);
   w.end_compound();
}

void Abilities::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Abilities Abilities::deserialize_no_header(minecpp::nbt::Reader &r) {
   Abilities res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Byte:
         res.__xx_put(name, r.read_byte());
         return;
      case minecpp::nbt::TagId::Float:
         res.__xx_put(name, r.read_float32());
         return;
      }
      r.skip_payload(tagid);
   });
   return res;
}

Abilities Abilities::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Abilities();
   }
   return Abilities::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> Abilities::__xx_offsets {
   {"flySpeed", {offsetof(Abilities, fly_speed), sizeof(Abilities::fly_speed), 1}},
   {"flying", {offsetof(Abilities, flying), sizeof(Abilities::flying), 2}},
   {"instabuild", {offsetof(Abilities, instabuild), sizeof(Abilities::instabuild), 3}},
   {"invulnerable", {offsetof(Abilities, invulnerable), sizeof(Abilities::invulnerable), 4}},
   {"mayBuild", {offsetof(Abilities, may_build), sizeof(Abilities::may_build), 5}},
   {"mayfly", {offsetof(Abilities, mayfly), sizeof(Abilities::mayfly), 6}},
   {"walkSpeed", {offsetof(Abilities, walk_speed), sizeof(Abilities::walk_speed), 7}},
};

int Abilities::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

void RecipeBook::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Byte, "isBlastingFurnaceFilteringCraftable");
   w.write_byte_content(is_blasting_furnace_filtering_craftable);
   w.write_header(minecpp::nbt::TagId::Byte, "isBlastingFurnaceGuiOpen");
   w.write_byte_content(is_blasting_furnace_gui_open);
   w.write_header(minecpp::nbt::TagId::Byte, "isFilteringCraftable");
   w.write_byte_content(is_filtering_craftable);
   w.write_header(minecpp::nbt::TagId::Byte, "isFurnaceFilteringCraftable");
   w.write_byte_content(is_furnace_filtering_craftable);
   w.write_header(minecpp::nbt::TagId::Byte, "isFurnaceGuiOpen");
   w.write_byte_content(is_furnace_gui_open);
   w.write_header(minecpp::nbt::TagId::Byte, "isGuiOpen");
   w.write_byte_content(is_gui_open);
   w.write_header(minecpp::nbt::TagId::Byte, "isSmokerFilteringCraftable");
   w.write_byte_content(is_smoker_filtering_craftable);
   w.write_header(minecpp::nbt::TagId::Byte, "isSmokerGuiOpen");
   w.write_byte_content(is_smoker_gui_open);
   w.end_compound();
}

void RecipeBook::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

RecipeBook RecipeBook::deserialize_no_header(minecpp::nbt::Reader &r) {
   RecipeBook res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Byte:
         res.__xx_put(name, r.read_byte());
         return;
      }
      r.skip_payload(tagid);
   });
   return res;
}

RecipeBook RecipeBook::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return RecipeBook();
   }
   return RecipeBook::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> RecipeBook::__xx_offsets {
   {"isBlastingFurnaceFilteringCraftable", {offsetof(RecipeBook, is_blasting_furnace_filtering_craftable), sizeof(RecipeBook::is_blasting_furnace_filtering_craftable), 1}},
   {"isBlastingFurnaceGuiOpen", {offsetof(RecipeBook, is_blasting_furnace_gui_open), sizeof(RecipeBook::is_blasting_furnace_gui_open), 2}},
   {"isFilteringCraftable", {offsetof(RecipeBook, is_filtering_craftable), sizeof(RecipeBook::is_filtering_craftable), 3}},
   {"isFurnaceFilteringCraftable", {offsetof(RecipeBook, is_furnace_filtering_craftable), sizeof(RecipeBook::is_furnace_filtering_craftable), 4}},
   {"isFurnaceGuiOpen", {offsetof(RecipeBook, is_furnace_gui_open), sizeof(RecipeBook::is_furnace_gui_open), 5}},
   {"isGuiOpen", {offsetof(RecipeBook, is_gui_open), sizeof(RecipeBook::is_gui_open), 6}},
   {"isSmokerFilteringCraftable", {offsetof(RecipeBook, is_smoker_filtering_craftable), sizeof(RecipeBook::is_smoker_filtering_craftable), 7}},
   {"isSmokerGuiOpen", {offsetof(RecipeBook, is_smoker_gui_open), sizeof(RecipeBook::is_smoker_gui_open), 8}},
};

int RecipeBook::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

void Version::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Int, "Id");
   w.write_int_content(id);
   w.write_header(minecpp::nbt::TagId::String, "Name");
   w.write_string_content(name);
   w.write_header(minecpp::nbt::TagId::Byte, "Snapshot");
   w.write_byte_content(snapshot);
   w.end_compound();
}

void Version::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Version Version::deserialize_no_header(minecpp::nbt::Reader &r) {
   Version res;
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
      }
      r.skip_payload(tagid);
   });
   return res;
}

Version Version::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Version();
   }
   return Version::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> Version::__xx_offsets {
   {"Id", {offsetof(Version, id), sizeof(Version::id), 1}},
   {"Name", {offsetof(Version, name), sizeof(Version::name), 2}},
   {"Snapshot", {offsetof(Version, snapshot), sizeof(Version::snapshot), 3}},
};

int Version::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

void BiomeSource::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::String, "preset");
   w.write_string_content(preset);
   w.write_header(minecpp::nbt::TagId::Byte, "large_biomes");
   w.write_byte_content(large_biomes);
   w.write_header(minecpp::nbt::TagId::Long, "seed");
   w.write_long_content(seed);
   w.write_header(minecpp::nbt::TagId::String, "type");
   w.write_string_content(type);
   w.end_compound();
}

void BiomeSource::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

BiomeSource BiomeSource::deserialize_no_header(minecpp::nbt::Reader &r) {
   BiomeSource res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Byte:
         res.__xx_put(name, r.read_byte());
         return;
      case minecpp::nbt::TagId::Long:
         res.__xx_put(name, r.read_long());
         return;
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      }
      r.skip_payload(tagid);
   });
   return res;
}

BiomeSource BiomeSource::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return BiomeSource();
   }
   return BiomeSource::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> BiomeSource::__xx_offsets {
   {"preset", {offsetof(BiomeSource, preset), sizeof(BiomeSource::preset), 1}},
   {"large_biomes", {offsetof(BiomeSource, large_biomes), sizeof(BiomeSource::large_biomes), 2}},
   {"seed", {offsetof(BiomeSource, seed), sizeof(BiomeSource::seed), 3}},
   {"type", {offsetof(BiomeSource, type), sizeof(BiomeSource::type), 4}},
};

int BiomeSource::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
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

void Generator::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Generator Generator::deserialize_no_header(minecpp::nbt::Reader &r) {
   Generator res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Long:
         res.__xx_put(name, r.read_long());
         return;
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      case minecpp::nbt::TagId::Compound:
         switch (res.__xx_get_id(name)) {
         case 1:
            res.__xx_put(name, BiomeSource::deserialize_no_header(r));
            return;
         }
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
}

Generator Generator::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Generator();
   }
   return Generator::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> Generator::__xx_offsets {
   {"biome_source", {offsetof(Generator, biome_source), sizeof(Generator::biome_source), 1}},
   {"seed", {offsetof(Generator, seed), sizeof(Generator::seed), 2}},
   {"settings", {offsetof(Generator, settings), sizeof(Generator::settings), 3}},
   {"type", {offsetof(Generator, type), sizeof(Generator::type), 4}},
};

int Generator::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

void DimentionData::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Compound, "generator");
   generator.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::String, "type");
   w.write_string_content(type);
   w.end_compound();
}

void DimentionData::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

DimentionData DimentionData::deserialize_no_header(minecpp::nbt::Reader &r) {
   DimentionData res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      case minecpp::nbt::TagId::Compound:
         switch (res.__xx_get_id(name)) {
         case 1:
            res.__xx_put(name, Generator::deserialize_no_header(r));
            return;
         }
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
}

DimentionData DimentionData::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return DimentionData();
   }
   return DimentionData::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> DimentionData::__xx_offsets {
   {"generator", {offsetof(DimentionData, generator), sizeof(DimentionData::generator), 1}},
   {"type", {offsetof(DimentionData, type), sizeof(DimentionData::type), 2}},
};

int DimentionData::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
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

void Dimentions::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Dimentions Dimentions::deserialize_no_header(minecpp::nbt::Reader &r) {
   Dimentions res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Compound:
         switch (res.__xx_get_id(name)) {
         case 1:
            res.__xx_put(name, DimentionData::deserialize_no_header(r));
            return;
         case 2:
            res.__xx_put(name, DimentionData::deserialize_no_header(r));
            return;
         case 3:
            res.__xx_put(name, DimentionData::deserialize_no_header(r));
            return;
         }
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
}

Dimentions Dimentions::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Dimentions();
   }
   return Dimentions::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> Dimentions::__xx_offsets {
   {"minecraft:overworld", {offsetof(Dimentions, overworld), sizeof(Dimentions::overworld), 1}},
   {"minecraft:the_end", {offsetof(Dimentions, the_end), sizeof(Dimentions::the_end), 2}},
   {"minecraft:the_nether", {offsetof(Dimentions, the_nether), sizeof(Dimentions::the_nether), 3}},
};

int Dimentions::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

void WorldGen::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Byte, "bonus_chest");
   w.write_byte_content(bonus_chest);
   w.write_header(minecpp::nbt::TagId::Compound, "dimensions");
   dimensions.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Byte, "generate_features");
   w.write_byte_content(generate_features);
   w.write_header(minecpp::nbt::TagId::Long, "seed");
   w.write_long_content(seed);
   w.end_compound();
}

void WorldGen::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

WorldGen WorldGen::deserialize_no_header(minecpp::nbt::Reader &r) {
   WorldGen res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Byte:
         res.__xx_put(name, r.read_byte());
         return;
      case minecpp::nbt::TagId::Long:
         res.__xx_put(name, r.read_long());
         return;
      case minecpp::nbt::TagId::Compound:
         switch (res.__xx_get_id(name)) {
         case 2:
            res.__xx_put(name, Dimentions::deserialize_no_header(r));
            return;
         }
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
}

WorldGen WorldGen::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return WorldGen();
   }
   return WorldGen::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> WorldGen::__xx_offsets {
   {"bonus_chest", {offsetof(WorldGen, bonus_chest), sizeof(WorldGen::bonus_chest), 1}},
   {"dimensions", {offsetof(WorldGen, dimensions), sizeof(WorldGen::dimensions), 2}},
   {"generate_features", {offsetof(WorldGen, generate_features), sizeof(WorldGen::generate_features), 3}},
   {"seed", {offsetof(WorldGen, seed), sizeof(WorldGen::seed), 4}},
};

int WorldGen::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

void DataPacks::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::LongArray, "Disabled");
   w.write_longs_content(disabled);
   w.end_compound();
}

void DataPacks::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

DataPacks DataPacks::deserialize_no_header(minecpp::nbt::Reader &r) {
   DataPacks res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::LongArray:
         res.__xx_put(name, r.read_long_vec());
         return;
      }
      r.skip_payload(tagid);
   });
   return res;
}

DataPacks DataPacks::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return DataPacks();
   }
   return DataPacks::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> DataPacks::__xx_offsets {
   {"Disabled", {offsetof(DataPacks, disabled), sizeof(DataPacks::disabled), 1}},
};

int DataPacks::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

void DragonFight::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Byte, "DragonKilled");
   w.write_byte_content(dragon_killed);
   w.write_header(minecpp::nbt::TagId::Byte, "PreviouslyKilled");
   w.write_byte_content(previously_killed);
   w.end_compound();
}

void DragonFight::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

DragonFight DragonFight::deserialize_no_header(minecpp::nbt::Reader &r) {
   DragonFight res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Byte:
         res.__xx_put(name, r.read_byte());
         return;
      }
      r.skip_payload(tagid);
   });
   return res;
}

DragonFight DragonFight::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return DragonFight();
   }
   return DragonFight::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> DragonFight::__xx_offsets {
   {"DragonKilled", {offsetof(DragonFight, dragon_killed), sizeof(DragonFight::dragon_killed), 1}},
   {"PreviouslyKilled", {offsetof(DragonFight, previously_killed), sizeof(DragonFight::previously_killed), 3}},
};

int DragonFight::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

void CustomBossEvents::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.end_compound();
}

void CustomBossEvents::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

CustomBossEvents CustomBossEvents::deserialize_no_header(minecpp::nbt::Reader &r) {
   CustomBossEvents res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      r.skip_payload(tagid);
   });
   return res;
}

CustomBossEvents CustomBossEvents::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return CustomBossEvents();
   }
   return CustomBossEvents::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> CustomBossEvents::__xx_offsets {
};

int CustomBossEvents::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
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
   w.write_byte_content(fall_flying);
   w.write_header(minecpp::nbt::TagId::Short, "Fire");
   w.write_short_content(fire);
   w.write_header(minecpp::nbt::TagId::Float, "Health");
   w.write_float_content(health);
   w.write_header(minecpp::nbt::TagId::Int, "HurtByTimestamp");
   w.write_int_content(hurt_by_timestamp);
   w.write_header(minecpp::nbt::TagId::Short, "HurtTime");
   w.write_short_content(hurt_time);
   w.write_header(minecpp::nbt::TagId::Byte, "Invulnerable");
   w.write_byte_content(invulnerable);
   w.write_header(minecpp::nbt::TagId::Byte, "OnGround");
   w.write_byte_content(on_ground);
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
   w.write_byte_content(seen_credits);
   w.end_compound();
}

void Player::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Player Player::deserialize_no_header(minecpp::nbt::Reader &r) {
   Player res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Byte:
         res.__xx_put(name, r.read_byte());
         return;
      case minecpp::nbt::TagId::Short:
         res.__xx_put(name, r.read_short());
         return;
      case minecpp::nbt::TagId::Int:
         res.__xx_put(name, r.read_int());
         return;
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      case minecpp::nbt::TagId::Float:
         res.__xx_put(name, r.read_float32());
         return;
      case minecpp::nbt::TagId::IntArray:
         res.__xx_put(name, r.read_int_vec());
         return;
      case minecpp::nbt::TagId::Compound:
         switch (res.__xx_get_id(name)) {
         case 4:
            res.__xx_put(name, Brain::deserialize_no_header(r));
            return;
         case 30:
            res.__xx_put(name, Abilities::deserialize_no_header(r));
            return;
         case 37:
            res.__xx_put(name, RecipeBook::deserialize_no_header(r));
            return;
         }
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
}

Player Player::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Player();
   }
   return Player::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> Player::__xx_offsets {
   {"AbsorptionAmount", {offsetof(Player, absorption_amount), sizeof(Player::absorption_amount), 1}},
   {"Air", {offsetof(Player, air), sizeof(Player::air), 2}},
   {"Brain", {offsetof(Player, brain), sizeof(Player::brain), 4}},
   {"DataVersion", {offsetof(Player, data_version), sizeof(Player::data_version), 5}},
   {"DeathTime", {offsetof(Player, death_time), sizeof(Player::death_time), 6}},
   {"Dimension", {offsetof(Player, dimension), sizeof(Player::dimension), 7}},
   {"FallDistance", {offsetof(Player, fall_distance), sizeof(Player::fall_distance), 9}},
   {"FallFlying", {offsetof(Player, fall_flying), sizeof(Player::fall_flying), 10}},
   {"Fire", {offsetof(Player, fire), sizeof(Player::fire), 11}},
   {"Health", {offsetof(Player, health), sizeof(Player::health), 12}},
   {"HurtByTimestamp", {offsetof(Player, hurt_by_timestamp), sizeof(Player::hurt_by_timestamp), 13}},
   {"HurtTime", {offsetof(Player, hurt_time), sizeof(Player::hurt_time), 14}},
   {"Invulnerable", {offsetof(Player, invulnerable), sizeof(Player::invulnerable), 16}},
   {"OnGround", {offsetof(Player, on_ground), sizeof(Player::on_ground), 18}},
   {"PortalCooldown", {offsetof(Player, portal_cooldown), sizeof(Player::portal_cooldown), 19}},
   {"Score", {offsetof(Player, score), sizeof(Player::score), 22}},
   {"SelectedItemSlot", {offsetof(Player, selected_item_slot), sizeof(Player::selected_item_slot), 23}},
   {"SleepTimer", {offsetof(Player, sleep_timer), sizeof(Player::sleep_timer), 24}},
   {"UUID", {offsetof(Player, uuid), sizeof(Player::uuid), 25}},
   {"XpLevel", {offsetof(Player, xp_level), sizeof(Player::xp_level), 26}},
   {"XpP", {offsetof(Player, xp_p), sizeof(Player::xp_p), 27}},
   {"XpSeed", {offsetof(Player, xp_seed), sizeof(Player::xp_seed), 28}},
   {"XpTotal", {offsetof(Player, xp_total), sizeof(Player::xp_total), 29}},
   {"abilities", {offsetof(Player, abilities), sizeof(Player::abilities), 30}},
   {"foodExhaustionLevel", {offsetof(Player, food_exhaustion_level), sizeof(Player::food_exhaustion_level), 31}},
   {"foodLevel", {offsetof(Player, food_level), sizeof(Player::food_level), 32}},
   {"foodSaturationLevel", {offsetof(Player, food_saturation_level), sizeof(Player::food_saturation_level), 33}},
   {"foodTickTimer", {offsetof(Player, food_tick_timer), sizeof(Player::food_tick_timer), 34}},
   {"playerGameType", {offsetof(Player, player_game_type), sizeof(Player::player_game_type), 35}},
   {"previousPlayerGameType", {offsetof(Player, previous_player_game_type), sizeof(Player::previous_player_game_type), 36}},
   {"recipeBook", {offsetof(Player, recipe_book), sizeof(Player::recipe_book), 37}},
   {"seenCredits", {offsetof(Player, seen_credits), sizeof(Player::seen_credits), 38}},
};

int Player::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
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

void GameRules::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

GameRules GameRules::deserialize_no_header(minecpp::nbt::Reader &r) {
   GameRules res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      }
      r.skip_payload(tagid);
   });
   return res;
}

GameRules GameRules::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return GameRules();
   }
   return GameRules::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> GameRules::__xx_offsets {
   {"announceAdvancements", {offsetof(GameRules, announce_advancements), sizeof(GameRules::announce_advancements), 1}},
   {"commandBlockOutput", {offsetof(GameRules, command_block_output), sizeof(GameRules::command_block_output), 2}},
   {"disableElytraMovementCheck", {offsetof(GameRules, disable_elytra_movement_check), sizeof(GameRules::disable_elytra_movement_check), 3}},
   {"disableRaids", {offsetof(GameRules, disable_raids), sizeof(GameRules::disable_raids), 4}},
   {"doDaylightCycle", {offsetof(GameRules, do_daylight_cycle), sizeof(GameRules::do_daylight_cycle), 5}},
   {"doEntityDrops", {offsetof(GameRules, do_entity_drops), sizeof(GameRules::do_entity_drops), 6}},
   {"doFireTick", {offsetof(GameRules, do_fire_tick), sizeof(GameRules::do_fire_tick), 7}},
   {"doImmediateRespawn", {offsetof(GameRules, do_immediate_respawn), sizeof(GameRules::do_immediate_respawn), 8}},
   {"doInsomnia", {offsetof(GameRules, do_insomnia), sizeof(GameRules::do_insomnia), 9}},
   {"doLimitedCrafting", {offsetof(GameRules, do_limited_crafting), sizeof(GameRules::do_limited_crafting), 10}},
   {"doMobLoot", {offsetof(GameRules, do_mob_loot), sizeof(GameRules::do_mob_loot), 11}},
   {"doMobSpawning", {offsetof(GameRules, do_mob_spawning), sizeof(GameRules::do_mob_spawning), 12}},
   {"doPatrolSpawning", {offsetof(GameRules, do_patrol_spawning), sizeof(GameRules::do_patrol_spawning), 13}},
   {"doTileDrops", {offsetof(GameRules, do_tile_drops), sizeof(GameRules::do_tile_drops), 14}},
   {"doTraderSpawning", {offsetof(GameRules, do_trader_spawning), sizeof(GameRules::do_trader_spawning), 15}},
   {"doWeatherCycle", {offsetof(GameRules, do_weather_cycle), sizeof(GameRules::do_weather_cycle), 16}},
   {"drowningDamage", {offsetof(GameRules, drowning_damage), sizeof(GameRules::drowning_damage), 17}},
   {"fallDamage", {offsetof(GameRules, fall_damage), sizeof(GameRules::fall_damage), 18}},
   {"fireDamage", {offsetof(GameRules, fire_damage), sizeof(GameRules::fire_damage), 19}},
   {"forgiveDeadPlayers", {offsetof(GameRules, forgive_dead_players), sizeof(GameRules::forgive_dead_players), 20}},
   {"keepInventory", {offsetof(GameRules, keep_inventory), sizeof(GameRules::keep_inventory), 21}},
   {"logAdminCommands", {offsetof(GameRules, log_admin_commands), sizeof(GameRules::log_admin_commands), 22}},
   {"maxCommandChainLength", {offsetof(GameRules, max_command_chain_length), sizeof(GameRules::max_command_chain_length), 23}},
   {"maxEntityCramming", {offsetof(GameRules, max_entity_cramming), sizeof(GameRules::max_entity_cramming), 24}},
   {"mobGriefing", {offsetof(GameRules, mob_griefing), sizeof(GameRules::mob_griefing), 25}},
   {"naturalRegeneration", {offsetof(GameRules, natural_regeneration), sizeof(GameRules::natural_regeneration), 26}},
   {"randomTickSpeed", {offsetof(GameRules, random_tick_speed), sizeof(GameRules::random_tick_speed), 27}},
   {"reducedDebugInfo", {offsetof(GameRules, reduced_debug_info), sizeof(GameRules::reduced_debug_info), 28}},
   {"sendCommandFeedback", {offsetof(GameRules, send_command_feedback), sizeof(GameRules::send_command_feedback), 29}},
   {"showDeathMessages", {offsetof(GameRules, show_death_messages), sizeof(GameRules::show_death_messages), 30}},
   {"spawnRadius", {offsetof(GameRules, spawn_radius), sizeof(GameRules::spawn_radius), 31}},
   {"spectatorsGenerateChunks", {offsetof(GameRules, spectators_generate_chunks), sizeof(GameRules::spectators_generate_chunks), 32}},
   {"universalAnger", {offsetof(GameRules, universal_anger), sizeof(GameRules::universal_anger), 33}},
};

int GameRules::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
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
   w.write_byte_content(difficulty);
   w.write_header(minecpp::nbt::TagId::Byte, "DifficultyLocked");
   w.write_byte_content(difficulty_locked);
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
   w.write_byte_content(was_modded);
   w.write_header(minecpp::nbt::TagId::Compound, "WorldGenSettings");
   world_gen_settings.serialize_no_header(w);
   w.write_header(minecpp::nbt::TagId::Byte, "allowCommands");
   w.write_byte_content(allow_commands);
   w.write_header(minecpp::nbt::TagId::Int, "clearWeatherTime");
   w.write_int_content(clear_weather_time);
   w.write_header(minecpp::nbt::TagId::Byte, "hardcore");
   w.write_byte_content(hardcore);
   w.write_header(minecpp::nbt::TagId::Byte, "initialized");
   w.write_byte_content(initialized);
   w.write_header(minecpp::nbt::TagId::Int, "rainTime");
   w.write_int_content(rain_time);
   w.write_header(minecpp::nbt::TagId::Byte, "raining");
   w.write_byte_content(raining);
   w.write_header(minecpp::nbt::TagId::Int, "thunderTime");
   w.write_int_content(thunder_time);
   w.write_header(minecpp::nbt::TagId::Byte, "thundering");
   w.write_byte_content(thundering);
   w.write_header(minecpp::nbt::TagId::Int, "version2");
   w.write_int_content(version2);
   w.end_compound();
}

void LevelData::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

LevelData LevelData::deserialize_no_header(minecpp::nbt::Reader &r) {
   LevelData res;
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
      case minecpp::nbt::TagId::Double:
         res.__xx_put(name, r.read_float64());
         return;
      case minecpp::nbt::TagId::Compound:
         switch (res.__xx_get_id(name)) {
         case 10:
            res.__xx_put(name, CustomBossEvents::deserialize_no_header(r));
            return;
         case 11:
            res.__xx_put(name, DataPacks::deserialize_no_header(r));
            return;
         case 16:
            res.__xx_put(name, DragonFight::deserialize_no_header(r));
            return;
         case 17:
            res.__xx_put(name, GameRules::deserialize_no_header(r));
            return;
         case 21:
            res.__xx_put(name, Player::deserialize_no_header(r));
            return;
         case 28:
            res.__xx_put(name, Version::deserialize_no_header(r));
            return;
         case 32:
            res.__xx_put(name, WorldGen::deserialize_no_header(r));
            return;
         }
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
}

LevelData LevelData::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return LevelData();
   }
   return LevelData::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> LevelData::__xx_offsets {
   {"BorderCenterX", {offsetof(LevelData, border_center_x), sizeof(LevelData::border_center_x), 1}},
   {"BorderCenterZ", {offsetof(LevelData, border_center_z), sizeof(LevelData::border_center_z), 2}},
   {"BorderDamagePerBlock", {offsetof(LevelData, border_damage_per_block), sizeof(LevelData::border_damage_per_block), 3}},
   {"BorderSafeZone", {offsetof(LevelData, border_safe_zone), sizeof(LevelData::border_safe_zone), 4}},
   {"BorderSize", {offsetof(LevelData, border_size), sizeof(LevelData::border_size), 5}},
   {"BorderSizeLerpTarget", {offsetof(LevelData, border_size_lerp_target), sizeof(LevelData::border_size_lerp_target), 6}},
   {"BorderSizeLerpTime", {offsetof(LevelData, border_size_lerp_time), sizeof(LevelData::border_size_lerp_time), 7}},
   {"BorderWarningBlocks", {offsetof(LevelData, border_warning_blocks), sizeof(LevelData::border_warning_blocks), 8}},
   {"BorderWarningTime", {offsetof(LevelData, border_warning_time), sizeof(LevelData::border_warning_time), 9}},
   {"CustomBossEvents", {offsetof(LevelData, custom_boss_events), sizeof(LevelData::custom_boss_events), 10}},
   {"DataPacks", {offsetof(LevelData, data_packs), sizeof(LevelData::data_packs), 11}},
   {"DataVersion", {offsetof(LevelData, data_version), sizeof(LevelData::data_version), 12}},
   {"DayTime", {offsetof(LevelData, day_time), sizeof(LevelData::day_time), 13}},
   {"Difficulty", {offsetof(LevelData, difficulty), sizeof(LevelData::difficulty), 14}},
   {"DifficultyLocked", {offsetof(LevelData, difficulty_locked), sizeof(LevelData::difficulty_locked), 15}},
   {"DragonFight", {offsetof(LevelData, dragon_fight), sizeof(LevelData::dragon_fight), 16}},
   {"GameRules", {offsetof(LevelData, game_rules), sizeof(LevelData::game_rules), 17}},
   {"GameType", {offsetof(LevelData, game_type), sizeof(LevelData::game_type), 18}},
   {"LastPlayed", {offsetof(LevelData, last_played), sizeof(LevelData::last_played), 19}},
   {"LevelName", {offsetof(LevelData, level_name), sizeof(LevelData::level_name), 20}},
   {"Player", {offsetof(LevelData, player), sizeof(LevelData::player), 21}},
   {"SpawnX", {offsetof(LevelData, spawn_x), sizeof(LevelData::spawn_x), 24}},
   {"SpawnY", {offsetof(LevelData, spawn_y), sizeof(LevelData::spawn_y), 25}},
   {"SpawnZ", {offsetof(LevelData, spawn_z), sizeof(LevelData::spawn_z), 26}},
   {"Time", {offsetof(LevelData, time), sizeof(LevelData::time), 27}},
   {"Version", {offsetof(LevelData, version), sizeof(LevelData::version), 28}},
   {"WanderingTraderSpawnChance", {offsetof(LevelData, wandering_trader_spawn_chance), sizeof(LevelData::wandering_trader_spawn_chance), 29}},
   {"WanderingTraderSpawnDelay", {offsetof(LevelData, wandering_trader_spawn_delay), sizeof(LevelData::wandering_trader_spawn_delay), 30}},
   {"WasModded", {offsetof(LevelData, was_modded), sizeof(LevelData::was_modded), 31}},
   {"WorldGenSettings", {offsetof(LevelData, world_gen_settings), sizeof(LevelData::world_gen_settings), 32}},
   {"allowCommands", {offsetof(LevelData, allow_commands), sizeof(LevelData::allow_commands), 33}},
   {"clearWeatherTime", {offsetof(LevelData, clear_weather_time), sizeof(LevelData::clear_weather_time), 34}},
   {"hardcore", {offsetof(LevelData, hardcore), sizeof(LevelData::hardcore), 35}},
   {"initialized", {offsetof(LevelData, initialized), sizeof(LevelData::initialized), 36}},
   {"rainTime", {offsetof(LevelData, rain_time), sizeof(LevelData::rain_time), 37}},
   {"raining", {offsetof(LevelData, raining), sizeof(LevelData::raining), 38}},
   {"thunderTime", {offsetof(LevelData, thunder_time), sizeof(LevelData::thunder_time), 39}},
   {"thundering", {offsetof(LevelData, thundering), sizeof(LevelData::thundering), 40}},
   {"version2", {offsetof(LevelData, version2), sizeof(LevelData::version2), 41}},
};

int LevelData::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

void Level::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Compound, "Data");
   data.serialize_no_header(w);
   w.end_compound();
}

void Level::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Level Level::deserialize_no_header(minecpp::nbt::Reader &r) {
   Level res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Compound:
         switch (res.__xx_get_id(name)) {
         case 1:
            res.__xx_put(name, LevelData::deserialize_no_header(r));
            return;
         }
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
}

Level Level::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Level();
   }
   return Level::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> Level::__xx_offsets {
   {"Data", {offsetof(Level, data), sizeof(Level::data), 1}},
};

int Level::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

}