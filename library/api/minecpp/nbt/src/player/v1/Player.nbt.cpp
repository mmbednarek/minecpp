#include <minecpp/nbt/player/v1/Player.nbt.h>

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
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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
      return {};
   }
   return Memories::deserialize_no_header(r);
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
         if (name == "memories") {
            res.__xx_put(name, Memories::deserialize_no_header(r));
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
      default: 
         break;
      }
      r.skip_payload(tagid);
   });
   return res;
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

RecipeBook RecipeBook::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return RecipeBook::deserialize_no_header(r);
}

void Location::serialize_no_header(minecpp::nbt::Writer &w) const {
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

void Location::serialize(std::ostream &out, std::string_view name) const {
   minecpp::nbt::Writer w(out);
   w.begin_compound(name);
   serialize_no_header(w);
}

Location Location::deserialize_no_header(minecpp::nbt::Reader &r) {
   Location res;
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
         if (name == "Brain") {
            res.__xx_put(name, Brain::deserialize_no_header(r));
            return;
         }
         if (name == "abilities") {
            res.__xx_put(name, Abilities::deserialize_no_header(r));
            return;
         }
         if (name == "recipeBook") {
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
               if (name == "Attributes") {
                  std::vector<Attribute> ls(list_info0.size);
                  std::generate(ls.begin(), ls.end(), [&r]() {
                     return Attribute::deserialize_no_header(r);
                  });
                  res.__xx_put(name, ls);
                  return;
               }
               if (name == "Inventory") {
                  std::vector<InventoryElement> ls(list_info0.size);
                  std::generate(ls.begin(), ls.end(), [&r]() {
                     return InventoryElement::deserialize_no_header(r);
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

Location Location::deserialize(std::istream &in) {
   minecpp::nbt::Reader r(in);
   auto peek = r.peek_tag();
   if (peek.id != minecpp::nbt::TagId::Compound) {
      return {};
   }
   return Location::deserialize_no_header(r);
}

}