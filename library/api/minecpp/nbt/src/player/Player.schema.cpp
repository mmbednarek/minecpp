#include "player/Player.schema.h"
#include <minecpp/nbt/Exception.h>

namespace minecpp::nbt::player {

void Attribute::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Double, "Base");
   w.write_double_content(base);
   w.write_header(minecpp::nbt::TagId::String, "Name");
   w.write_string_content(name);
   w.end_compound();
}

void Attribute::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

Attribute Attribute::deserialize_no_header(minecpp::nbt::Reader &r) {
   Attribute result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "Base") {
         ::minecpp::nbt::verify_tag("Attribute", in_field_name, minecpp::nbt::TagId::Double, tagid);
         result.base = r.read_float64();
         continue;
      }
      if (in_field_name == "Name") {
         ::minecpp::nbt::verify_tag("Attribute", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.name = r.read_str();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

Attribute Attribute::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return Attribute::deserialize_no_header(r);
}

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

void InventoryElement::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Byte, "Count");
   w.write_byte_content(static_cast<std::uint8_t>(count));
   w.write_header(minecpp::nbt::TagId::Byte, "Slot");
   w.write_byte_content(static_cast<std::uint8_t>(slot));
   w.write_header(minecpp::nbt::TagId::String, "id");
   w.write_string_content(id);
   w.end_compound();
}

void InventoryElement::serialize(std::ostream &out_stream, std::string_view in_compound_name) const {
   minecpp::nbt::Writer w(out_stream);
   w.begin_compound(in_compound_name);
   this->serialize_no_header(w);
}

InventoryElement InventoryElement::deserialize_no_header(minecpp::nbt::Reader &r) {
   InventoryElement result;
   for (const auto &[tagid, in_field_name] : r.iterate_compound()) {
      if (in_field_name == "Count") {
         ::minecpp::nbt::verify_tag("InventoryElement", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.count = r.read_byte();
         continue;
      }
      if (in_field_name == "Slot") {
         ::minecpp::nbt::verify_tag("InventoryElement", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.slot = r.read_byte();
         continue;
      }
      if (in_field_name == "id") {
         ::minecpp::nbt::verify_tag("InventoryElement", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.id = r.read_str();
         continue;
      }
      r.skip_payload(tagid);
   }
   return result;
}

InventoryElement InventoryElement::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return InventoryElement::deserialize_no_header(r);
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
   w.write_header(minecpp::nbt::TagId::List, "recipes");
   w.begin_list_no_header(minecpp::nbt::TagId::String, recipes.size());
   for (const auto &list_item_0 : recipes) {
      w.write_string_content(list_item_0);
   }
   w.write_header(minecpp::nbt::TagId::List, "toBeDisplayed");
   w.begin_list_no_header(minecpp::nbt::TagId::String, to_be_displayed.size());
   for (const auto &list_item_0 : to_be_displayed) {
      w.write_string_content(list_item_0);
   }
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
      if (in_field_name == "recipes") {
         ::minecpp::nbt::verify_tag("RecipeBook", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<std::string> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return r.read_str();
         });
         result.recipes = std::move(list);
         continue;
      }
      if (in_field_name == "toBeDisplayed") {
         ::minecpp::nbt::verify_tag("RecipeBook", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<std::string> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return r.read_str();
         });
         result.to_be_displayed = std::move(list);
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

void Player::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Float, "AbsorptionAmount");
   w.write_float_content(absorption_amount);
   w.write_header(minecpp::nbt::TagId::Short, "Air");
   w.write_short_content(air);
   w.write_header(minecpp::nbt::TagId::List, "Attributes");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, attributes.size());
   for (const auto &list_item_0 : attributes) {
      list_item_0.serialize_no_header(w);
   }
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
   w.write_header(minecpp::nbt::TagId::List, "Inventory");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, inventory.size());
   for (const auto &list_item_0 : inventory) {
      list_item_0.serialize_no_header(w);
   }
   w.write_header(minecpp::nbt::TagId::Byte, "Invulnerable");
   w.write_byte_content(static_cast<std::uint8_t>(invulnerable));
   w.write_header(minecpp::nbt::TagId::List, "Motion");
   w.begin_list_no_header(minecpp::nbt::TagId::Double, motion.size());
   for (const auto &list_item_0 : motion) {
      w.write_double_content(list_item_0);
   }
   w.write_header(minecpp::nbt::TagId::Byte, "OnGround");
   w.write_byte_content(static_cast<std::uint8_t>(on_ground));
   w.write_header(minecpp::nbt::TagId::Int, "PortalCooldown");
   w.write_int_content(portal_cooldown);
   w.write_header(minecpp::nbt::TagId::List, "Pos");
   w.begin_list_no_header(minecpp::nbt::TagId::Double, pos.size());
   for (const auto &list_item_0 : pos) {
      w.write_double_content(list_item_0);
   }
   w.write_header(minecpp::nbt::TagId::List, "Rotation");
   w.begin_list_no_header(minecpp::nbt::TagId::Float, rotation.size());
   for (const auto &list_item_0 : rotation) {
      w.write_float_content(list_item_0);
   }
   w.write_header(minecpp::nbt::TagId::Int, "Score");
   w.write_int_content(score);
   w.write_header(minecpp::nbt::TagId::Int, "SelectedItemSlot");
   w.write_int_content(selected_item_slot);
   w.write_header(minecpp::nbt::TagId::Short, "SleepTimer");
   w.write_short_content(sleep_timer);
   w.write_header(minecpp::nbt::TagId::Float, "SpawnAngle");
   w.write_float_content(spawn_angle);
   w.write_header(minecpp::nbt::TagId::String, "SpawnDimension");
   w.write_string_content(spawn_dimension);
   w.write_header(minecpp::nbt::TagId::Byte, "SpawnForced");
   w.write_byte_content(static_cast<std::uint8_t>(spawn_forced));
   w.write_header(minecpp::nbt::TagId::Int, "SpawnX");
   w.write_int_content(spawn_x);
   w.write_header(minecpp::nbt::TagId::Int, "SpawnY");
   w.write_int_content(spawn_y);
   w.write_header(minecpp::nbt::TagId::Int, "SpawnZ");
   w.write_int_content(spawn_z);
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
      if (in_field_name == "Attributes") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<Attribute> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return Attribute::deserialize_no_header(r);
         });
         result.attributes = std::move(list);
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
      if (in_field_name == "Inventory") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<InventoryElement> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return InventoryElement::deserialize_no_header(r);
         });
         result.inventory = std::move(list);
         continue;
      }
      if (in_field_name == "Invulnerable") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.invulnerable = r.read_byte();
         continue;
      }
      if (in_field_name == "Motion") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<double> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return r.read_float64();
         });
         result.motion = std::move(list);
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
      if (in_field_name == "Pos") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<double> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return r.read_float64();
         });
         result.pos = std::move(list);
         continue;
      }
      if (in_field_name == "Rotation") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::List, tagid);
         auto list_info = r.peek_list();
         std::vector<float> list(list_info.size);
         std::generate(list.begin(), list.end(), [&r]() {
            return r.read_float32();
         });
         result.rotation = std::move(list);
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
      if (in_field_name == "SpawnAngle") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Float, tagid);
         result.spawn_angle = r.read_float32();
         continue;
      }
      if (in_field_name == "SpawnDimension") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::String, tagid);
         result.spawn_dimension = r.read_str();
         continue;
      }
      if (in_field_name == "SpawnForced") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Byte, tagid);
         result.spawn_forced = r.read_byte();
         continue;
      }
      if (in_field_name == "SpawnX") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.spawn_x = r.read_int();
         continue;
      }
      if (in_field_name == "SpawnY") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.spawn_y = r.read_int();
         continue;
      }
      if (in_field_name == "SpawnZ") {
         ::minecpp::nbt::verify_tag("Player", in_field_name, minecpp::nbt::TagId::Int, tagid);
         result.spawn_z = r.read_int();
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

}