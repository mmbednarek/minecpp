#pragma once
#include <iostream>
#include <map>
#include <mb/int.h>
#include <mb/result.h>
#include <minecpp/nbt/Reader.h>
#include <minecpp/nbt/Writer.h>
#include <optional>
#include <string>
#include <vector>

namespace minecpp::nbt::player {

class Attribute {
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
 public:
   std::int32_t no_empty{};
   Memories() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Memories deserialize_no_header(minecpp::nbt::Reader &r);
   static Memories deserialize(std::istream &in);
};

class Brain {
 public:
   Memories memories{};
   Brain() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Brain deserialize_no_header(minecpp::nbt::Reader &r);
   static Brain deserialize(std::istream &in);
};

class InventoryElement {
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
