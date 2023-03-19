#include <minecpp/nbt/level/v1/Level.nbt.h>

namespace minecpp::nbt::level::v1 {

void Memories::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Int, "no_empty");
   w.write_int_content(no_empty);
   w.end_compound();
}

void Memories::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   serialize_no_header(w);
}

Memories Memories::deserialize_no_header(minecpp::nbt::Reader &r) {
   Memories res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Int:
         res.set_property(in_field_name, r.read_int());
         return;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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
   serialize_no_header(w);
}

Brain Brain::deserialize_no_header(minecpp::nbt::Reader &r) {
   Brain res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Compound:
         if (in_field_name == "memories") {
            res.set_property(in_field_name, Memories::deserialize_no_header(r));
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
   serialize_no_header(w);
}

Abilities Abilities::deserialize_no_header(minecpp::nbt::Reader &r) {
   Abilities res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Byte:
         res.set_property(in_field_name, r.read_byte());
         return;
      case minecpp::nbt::TagId::Float:
         res.set_property(in_field_name, r.read_float32());
         return;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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
   serialize_no_header(w);
}

RecipeBook RecipeBook::deserialize_no_header(minecpp::nbt::Reader &r) {
   RecipeBook res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Byte:
         res.set_property(in_field_name, r.read_byte());
         return;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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
   serialize_no_header(w);
}

Version Version::deserialize_no_header(minecpp::nbt::Reader &r) {
   Version res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Byte:
         res.set_property(in_field_name, r.read_byte());
         return;
      case minecpp::nbt::TagId::Int:
         res.set_property(in_field_name, r.read_int());
         return;
      case minecpp::nbt::TagId::String:
         res.set_property(in_field_name, r.read_str());
         return;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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
   serialize_no_header(w);
}

BiomeSource BiomeSource::deserialize_no_header(minecpp::nbt::Reader &r) {
   BiomeSource res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Byte:
         res.set_property(in_field_name, r.read_byte());
         return;
      case minecpp::nbt::TagId::Long:
         res.set_property(in_field_name, r.read_long());
         return;
      case minecpp::nbt::TagId::String:
         res.set_property(in_field_name, r.read_str());
         return;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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
   serialize_no_header(w);
}

Generator Generator::deserialize_no_header(minecpp::nbt::Reader &r) {
   Generator res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Long:
         res.set_property(in_field_name, r.read_long());
         return;
      case minecpp::nbt::TagId::String:
         res.set_property(in_field_name, r.read_str());
         return;
      case minecpp::nbt::TagId::Compound:
         if (in_field_name == "biome_source") {
            res.set_property(in_field_name, BiomeSource::deserialize_no_header(r));
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
   serialize_no_header(w);
}

DimentionData DimentionData::deserialize_no_header(minecpp::nbt::Reader &r) {
   DimentionData res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String:
         res.set_property(in_field_name, r.read_str());
         return;
      case minecpp::nbt::TagId::Compound:
         if (in_field_name == "generator") {
            res.set_property(in_field_name, Generator::deserialize_no_header(r));
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
   serialize_no_header(w);
}

Dimentions Dimentions::deserialize_no_header(minecpp::nbt::Reader &r) {
   Dimentions res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Compound:
         if (in_field_name == "minecraft:overworld") {
            res.set_property(in_field_name, DimentionData::deserialize_no_header(r));
            return;
         }
         if (in_field_name == "minecraft:the_end") {
            res.set_property(in_field_name, DimentionData::deserialize_no_header(r));
            return;
         }
         if (in_field_name == "minecraft:the_nether") {
            res.set_property(in_field_name, DimentionData::deserialize_no_header(r));
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
   serialize_no_header(w);
}

WorldGen WorldGen::deserialize_no_header(minecpp::nbt::Reader &r) {
   WorldGen res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Byte:
         res.set_property(in_field_name, r.read_byte());
         return;
      case minecpp::nbt::TagId::Long:
         res.set_property(in_field_name, r.read_long());
         return;
      case minecpp::nbt::TagId::Compound:
         if (in_field_name == "dimensions") {
            res.set_property(in_field_name, Dimentions::deserialize_no_header(r));
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
   serialize_no_header(w);
}

DataPacks DataPacks::deserialize_no_header(minecpp::nbt::Reader &r) {
   DataPacks res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
      switch (tagid) {
      case minecpp::nbt::TagId::LongArray:
         res.set_property(in_field_name, r.read_long_vec());
         return;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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
   serialize_no_header(w);
}

DragonFight DragonFight::deserialize_no_header(minecpp::nbt::Reader &r) {
   DragonFight res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Byte:
         res.set_property(in_field_name, r.read_byte());
         return;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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
   serialize_no_header(w);
}

CustomBossEvents CustomBossEvents::deserialize_no_header(minecpp::nbt::Reader &r) {
   CustomBossEvents res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Int:
         res.set_property(in_field_name, r.read_int());
         return;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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
   serialize_no_header(w);
}

Player Player::deserialize_no_header(minecpp::nbt::Reader &r) {
   Player res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Byte:
         res.set_property(in_field_name, r.read_byte());
         return;
      case minecpp::nbt::TagId::Short:
         res.set_property(in_field_name, r.read_short());
         return;
      case minecpp::nbt::TagId::Int:
         res.set_property(in_field_name, r.read_int());
         return;
      case minecpp::nbt::TagId::String:
         res.set_property(in_field_name, r.read_str());
         return;
      case minecpp::nbt::TagId::Float:
         res.set_property(in_field_name, r.read_float32());
         return;
      case minecpp::nbt::TagId::IntArray:
         res.set_property(in_field_name, r.read_int_vec());
         return;
      case minecpp::nbt::TagId::Compound:
         if (in_field_name == "Brain") {
            res.set_property(in_field_name, Brain::deserialize_no_header(r));
            return;
         }
         if (in_field_name == "abilities") {
            res.set_property(in_field_name, Abilities::deserialize_no_header(r));
            return;
         }
         if (in_field_name == "recipeBook") {
            res.set_property(in_field_name, RecipeBook::deserialize_no_header(r));
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
   serialize_no_header(w);
}

GameRules GameRules::deserialize_no_header(minecpp::nbt::Reader &r) {
   GameRules res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String:
         res.set_property(in_field_name, r.read_str());
         return;
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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
   serialize_no_header(w);
}

LevelData LevelData::deserialize_no_header(minecpp::nbt::Reader &r) {
   LevelData res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Byte:
         res.set_property(in_field_name, r.read_byte());
         return;
      case minecpp::nbt::TagId::Int:
         res.set_property(in_field_name, r.read_int());
         return;
      case minecpp::nbt::TagId::Long:
         res.set_property(in_field_name, r.read_long());
         return;
      case minecpp::nbt::TagId::String:
         res.set_property(in_field_name, r.read_str());
         return;
      case minecpp::nbt::TagId::Double:
         res.set_property(in_field_name, r.read_float64());
         return;
      case minecpp::nbt::TagId::Compound:
         if (in_field_name == "CustomBossEvents") {
            res.set_property(in_field_name, CustomBossEvents::deserialize_no_header(r));
            return;
         }
         if (in_field_name == "DataPacks") {
            res.set_property(in_field_name, DataPacks::deserialize_no_header(r));
            return;
         }
         if (in_field_name == "DragonFight") {
            res.set_property(in_field_name, DragonFight::deserialize_no_header(r));
            return;
         }
         if (in_field_name == "GameRules") {
            res.set_property(in_field_name, GameRules::deserialize_no_header(r));
            return;
         }
         if (in_field_name == "Player") {
            res.set_property(in_field_name, Player::deserialize_no_header(r));
            return;
         }
         if (in_field_name == "Version") {
            res.set_property(in_field_name, Version::deserialize_no_header(r));
            return;
         }
         if (in_field_name == "WorldGenSettings") {
            res.set_property(in_field_name, WorldGen::deserialize_no_header(r));
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
   serialize_no_header(w);
}

Level Level::deserialize_no_header(minecpp::nbt::Reader &r) {
   Level res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &in_field_name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Compound:
         if (in_field_name == "Data") {
            res.set_property(in_field_name, LevelData::deserialize_no_header(r));
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

Level Level::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return Level::deserialize_no_header(r);
}

}