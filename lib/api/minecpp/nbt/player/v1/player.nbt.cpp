#include <minecpp/nbt/player/v1/player.nbt.h>

namespace minecpp::nbt::player::v1 {

void Attribute::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Double, "Base");
   w.write_double_content(base);
   w.write_header(minecpp::nbt::TagId::String, "Name");
   w.write_string_content(name);
   w.end_compound();
}

void Attribute::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Attribute Attribute::deserialize_no_header(minecpp::nbt::Reader &r) {
   Attribute res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      case minecpp::nbt::TagId::Double:
         res.__xx_put(name, r.read_float64());
         return;
      }
      r.skip_payload(tagid);
   });
   return res;
}

Attribute Attribute::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return Attribute();
   }
   return Attribute::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> Attribute::__xx_offsets {
   {"Base", {offsetof(Attribute, base), sizeof(Attribute::base), 1}},
   {"Name", {offsetof(Attribute, name), sizeof(Attribute::name), 2}},
};

int Attribute::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

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

void InventoryElement::serialize_no_header(minecpp::nbt::Writer &w) const {
   w.write_header(minecpp::nbt::TagId::Byte, "Count");
   w.write_byte_content(count);
   w.write_header(minecpp::nbt::TagId::Byte, "Slot");
   w.write_byte_content(slot);
   w.write_header(minecpp::nbt::TagId::String, "id");
   w.write_string_content(id);
   w.end_compound();
}

void InventoryElement::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

InventoryElement InventoryElement::deserialize_no_header(minecpp::nbt::Reader &r) {
   InventoryElement res;
   r.read_compound([&res](minecpp::nbt::Reader &r, minecpp::nbt::TagId tagid, const std::string &name) {
      switch (tagid) {
      case minecpp::nbt::TagId::Byte:
         res.__xx_put(name, r.read_byte());
         return;
      case minecpp::nbt::TagId::String:
         res.__xx_put(name, r.read_str());
         return;
      }
      r.skip_payload(tagid);
   });
   return res;
}

InventoryElement InventoryElement::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return InventoryElement();
   }
   return InventoryElement::deserialize_no_header(r);
}

std::unordered_map<std::string, __nbt_idl_offset> InventoryElement::__xx_offsets {
   {"Count", {offsetof(InventoryElement, count), sizeof(InventoryElement::count), 1}},
   {"Slot", {offsetof(InventoryElement, slot), sizeof(InventoryElement::slot), 2}},
   {"id", {offsetof(InventoryElement, id), sizeof(InventoryElement::id), 3}},
};

int InventoryElement::__xx_get_id(const std::string &name) const {
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
   w.write_header(minecpp::nbt::TagId::List, "recipes");
   w.begin_list_no_header(minecpp::nbt::TagId::String, recipes.size());
   std::for_each(recipes.begin(), recipes.end(), [&w](const auto &value) {
      w.write_string_content(value);
   });
   w.write_header(minecpp::nbt::TagId::List, "toBeDisplayed");
   w.begin_list_no_header(minecpp::nbt::TagId::String, to_be_displayed.size());
   std::for_each(to_be_displayed.begin(), to_be_displayed.end(), [&w](const auto &value) {
      w.write_string_content(value);
   });
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
            }
            for (mb::size i = 0; i < list_info0.size; ++i) {
               r.skip_payload(list_info0.tagid);
            }
         }
         return;
      }
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
   {"recipes", {offsetof(RecipeBook, recipes), sizeof(RecipeBook::recipes), 9}},
   {"toBeDisplayed", {offsetof(RecipeBook, to_be_displayed), sizeof(RecipeBook::to_be_displayed), 10}},
};

int RecipeBook::__xx_get_id(const std::string &name) const {
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
   w.write_header(minecpp::nbt::TagId::List, "Attributes");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, attributes.size());
   std::for_each(attributes.begin(), attributes.end(), [&w](const auto &value) {
      value.serialize_no_header(w);
   });
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
   w.write_header(minecpp::nbt::TagId::List, "Inventory");
   w.begin_list_no_header(minecpp::nbt::TagId::Compound, inventory.size());
   std::for_each(inventory.begin(), inventory.end(), [&w](const auto &value) {
      value.serialize_no_header(w);
   });
   w.write_header(minecpp::nbt::TagId::Byte, "Invulnerable");
   w.write_byte_content(invulnerable);
   w.write_header(minecpp::nbt::TagId::List, "Motion");
   w.begin_list_no_header(minecpp::nbt::TagId::Double, motion.size());
   std::for_each(motion.begin(), motion.end(), [&w](const auto &value) {
      w.write_double_content(value);
   });
   w.write_header(minecpp::nbt::TagId::Byte, "OnGround");
   w.write_byte_content(on_ground);
   w.write_header(minecpp::nbt::TagId::Int, "PortalCooldown");
   w.write_int_content(portal_cooldown);
   w.write_header(minecpp::nbt::TagId::List, "Pos");
   w.begin_list_no_header(minecpp::nbt::TagId::Double, pos.size());
   std::for_each(pos.begin(), pos.end(), [&w](const auto &value) {
      w.write_double_content(value);
   });
   w.write_header(minecpp::nbt::TagId::List, "Rotation");
   w.begin_list_no_header(minecpp::nbt::TagId::Float, rotation.size());
   std::for_each(rotation.begin(), rotation.end(), [&w](const auto &value) {
      w.write_float_content(value);
   });
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
   w.write_byte_content(spawn_forced);
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
         case 36:
            res.__xx_put(name, Abilities::deserialize_no_header(r));
            return;
         case 42:
            res.__xx_put(name, RecipeBook::deserialize_no_header(r));
            return;
         }
         break;
      case minecpp::nbt::TagId::List: {
         auto list_info0 = r.peek_list();
         if (list_info0.size > 0) {
            switch (list_info0.tagid) {
            case minecpp::nbt::TagId::Float: {
               std::vector<float> ls(list_info0.size);
               std::generate(ls.begin(), ls.end(), [&r]() {
                  return r.read_float32();
               });
               res.__xx_put(name, ls);
               return;
            }
            case minecpp::nbt::TagId::Double: {
               std::vector<double> ls(list_info0.size);
               std::generate(ls.begin(), ls.end(), [&r]() {
                  return r.read_float64();
               });
               res.__xx_put(name, ls);
               return;
            }
            case minecpp::nbt::TagId::Compound: {
               switch (res.__xx_get_id(name)) {
               case 3: {
                  std::vector<Attribute> ls(list_info0.size);
                  std::generate(ls.begin(), ls.end(), [&r]() {
                     return Attribute::deserialize_no_header(r);
                  });
                  res.__xx_put(name, ls);
                  return;
               }
               case 15: {
                  std::vector<InventoryElement> ls(list_info0.size);
                  std::generate(ls.begin(), ls.end(), [&r]() {
                     return InventoryElement::deserialize_no_header(r);
                  });
                  res.__xx_put(name, ls);
                  return;
               }
               }
               break;
            }
            }
            for (mb::size i = 0; i < list_info0.size; ++i) {
               r.skip_payload(list_info0.tagid);
            }
         }
         return;
      }
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
   {"Attributes", {offsetof(Player, attributes), sizeof(Player::attributes), 3}},
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
   {"Inventory", {offsetof(Player, inventory), sizeof(Player::inventory), 15}},
   {"Invulnerable", {offsetof(Player, invulnerable), sizeof(Player::invulnerable), 16}},
   {"Motion", {offsetof(Player, motion), sizeof(Player::motion), 17}},
   {"OnGround", {offsetof(Player, on_ground), sizeof(Player::on_ground), 18}},
   {"PortalCooldown", {offsetof(Player, portal_cooldown), sizeof(Player::portal_cooldown), 19}},
   {"Pos", {offsetof(Player, pos), sizeof(Player::pos), 20}},
   {"Rotation", {offsetof(Player, rotation), sizeof(Player::rotation), 21}},
   {"Score", {offsetof(Player, score), sizeof(Player::score), 22}},
   {"SelectedItemSlot", {offsetof(Player, selected_item_slot), sizeof(Player::selected_item_slot), 23}},
   {"SleepTimer", {offsetof(Player, sleep_timer), sizeof(Player::sleep_timer), 24}},
   {"SpawnAngle", {offsetof(Player, spawn_angle), sizeof(Player::spawn_angle), 25}},
   {"SpawnDimension", {offsetof(Player, spawn_dimension), sizeof(Player::spawn_dimension), 26}},
   {"SpawnForced", {offsetof(Player, spawn_forced), sizeof(Player::spawn_forced), 27}},
   {"SpawnX", {offsetof(Player, spawn_x), sizeof(Player::spawn_x), 28}},
   {"SpawnY", {offsetof(Player, spawn_y), sizeof(Player::spawn_y), 29}},
   {"SpawnZ", {offsetof(Player, spawn_z), sizeof(Player::spawn_z), 30}},
   {"UUID", {offsetof(Player, uuid), sizeof(Player::uuid), 31}},
   {"XpLevel", {offsetof(Player, xp_level), sizeof(Player::xp_level), 32}},
   {"XpP", {offsetof(Player, xp_p), sizeof(Player::xp_p), 33}},
   {"XpSeed", {offsetof(Player, xp_seed), sizeof(Player::xp_seed), 34}},
   {"XpTotal", {offsetof(Player, xp_total), sizeof(Player::xp_total), 35}},
   {"abilities", {offsetof(Player, abilities), sizeof(Player::abilities), 36}},
   {"foodExhaustionLevel", {offsetof(Player, food_exhaustion_level), sizeof(Player::food_exhaustion_level), 37}},
   {"foodLevel", {offsetof(Player, food_level), sizeof(Player::food_level), 38}},
   {"foodSaturationLevel", {offsetof(Player, food_saturation_level), sizeof(Player::food_saturation_level), 39}},
   {"foodTickTimer", {offsetof(Player, food_tick_timer), sizeof(Player::food_tick_timer), 40}},
   {"playerGameType", {offsetof(Player, player_game_type), sizeof(Player::player_game_type), 41}},
   {"recipeBook", {offsetof(Player, recipe_book), sizeof(Player::recipe_book), 42}},
   {"seenCredits", {offsetof(Player, seen_credits), sizeof(Player::seen_credits), 43}},
};

int Player::__xx_get_id(const std::string &name) const {
   auto it = __xx_offsets.find(name);
   if (it == __xx_offsets.end()) {
      return -1;
   }
   return it->second.id;
}

}