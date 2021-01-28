// Generated using ProtoNBT generator
#include "level.h"

namespace Game::NbtLevel {

int Memories::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void Memories::serialize_no_header(NBT::Writer &w) const {
   w.end_compound();
}

void Memories::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> Memories::__xx_offsets {
};

Memories Memories::deserialize_no_header(NBT::Reader &r) {
   Memories res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      }
      r.skip_payload(tagid);
   });

   return res;
}

Memories Memories::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return Memories();
   }
   return Memories::deserialize_no_header(r);
}

int Brain::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void Brain::serialize_no_header(NBT::Writer &w) const {
   w.begin_compound("memories");
   this->memories.serialize_no_header(w);
   w.end_compound();
}

void Brain::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> Brain::__xx_offsets {
   {"memories", {offsetof(Brain, memories), sizeof(Brain::memories), 1}},
};

Brain Brain::deserialize_no_header(NBT::Reader &r) {
   Brain res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      case NBT::TagId::Compound: {
         switch(res.__xx_get_id(name)) {
            case 1:
               res.__xx_put(name, Memories::deserialize_no_header(r));
               return;
         }
         break;
      }
      }
      r.skip_payload(tagid);
   });

   return res;
}

Brain Brain::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return Brain();
   }
   return Brain::deserialize_no_header(r);
}

int Abilities::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void Abilities::serialize_no_header(NBT::Writer &w) const {
   w.write_float("flySpeed", this->fly_speed);
   w.write_byte("flying", this->flying);
   w.write_byte("instabuild", this->instabuild);
   w.write_byte("invulnerable", this->invulnerable);
   w.write_byte("mayBuild", this->may_build);
   w.write_byte("mayfly", this->mayfly);
   w.write_float("walkSpeed", this->walk_speed);
   w.end_compound();
}

void Abilities::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> Abilities::__xx_offsets {
   {"flySpeed", {offsetof(Abilities, fly_speed), sizeof(Abilities::fly_speed), 1}},
   {"flying", {offsetof(Abilities, flying), sizeof(Abilities::flying), 2}},
   {"instabuild", {offsetof(Abilities, instabuild), sizeof(Abilities::instabuild), 3}},
   {"invulnerable", {offsetof(Abilities, invulnerable), sizeof(Abilities::invulnerable), 4}},
   {"mayBuild", {offsetof(Abilities, may_build), sizeof(Abilities::may_build), 5}},
   {"mayfly", {offsetof(Abilities, mayfly), sizeof(Abilities::mayfly), 6}},
   {"walkSpeed", {offsetof(Abilities, walk_speed), sizeof(Abilities::walk_speed), 7}},
};

Abilities Abilities::deserialize_no_header(NBT::Reader &r) {
   Abilities res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      case NBT::TagId::Byte: 
         res.__xx_put(name, r.read_byte());
         return;
      case NBT::TagId::Float: 
         res.__xx_put(name, r.read_float32());
         return;
      }
      r.skip_payload(tagid);
   });

   return res;
}

Abilities Abilities::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return Abilities();
   }
   return Abilities::deserialize_no_header(r);
}

int RecipeBook::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void RecipeBook::serialize_no_header(NBT::Writer &w) const {
   w.write_byte("isBlastingFurnaceFilteringCraftable", this->is_blasting_furnace_filtering_craftable);
   w.write_byte("isBlastingFurnaceGuiOpen", this->is_blasting_furnace_gui_open);
   w.write_byte("isFilteringCraftable", this->is_filtering_craftable);
   w.write_byte("isFurnaceFilteringCraftable", this->is_furnace_filtering_craftable);
   w.write_byte("isFurnaceGuiOpen", this->is_furnace_gui_open);
   w.write_byte("isGuiOpen", this->is_gui_open);
   w.write_byte("isSmokerFilteringCraftable", this->is_smoker_filtering_craftable);
   w.write_byte("isSmokerGuiOpen", this->is_smoker_gui_open);
   w.end_compound();
}

void RecipeBook::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> RecipeBook::__xx_offsets {
   {"isBlastingFurnaceFilteringCraftable", {offsetof(RecipeBook, is_blasting_furnace_filtering_craftable), sizeof(RecipeBook::is_blasting_furnace_filtering_craftable), 1}},
   {"isBlastingFurnaceGuiOpen", {offsetof(RecipeBook, is_blasting_furnace_gui_open), sizeof(RecipeBook::is_blasting_furnace_gui_open), 2}},
   {"isFilteringCraftable", {offsetof(RecipeBook, is_filtering_craftable), sizeof(RecipeBook::is_filtering_craftable), 3}},
   {"isFurnaceFilteringCraftable", {offsetof(RecipeBook, is_furnace_filtering_craftable), sizeof(RecipeBook::is_furnace_filtering_craftable), 4}},
   {"isFurnaceGuiOpen", {offsetof(RecipeBook, is_furnace_gui_open), sizeof(RecipeBook::is_furnace_gui_open), 5}},
   {"isGuiOpen", {offsetof(RecipeBook, is_gui_open), sizeof(RecipeBook::is_gui_open), 6}},
   {"isSmokerFilteringCraftable", {offsetof(RecipeBook, is_smoker_filtering_craftable), sizeof(RecipeBook::is_smoker_filtering_craftable), 7}},
   {"isSmokerGuiOpen", {offsetof(RecipeBook, is_smoker_gui_open), sizeof(RecipeBook::is_smoker_gui_open), 8}},
};

RecipeBook RecipeBook::deserialize_no_header(NBT::Reader &r) {
   RecipeBook res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      case NBT::TagId::Byte: 
         res.__xx_put(name, r.read_byte());
         return;
      }
      r.skip_payload(tagid);
   });

   return res;
}

RecipeBook RecipeBook::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return RecipeBook();
   }
   return RecipeBook::deserialize_no_header(r);
}

int Version::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void Version::serialize_no_header(NBT::Writer &w) const {
   w.write_int("Id", this->id);
   w.write_string("Name", this->name);
   w.write_byte("Snapshot", this->snapshot);
   w.end_compound();
}

void Version::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> Version::__xx_offsets {
   {"Id", {offsetof(Version, id), sizeof(Version::id), 1}},
   {"Name", {offsetof(Version, name), sizeof(Version::name), 2}},
   {"Snapshot", {offsetof(Version, snapshot), sizeof(Version::snapshot), 3}},
};

Version Version::deserialize_no_header(NBT::Reader &r) {
   Version res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      case NBT::TagId::Byte: 
         res.__xx_put(name, r.read_byte());
         return;
      case NBT::TagId::Int: 
         res.__xx_put(name, r.read_int());
         return;
      case NBT::TagId::String: 
         res.__xx_put(name, r.read_str());
         return;
      }
      r.skip_payload(tagid);
   });

   return res;
}

Version Version::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return Version();
   }
   return Version::deserialize_no_header(r);
}

int BiomeSource::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void BiomeSource::serialize_no_header(NBT::Writer &w) const {
   w.write_string("preset", this->preset);
   w.write_byte("large_biomes", this->large_biomes);
   w.write_long("seed", this->seed);
   w.write_string("type", this->type);
   w.end_compound();
}

void BiomeSource::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> BiomeSource::__xx_offsets {
   {"preset", {offsetof(BiomeSource, preset), sizeof(BiomeSource::preset), 1}},
   {"large_biomes", {offsetof(BiomeSource, large_biomes), sizeof(BiomeSource::large_biomes), 2}},
   {"seed", {offsetof(BiomeSource, seed), sizeof(BiomeSource::seed), 3}},
   {"type", {offsetof(BiomeSource, type), sizeof(BiomeSource::type), 4}},
};

BiomeSource BiomeSource::deserialize_no_header(NBT::Reader &r) {
   BiomeSource res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      case NBT::TagId::Byte: 
         res.__xx_put(name, r.read_byte());
         return;
      case NBT::TagId::Long: 
         res.__xx_put(name, r.read_long());
         return;
      case NBT::TagId::String: 
         res.__xx_put(name, r.read_str());
         return;
      }
      r.skip_payload(tagid);
   });

   return res;
}

BiomeSource BiomeSource::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return BiomeSource();
   }
   return BiomeSource::deserialize_no_header(r);
}

int Generator::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void Generator::serialize_no_header(NBT::Writer &w) const {
   w.begin_compound("biome_source");
   this->biome_source.serialize_no_header(w);
   w.write_long("seed", this->seed);
   w.write_string("settings", this->settings);
   w.write_string("type", this->type);
   w.end_compound();
}

void Generator::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> Generator::__xx_offsets {
   {"biome_source", {offsetof(Generator, biome_source), sizeof(Generator::biome_source), 1}},
   {"seed", {offsetof(Generator, seed), sizeof(Generator::seed), 2}},
   {"settings", {offsetof(Generator, settings), sizeof(Generator::settings), 3}},
   {"type", {offsetof(Generator, type), sizeof(Generator::type), 4}},
};

Generator Generator::deserialize_no_header(NBT::Reader &r) {
   Generator res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      case NBT::TagId::Long: 
         res.__xx_put(name, r.read_long());
         return;
      case NBT::TagId::String: 
         res.__xx_put(name, r.read_str());
         return;
      case NBT::TagId::Compound: {
         switch(res.__xx_get_id(name)) {
            case 1:
               res.__xx_put(name, BiomeSource::deserialize_no_header(r));
               return;
         }
         break;
      }
      }
      r.skip_payload(tagid);
   });

   return res;
}

Generator Generator::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return Generator();
   }
   return Generator::deserialize_no_header(r);
}

int DimentionData::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void DimentionData::serialize_no_header(NBT::Writer &w) const {
   w.begin_compound("generator");
   this->generator.serialize_no_header(w);
   w.write_string("type", this->type);
   w.end_compound();
}

void DimentionData::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> DimentionData::__xx_offsets {
   {"generator", {offsetof(DimentionData, generator), sizeof(DimentionData::generator), 1}},
   {"type", {offsetof(DimentionData, type), sizeof(DimentionData::type), 2}},
};

DimentionData DimentionData::deserialize_no_header(NBT::Reader &r) {
   DimentionData res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      case NBT::TagId::String: 
         res.__xx_put(name, r.read_str());
         return;
      case NBT::TagId::Compound: {
         switch(res.__xx_get_id(name)) {
            case 1:
               res.__xx_put(name, Generator::deserialize_no_header(r));
               return;
         }
         break;
      }
      }
      r.skip_payload(tagid);
   });

   return res;
}

DimentionData DimentionData::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return DimentionData();
   }
   return DimentionData::deserialize_no_header(r);
}

int Dimentions::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void Dimentions::serialize_no_header(NBT::Writer &w) const {
   w.begin_compound("minecraft:overworld");
   this->overworld.serialize_no_header(w);
   w.begin_compound("minecraft:the_end");
   this->the_end.serialize_no_header(w);
   w.begin_compound("minecraft:the_nether");
   this->the_nether.serialize_no_header(w);
   w.end_compound();
}

void Dimentions::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> Dimentions::__xx_offsets {
   {"minecraft:overworld", {offsetof(Dimentions, overworld), sizeof(Dimentions::overworld), 1}},
   {"minecraft:the_end", {offsetof(Dimentions, the_end), sizeof(Dimentions::the_end), 2}},
   {"minecraft:the_nether", {offsetof(Dimentions, the_nether), sizeof(Dimentions::the_nether), 3}},
};

Dimentions Dimentions::deserialize_no_header(NBT::Reader &r) {
   Dimentions res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      case NBT::TagId::Compound: {
         switch(res.__xx_get_id(name)) {
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
      }
      r.skip_payload(tagid);
   });

   return res;
}

Dimentions Dimentions::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return Dimentions();
   }
   return Dimentions::deserialize_no_header(r);
}

int WorldGen::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void WorldGen::serialize_no_header(NBT::Writer &w) const {
   w.write_byte("bonus_chest", this->bonus_chest);
   w.begin_compound("dimensions");
   this->dimensions.serialize_no_header(w);
   w.write_byte("generate_features", this->generate_features);
   w.write_long("seed", this->seed);
   w.end_compound();
}

void WorldGen::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> WorldGen::__xx_offsets {
   {"bonus_chest", {offsetof(WorldGen, bonus_chest), sizeof(WorldGen::bonus_chest), 1}},
   {"dimensions", {offsetof(WorldGen, dimensions), sizeof(WorldGen::dimensions), 2}},
   {"generate_features", {offsetof(WorldGen, generate_features), sizeof(WorldGen::generate_features), 3}},
   {"seed", {offsetof(WorldGen, seed), sizeof(WorldGen::seed), 4}},
};

WorldGen WorldGen::deserialize_no_header(NBT::Reader &r) {
   WorldGen res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      case NBT::TagId::Byte: 
         res.__xx_put(name, r.read_byte());
         return;
      case NBT::TagId::Long: 
         res.__xx_put(name, r.read_long());
         return;
      case NBT::TagId::Compound: {
         switch(res.__xx_get_id(name)) {
            case 2:
               res.__xx_put(name, Dimentions::deserialize_no_header(r));
               return;
         }
         break;
      }
      }
      r.skip_payload(tagid);
   });

   return res;
}

WorldGen WorldGen::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return WorldGen();
   }
   return WorldGen::deserialize_no_header(r);
}

int DataPacks::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void DataPacks::serialize_no_header(NBT::Writer &w) const {
   w.write_longs("Disabled", disabled);
   w.end_compound();
}

void DataPacks::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> DataPacks::__xx_offsets {
   {"Disabled", {offsetof(DataPacks, disabled), sizeof(DataPacks::disabled), 1}},
};

DataPacks DataPacks::deserialize_no_header(NBT::Reader &r) {
   DataPacks res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      case NBT::TagId::LongArray: 
         res.__xx_put(name, r.read_long_vec());
         return;
      }
      r.skip_payload(tagid);
   });

   return res;
}

DataPacks DataPacks::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return DataPacks();
   }
   return DataPacks::deserialize_no_header(r);
}

int DragonFight::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void DragonFight::serialize_no_header(NBT::Writer &w) const {
   w.write_byte("DragonKilled", this->dragon_killed);
   w.write_byte("PreviouslyKilled", this->previously_killed);
   w.end_compound();
}

void DragonFight::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> DragonFight::__xx_offsets {
   {"DragonKilled", {offsetof(DragonFight, dragon_killed), sizeof(DragonFight::dragon_killed), 1}},
   {"PreviouslyKilled", {offsetof(DragonFight, previously_killed), sizeof(DragonFight::previously_killed), 3}},
};

DragonFight DragonFight::deserialize_no_header(NBT::Reader &r) {
   DragonFight res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      case NBT::TagId::Byte: 
         res.__xx_put(name, r.read_byte());
         return;
      }
      r.skip_payload(tagid);
   });

   return res;
}

DragonFight DragonFight::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return DragonFight();
   }
   return DragonFight::deserialize_no_header(r);
}

int CustomBossEvents::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void CustomBossEvents::serialize_no_header(NBT::Writer &w) const {
   w.end_compound();
}

void CustomBossEvents::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> CustomBossEvents::__xx_offsets {
};

CustomBossEvents CustomBossEvents::deserialize_no_header(NBT::Reader &r) {
   CustomBossEvents res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      }
      r.skip_payload(tagid);
   });

   return res;
}

CustomBossEvents CustomBossEvents::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return CustomBossEvents();
   }
   return CustomBossEvents::deserialize_no_header(r);
}

int Player::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void Player::serialize_no_header(NBT::Writer &w) const {
   w.write_float("AbsorptionAmount", this->absorption_amount);
   w.write_short("Air", this->air);
   w.begin_compound("Brain");
   this->brain.serialize_no_header(w);
   w.write_int("DataVersion", this->data_version);
   w.write_short("DeathTime", this->death_time);
   w.write_string("Dimension", this->dimension);
   w.write_float("FallDistance", this->fall_distance);
   w.write_byte("FallFlying", this->fall_flying);
   w.write_short("Fire", this->fire);
   w.write_float("Health", this->health);
   w.write_int("HurtByTimestamp", this->hurt_by_timestamp);
   w.write_short("HurtTime", this->hurt_time);
   w.write_byte("Invulnerable", this->invulnerable);
   w.write_byte("OnGround", this->on_ground);
   w.write_int("PortalCooldown", this->portal_cooldown);
   w.write_int("Score", this->score);
   w.write_int("SelectedItemSlot", this->selected_item_slot);
   w.write_short("SleepTimer", this->sleep_timer);
   w.write_ints("UUID", uuid);
   w.write_int("XpLevel", this->xp_level);
   w.write_float("XpP", this->xp_p);
   w.write_int("XpSeed", this->xp_seed);
   w.write_int("XpTotal", this->xp_total);
   w.begin_compound("abilities");
   this->abilities.serialize_no_header(w);
   w.write_float("foodExhaustionLevel", this->food_exhaustion_level);
   w.write_int("foodLevel", this->food_level);
   w.write_float("foodSaturationLevel", this->food_saturation_level);
   w.write_int("foodTickTimer", this->food_tick_timer);
   w.write_int("playerGameType", this->player_game_type);
   w.write_int("previousPlayerGameType", this->previous_player_game_type);
   w.begin_compound("recipeBook");
   this->recipe_book.serialize_no_header(w);
   w.write_byte("seenCredits", this->seen_credits);
   w.end_compound();
}

void Player::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> Player::__xx_offsets {
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

Player Player::deserialize_no_header(NBT::Reader &r) {
   Player res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      case NBT::TagId::Byte: 
         res.__xx_put(name, r.read_byte());
         return;
      case NBT::TagId::Short: 
         res.__xx_put(name, r.read_short());
         return;
      case NBT::TagId::Int: 
         res.__xx_put(name, r.read_int());
         return;
      case NBT::TagId::String: 
         res.__xx_put(name, r.read_str());
         return;
      case NBT::TagId::Float: 
         res.__xx_put(name, r.read_float32());
         return;
      case NBT::TagId::IntArray: 
         res.__xx_put(name, r.read_int_vec());
         return;
      case NBT::TagId::Compound: {
         switch(res.__xx_get_id(name)) {
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
      }
      r.skip_payload(tagid);
   });

   return res;
}

Player Player::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return Player();
   }
   return Player::deserialize_no_header(r);
}

int GameRules::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void GameRules::serialize_no_header(NBT::Writer &w) const {
   w.write_string("announceAdvancements", this->announce_advancements);
   w.write_string("commandBlockOutput", this->command_block_output);
   w.write_string("disableElytraMovementCheck", this->disable_elytra_movement_check);
   w.write_string("disableRaids", this->disable_raids);
   w.write_string("doDaylightCycle", this->do_daylight_cycle);
   w.write_string("doEntityDrops", this->do_entity_drops);
   w.write_string("doFireTick", this->do_fire_tick);
   w.write_string("doImmediateRespawn", this->do_immediate_respawn);
   w.write_string("doInsomnia", this->do_insomnia);
   w.write_string("doLimitedCrafting", this->do_limited_crafting);
   w.write_string("doMobLoot", this->do_mob_loot);
   w.write_string("doMobSpawning", this->do_mob_spawning);
   w.write_string("doPatrolSpawning", this->do_patrol_spawning);
   w.write_string("doTileDrops", this->do_tile_drops);
   w.write_string("doTraderSpawning", this->do_trader_spawning);
   w.write_string("doWeatherCycle", this->do_weather_cycle);
   w.write_string("drowningDamage", this->drowning_damage);
   w.write_string("fallDamage", this->fall_damage);
   w.write_string("fireDamage", this->fire_damage);
   w.write_string("forgiveDeadPlayers", this->forgive_dead_players);
   w.write_string("keepInventory", this->keep_inventory);
   w.write_string("logAdminCommands", this->log_admin_commands);
   w.write_string("maxCommandChainLength", this->max_command_chain_length);
   w.write_string("maxEntityCramming", this->max_entity_cramming);
   w.write_string("mobGriefing", this->mob_griefing);
   w.write_string("naturalRegeneration", this->natural_regeneration);
   w.write_string("randomTickSpeed", this->random_tick_speed);
   w.write_string("reducedDebugInfo", this->reduced_debug_info);
   w.write_string("sendCommandFeedback", this->send_command_feedback);
   w.write_string("showDeathMessages", this->show_death_messages);
   w.write_string("spawnRadius", this->spawn_radius);
   w.write_string("spectatorsGenerateChunks", this->spectators_generate_chunks);
   w.write_string("universalAnger", this->universal_anger);
   w.end_compound();
}

void GameRules::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> GameRules::__xx_offsets {
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

GameRules GameRules::deserialize_no_header(NBT::Reader &r) {
   GameRules res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      case NBT::TagId::String: 
         res.__xx_put(name, r.read_str());
         return;
      }
      r.skip_payload(tagid);
   });

   return res;
}

GameRules GameRules::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return GameRules();
   }
   return GameRules::deserialize_no_header(r);
}

int LevelData::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void LevelData::serialize_no_header(NBT::Writer &w) const {
   w.write_double("BorderCenterX", border_center_x);
   w.write_double("BorderCenterZ", border_center_z);
   w.write_double("BorderDamagePerBlock", border_damage_per_block);
   w.write_double("BorderSafeZone", border_safe_zone);
   w.write_double("BorderSize", border_size);
   w.write_double("BorderSizeLerpTarget", border_size_lerp_target);
   w.write_long("BorderSizeLerpTime", this->border_size_lerp_time);
   w.write_double("BorderWarningBlocks", border_warning_blocks);
   w.write_double("BorderWarningTime", border_warning_time);
   w.begin_compound("CustomBossEvents");
   this->custom_boss_events.serialize_no_header(w);
   w.begin_compound("DataPacks");
   this->data_packs.serialize_no_header(w);
   w.write_int("DataVersion", this->data_version);
   w.write_long("DayTime", this->day_time);
   w.write_byte("Difficulty", this->difficulty);
   w.write_byte("DifficultyLocked", this->difficulty_locked);
   w.begin_compound("DragonFight");
   this->dragon_fight.serialize_no_header(w);
   w.begin_compound("GameRules");
   this->game_rules.serialize_no_header(w);
   w.write_int("GameType", this->game_type);
   w.write_long("LastPlayed", this->last_played);
   w.write_string("LevelName", this->level_name);
   w.begin_compound("Player");
   this->player.serialize_no_header(w);
   w.write_int("SpawnX", this->spawn_x);
   w.write_int("SpawnY", this->spawn_y);
   w.write_int("SpawnZ", this->spawn_z);
   w.write_long("Time", this->time);
   w.begin_compound("Version");
   this->version.serialize_no_header(w);
   w.write_int("WanderingTraderSpawnChance", this->wandering_trader_spawn_chance);
   w.write_int("WanderingTraderSpawnDelay", this->wandering_trader_spawn_delay);
   w.write_byte("WasModded", this->was_modded);
   w.begin_compound("WorldGenSettings");
   this->world_gen_settings.serialize_no_header(w);
   w.write_byte("allowCommands", this->allow_commands);
   w.write_int("clearWeatherTime", this->clear_weather_time);
   w.write_byte("hardcore", this->hardcore);
   w.write_byte("initialized", this->initialized);
   w.write_int("rainTime", this->rain_time);
   w.write_byte("raining", this->raining);
   w.write_int("thunderTime", this->thunder_time);
   w.write_byte("thundering", this->thundering);
   w.write_int("version2", this->version2);
   w.end_compound();
}

void LevelData::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> LevelData::__xx_offsets {
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

LevelData LevelData::deserialize_no_header(NBT::Reader &r) {
   LevelData res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      case NBT::TagId::Byte: 
         res.__xx_put(name, r.read_byte());
         return;
      case NBT::TagId::Int: 
         res.__xx_put(name, r.read_int());
         return;
      case NBT::TagId::Long: 
         res.__xx_put(name, r.read_long());
         return;
      case NBT::TagId::String: 
         res.__xx_put(name, r.read_str());
         return;
      case NBT::TagId::Double: 
         res.__xx_put(name, r.read_float64());
         return;
      case NBT::TagId::Compound: {
         switch(res.__xx_get_id(name)) {
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
      }
      r.skip_payload(tagid);
   });

   return res;
}

LevelData LevelData::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return LevelData();
   }
   return LevelData::deserialize_no_header(r);
}

int Level::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) return -1;
   return it->second.id;
}

void Level::serialize_no_header(NBT::Writer &w) const {
   w.begin_compound("Data");
   this->data.serialize_no_header(w);
   w.end_compound();
}

void Level::serialize(std::ostream &out, const std::string_view name) const {
   NBT::Writer w(out);
   w.begin_compound(name);
   this->serialize_no_header(w);
}

std::unordered_map<std::string, __nbt_offset> Level::__xx_offsets {
   {"Data", {offsetof(Level, data), sizeof(Level::data), 1}},
};

Level Level::deserialize_no_header(NBT::Reader &r) {
   Level res;
   r.read_compound([&res] (NBT::Reader &r, NBT::TagId tagid, const std::string &name) {
      switch (tagid) {
      case NBT::TagId::Compound: {
         switch(res.__xx_get_id(name)) {
            case 1:
               res.__xx_put(name, LevelData::deserialize_no_header(r));
               return;
         }
         break;
      }
      }
      r.skip_payload(tagid);
   });

   return res;
}

Level Level::deserialize(std::istream &in) {
   NBT::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != NBT::TagId::Compound) {
      return Level();
   }
   return Level::deserialize_no_header(r);
}

}// namespace Game::NbtLevel
