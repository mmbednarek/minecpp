#ifndef MINECPP_NBT_PLAYER_V1_PLAYER_H
#define MINECPP_NBT_PLAYER_V1_PLAYER_H
#include <iostream>
#include <map>
#include <mb/int.h>
#include <mb/result.h>
#include <minecpp/nbt/reader.h>
#include <minecpp/nbt/writer.h>
#include <string>
#include <vector>

namespace minecpp::nbt::player::v1 {

#ifndef MINECPP_NBT_PLAYER_V1_PLAYER_H_OFFSET_CLASS
#define MINECPP_NBT_PLAYER_V1_PLAYER_H_OFFSET_CLASS
class __nbt_idl_offset {
 public:
   mb::size offset{};
   mb::size size{};
   int id{};
};
#endif//MINECPP_NBT_PLAYER_V1_PLAYER_H_OFFSET_CLASS

class Attribute {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      if constexpr (std::is_same_v<T, double>) {
         if (name == "Base") {
            this->base = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<T, std::string>) {
         if (name == "Name") {
            this->name = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   double base{};
   std::string name{};
   Attribute() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static Attribute deserialize_no_header(minecpp::nbt::Reader &r);
   static Attribute deserialize(std::istream &in);
};

class Memories {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
   }

 public:
   Memories() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static Memories deserialize_no_header(minecpp::nbt::Reader &r);
   static Memories deserialize(std::istream &in);
};

class Brain {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      if constexpr (std::is_same_v<T, Memories>) {
         if (name == "memories") {
            this->memories = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   Memories memories{};
   Brain() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static Brain deserialize_no_header(minecpp::nbt::Reader &r);
   static Brain deserialize(std::istream &in);
};

class InventoryElement {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      if constexpr (std::is_same_v<T, std::int8_t>) {
         if (name == "Count") {
            this->count = std::forward<T>(value);
            return;
         }
         if (name == "Slot") {
            this->slot = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<T, std::string>) {
         if (name == "id") {
            this->id = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   std::int8_t count{};
   std::int8_t slot{};
   std::string id{};
   InventoryElement() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static InventoryElement deserialize_no_header(minecpp::nbt::Reader &r);
   static InventoryElement deserialize(std::istream &in);
};

class Abilities {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      if constexpr (std::is_same_v<T, float>) {
         if (name == "flySpeed") {
            this->fly_speed = std::forward<T>(value);
            return;
         }
         if (name == "walkSpeed") {
            this->walk_speed = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<T, std::int8_t>) {
         if (name == "flying") {
            this->flying = std::forward<T>(value);
            return;
         }
         if (name == "instabuild") {
            this->instabuild = std::forward<T>(value);
            return;
         }
         if (name == "invulnerable") {
            this->invulnerable = std::forward<T>(value);
            return;
         }
         if (name == "mayBuild") {
            this->may_build = std::forward<T>(value);
            return;
         }
         if (name == "mayfly") {
            this->mayfly = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   float fly_speed{};
   std::int8_t flying{};
   std::int8_t instabuild{};
   std::int8_t invulnerable{};
   std::int8_t may_build{};
   std::int8_t mayfly{};
   float walk_speed{};
   Abilities() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static Abilities deserialize_no_header(minecpp::nbt::Reader &r);
   static Abilities deserialize(std::istream &in);
};

class RecipeBook {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      if constexpr (std::is_same_v<T, std::int8_t>) {
         if (name == "isBlastingFurnaceFilteringCraftable") {
            this->is_blasting_furnace_filtering_craftable = std::forward<T>(value);
            return;
         }
         if (name == "isBlastingFurnaceGuiOpen") {
            this->is_blasting_furnace_gui_open = std::forward<T>(value);
            return;
         }
         if (name == "isFilteringCraftable") {
            this->is_filtering_craftable = std::forward<T>(value);
            return;
         }
         if (name == "isFurnaceFilteringCraftable") {
            this->is_furnace_filtering_craftable = std::forward<T>(value);
            return;
         }
         if (name == "isFurnaceGuiOpen") {
            this->is_furnace_gui_open = std::forward<T>(value);
            return;
         }
         if (name == "isGuiOpen") {
            this->is_gui_open = std::forward<T>(value);
            return;
         }
         if (name == "isSmokerFilteringCraftable") {
            this->is_smoker_filtering_craftable = std::forward<T>(value);
            return;
         }
         if (name == "isSmokerGuiOpen") {
            this->is_smoker_gui_open = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<T, std::vector<std::string>>) {
         if (name == "recipes") {
            this->recipes = std::forward<T>(value);
            return;
         }
         if (name == "toBeDisplayed") {
            this->to_be_displayed = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   std::int8_t is_blasting_furnace_filtering_craftable{};
   std::int8_t is_blasting_furnace_gui_open{};
   std::int8_t is_filtering_craftable{};
   std::int8_t is_furnace_filtering_craftable{};
   std::int8_t is_furnace_gui_open{};
   std::int8_t is_gui_open{};
   std::int8_t is_smoker_filtering_craftable{};
   std::int8_t is_smoker_gui_open{};
   std::vector<std::string> recipes{};
   std::vector<std::string> to_be_displayed{};
   RecipeBook() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static RecipeBook deserialize_no_header(minecpp::nbt::Reader &r);
   static RecipeBook deserialize(std::istream &in);
};

class Player {

   template<typename T>
   void __xx_put(const std::string &name, T &&value) {
      if constexpr (std::is_same_v<T, Abilities>) {
         if (name == "abilities") {
            this->abilities = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<T, Brain>) {
         if (name == "Brain") {
            this->brain = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<T, RecipeBook>) {
         if (name == "recipeBook") {
            this->recipe_book = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<T, float>) {
         if (name == "AbsorptionAmount") {
            this->absorption_amount = std::forward<T>(value);
            return;
         }
         if (name == "FallDistance") {
            this->fall_distance = std::forward<T>(value);
            return;
         }
         if (name == "Health") {
            this->health = std::forward<T>(value);
            return;
         }
         if (name == "SpawnAngle") {
            this->spawn_angle = std::forward<T>(value);
            return;
         }
         if (name == "XpP") {
            this->xp_p = std::forward<T>(value);
            return;
         }
         if (name == "foodExhaustionLevel") {
            this->food_exhaustion_level = std::forward<T>(value);
            return;
         }
         if (name == "foodSaturationLevel") {
            this->food_saturation_level = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<T, std::int16_t>) {
         if (name == "Air") {
            this->air = std::forward<T>(value);
            return;
         }
         if (name == "DeathTime") {
            this->death_time = std::forward<T>(value);
            return;
         }
         if (name == "Fire") {
            this->fire = std::forward<T>(value);
            return;
         }
         if (name == "HurtTime") {
            this->hurt_time = std::forward<T>(value);
            return;
         }
         if (name == "SleepTimer") {
            this->sleep_timer = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<T, std::int32_t>) {
         if (name == "DataVersion") {
            this->data_version = std::forward<T>(value);
            return;
         }
         if (name == "HurtByTimestamp") {
            this->hurt_by_timestamp = std::forward<T>(value);
            return;
         }
         if (name == "PortalCooldown") {
            this->portal_cooldown = std::forward<T>(value);
            return;
         }
         if (name == "Score") {
            this->score = std::forward<T>(value);
            return;
         }
         if (name == "SelectedItemSlot") {
            this->selected_item_slot = std::forward<T>(value);
            return;
         }
         if (name == "SpawnX") {
            this->spawn_x = std::forward<T>(value);
            return;
         }
         if (name == "SpawnY") {
            this->spawn_y = std::forward<T>(value);
            return;
         }
         if (name == "SpawnZ") {
            this->spawn_z = std::forward<T>(value);
            return;
         }
         if (name == "XpLevel") {
            this->xp_level = std::forward<T>(value);
            return;
         }
         if (name == "XpSeed") {
            this->xp_seed = std::forward<T>(value);
            return;
         }
         if (name == "XpTotal") {
            this->xp_total = std::forward<T>(value);
            return;
         }
         if (name == "foodLevel") {
            this->food_level = std::forward<T>(value);
            return;
         }
         if (name == "foodTickTimer") {
            this->food_tick_timer = std::forward<T>(value);
            return;
         }
         if (name == "playerGameType") {
            this->player_game_type = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<T, std::int8_t>) {
         if (name == "FallFlying") {
            this->fall_flying = std::forward<T>(value);
            return;
         }
         if (name == "Invulnerable") {
            this->invulnerable = std::forward<T>(value);
            return;
         }
         if (name == "OnGround") {
            this->on_ground = std::forward<T>(value);
            return;
         }
         if (name == "SpawnForced") {
            this->spawn_forced = std::forward<T>(value);
            return;
         }
         if (name == "seenCredits") {
            this->seen_credits = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<T, std::string>) {
         if (name == "Dimension") {
            this->dimension = std::forward<T>(value);
            return;
         }
         if (name == "SpawnDimension") {
            this->spawn_dimension = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<T, std::vector<Attribute>>) {
         if (name == "Attributes") {
            this->attributes = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<T, std::vector<InventoryElement>>) {
         if (name == "Inventory") {
            this->inventory = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<T, std::vector<double>>) {
         if (name == "Motion") {
            this->motion = std::forward<T>(value);
            return;
         }
         if (name == "Pos") {
            this->pos = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<T, std::vector<float>>) {
         if (name == "Rotation") {
            this->rotation = std::forward<T>(value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<T, std::vector<std::int32_t>>) {
         if (name == "UUID") {
            this->uuid = std::forward<T>(value);
            return;
         }
         return;
      }
   }

 public:
   float absorption_amount{};
   std::int16_t air{};
   std::vector<Attribute> attributes{};
   Brain brain{};
   std::int32_t data_version{};
   std::int16_t death_time{};
   std::string dimension{};
   float fall_distance{};
   std::int8_t fall_flying{};
   std::int16_t fire{};
   float health{};
   std::int32_t hurt_by_timestamp{};
   std::int16_t hurt_time{};
   std::vector<InventoryElement> inventory{};
   std::int8_t invulnerable{};
   std::vector<double> motion{};
   std::int8_t on_ground{};
   std::int32_t portal_cooldown{};
   std::vector<double> pos{};
   std::vector<float> rotation{};
   std::int32_t score{};
   std::int32_t selected_item_slot{};
   std::int16_t sleep_timer{};
   float spawn_angle{};
   std::string spawn_dimension{};
   std::int8_t spawn_forced{};
   std::int32_t spawn_x{};
   std::int32_t spawn_y{};
   std::int32_t spawn_z{};
   std::vector<std::int32_t> uuid{};
   std::int32_t xp_level{};
   float xp_p{};
   std::int32_t xp_seed{};
   std::int32_t xp_total{};
   Abilities abilities{};
   float food_exhaustion_level{};
   std::int32_t food_level{};
   float food_saturation_level{};
   std::int32_t food_tick_timer{};
   std::int32_t player_game_type{};
   RecipeBook recipe_book{};
   std::int8_t seen_credits{};
   Player() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out, std::string_view name) const;
   static Player deserialize_no_header(minecpp::nbt::Reader &r);
   static Player deserialize(std::istream &in);
};

}
#endif//MINECPP_NBT_PLAYER_V1_PLAYER_H
