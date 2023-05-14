#ifndef MINECPP_NBT_PLAYER_V1_PLAYER_H
#define MINECPP_NBT_PLAYER_V1_PLAYER_H
#include <iostream>
#include <map>
#include <mb/int.h>
#include <mb/result.h>
#include <minecpp/nbt/Reader.h>
#include <minecpp/nbt/Writer.h>
#include <optional>
#include <string>
#include <vector>

namespace minecpp::nbt::player::v1 {

class Attribute {

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, double>) {
         if (in_field_name == "Base") {
            this->base = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (in_field_name == "Name") {
            this->name = std::forward<T>(in_value);
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
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Attribute deserialize_no_header(minecpp::nbt::Reader &r);
   static Attribute deserialize(std::istream &in);
};

class Memories {

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::int32_t>) {
         if (in_field_name == "no_empty") {
            this->no_empty = std::forward<T>(in_value);
            return;
         }
         return;
      }
   }

 public:
   std::int32_t no_empty{};
   Memories() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Memories deserialize_no_header(minecpp::nbt::Reader &r);
   static Memories deserialize(std::istream &in);
};

class Brain {

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, Memories>) {
         if (in_field_name == "memories") {
            this->memories = std::forward<T>(in_value);
            return;
         }
         return;
      }
   }

 public:
   Memories memories{};
   Brain() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Brain deserialize_no_header(minecpp::nbt::Reader &r);
   static Brain deserialize(std::istream &in);
};

class InventoryElement {

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::int8_t>) {
         if (in_field_name == "Count") {
            this->count = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "Slot") {
            this->slot = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (in_field_name == "id") {
            this->id = std::forward<T>(in_value);
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
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static InventoryElement deserialize_no_header(minecpp::nbt::Reader &r);
   static InventoryElement deserialize(std::istream &in);
};

class Abilities {

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, float>) {
         if (in_field_name == "flySpeed") {
            this->fly_speed = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "walkSpeed") {
            this->walk_speed = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int8_t>) {
         if (in_field_name == "flying") {
            this->flying = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "instabuild") {
            this->instabuild = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "invulnerable") {
            this->invulnerable = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "mayBuild") {
            this->may_build = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "mayfly") {
            this->mayfly = std::forward<T>(in_value);
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
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Abilities deserialize_no_header(minecpp::nbt::Reader &r);
   static Abilities deserialize(std::istream &in);
};

class RecipeBook {

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::int8_t>) {
         if (in_field_name == "isBlastingFurnaceFilteringCraftable") {
            this->is_blasting_furnace_filtering_craftable = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "isBlastingFurnaceGuiOpen") {
            this->is_blasting_furnace_gui_open = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "isFilteringCraftable") {
            this->is_filtering_craftable = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "isFurnaceFilteringCraftable") {
            this->is_furnace_filtering_craftable = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "isFurnaceGuiOpen") {
            this->is_furnace_gui_open = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "isGuiOpen") {
            this->is_gui_open = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "isSmokerFilteringCraftable") {
            this->is_smoker_filtering_craftable = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "isSmokerGuiOpen") {
            this->is_smoker_gui_open = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<std::string>>) {
         if (in_field_name == "recipes") {
            this->recipes = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "toBeDisplayed") {
            this->to_be_displayed = std::forward<T>(in_value);
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
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static RecipeBook deserialize_no_header(minecpp::nbt::Reader &r);
   static RecipeBook deserialize(std::istream &in);
};

class Player {

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value) {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, Abilities>) {
         if (in_field_name == "abilities") {
            this->abilities = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, Brain>) {
         if (in_field_name == "Brain") {
            this->brain = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, RecipeBook>) {
         if (in_field_name == "recipeBook") {
            this->recipe_book = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, float>) {
         if (in_field_name == "AbsorptionAmount") {
            this->absorption_amount = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "FallDistance") {
            this->fall_distance = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "Health") {
            this->health = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "SpawnAngle") {
            this->spawn_angle = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "XpP") {
            this->xp_p = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "foodExhaustionLevel") {
            this->food_exhaustion_level = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "foodSaturationLevel") {
            this->food_saturation_level = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int16_t>) {
         if (in_field_name == "Air") {
            this->air = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "DeathTime") {
            this->death_time = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "Fire") {
            this->fire = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "HurtTime") {
            this->hurt_time = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "SleepTimer") {
            this->sleep_timer = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int32_t>) {
         if (in_field_name == "DataVersion") {
            this->data_version = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "HurtByTimestamp") {
            this->hurt_by_timestamp = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "PortalCooldown") {
            this->portal_cooldown = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "Score") {
            this->score = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "SelectedItemSlot") {
            this->selected_item_slot = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "SpawnX") {
            this->spawn_x = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "SpawnY") {
            this->spawn_y = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "SpawnZ") {
            this->spawn_z = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "XpLevel") {
            this->xp_level = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "XpSeed") {
            this->xp_seed = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "XpTotal") {
            this->xp_total = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "foodLevel") {
            this->food_level = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "foodTickTimer") {
            this->food_tick_timer = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "playerGameType") {
            this->player_game_type = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int8_t>) {
         if (in_field_name == "FallFlying") {
            this->fall_flying = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "Invulnerable") {
            this->invulnerable = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "OnGround") {
            this->on_ground = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "SpawnForced") {
            this->spawn_forced = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "seenCredits") {
            this->seen_credits = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (in_field_name == "Dimension") {
            this->dimension = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "SpawnDimension") {
            this->spawn_dimension = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<Attribute>>) {
         if (in_field_name == "Attributes") {
            this->attributes = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<InventoryElement>>) {
         if (in_field_name == "Inventory") {
            this->inventory = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<double>>) {
         if (in_field_name == "Motion") {
            this->motion = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "Pos") {
            this->pos = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<float>>) {
         if (in_field_name == "Rotation") {
            this->rotation = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::vector<std::int32_t>>) {
         if (in_field_name == "UUID") {
            this->uuid = std::forward<T>(in_value);
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
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Player deserialize_no_header(minecpp::nbt::Reader &r);
   static Player deserialize(std::istream &in);
};

}
#endif//MINECPP_NBT_PLAYER_V1_PLAYER_H
