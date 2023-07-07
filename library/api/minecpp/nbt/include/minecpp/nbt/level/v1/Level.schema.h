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

namespace minecpp::nbt::level::v1 {

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
   RecipeBook() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static RecipeBook deserialize_no_header(minecpp::nbt::Reader &r);
   static RecipeBook deserialize(std::istream &in);
};

class Version {
 public:
   std::int32_t id{};
   std::string name{};
   std::int8_t snapshot{};
   Version() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Version deserialize_no_header(minecpp::nbt::Reader &r);
   static Version deserialize(std::istream &in);
};

class BiomeSource {
 public:
   std::string preset{};
   std::int8_t large_biomes{};
   std::int64_t seed{};
   std::string type{};
   BiomeSource() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static BiomeSource deserialize_no_header(minecpp::nbt::Reader &r);
   static BiomeSource deserialize(std::istream &in);
};

class Generator {
 public:
   BiomeSource biome_source{};
   std::int64_t seed{};
   std::string settings{};
   std::string type{};
   Generator() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Generator deserialize_no_header(minecpp::nbt::Reader &r);
   static Generator deserialize(std::istream &in);
};

class DimentionData {
 public:
   Generator generator{};
   std::string type{};
   DimentionData() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static DimentionData deserialize_no_header(minecpp::nbt::Reader &r);
   static DimentionData deserialize(std::istream &in);
};

class Dimentions {
 public:
   DimentionData overworld{};
   DimentionData the_end{};
   DimentionData the_nether{};
   Dimentions() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Dimentions deserialize_no_header(minecpp::nbt::Reader &r);
   static Dimentions deserialize(std::istream &in);
};

class WorldGen {
 public:
   std::int8_t bonus_chest{};
   Dimentions dimensions{};
   std::int8_t generate_features{};
   std::int64_t seed{};
   WorldGen() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static WorldGen deserialize_no_header(minecpp::nbt::Reader &r);
   static WorldGen deserialize(std::istream &in);
};

class DataPacks {
 public:
   std::vector<std::int64_t> disabled{};
   DataPacks() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static DataPacks deserialize_no_header(minecpp::nbt::Reader &r);
   static DataPacks deserialize(std::istream &in);
};

class DragonFight {
 public:
   std::int8_t dragon_killed{};
   std::int8_t previously_killed{};
   DragonFight() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static DragonFight deserialize_no_header(minecpp::nbt::Reader &r);
   static DragonFight deserialize(std::istream &in);
};

class CustomBossEvents {
 public:
   std::int32_t no_empty{};
   CustomBossEvents() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static CustomBossEvents deserialize_no_header(minecpp::nbt::Reader &r);
   static CustomBossEvents deserialize(std::istream &in);
};

class Player {
 public:
   float absorption_amount{};
   std::int16_t air{};
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
   std::int8_t invulnerable{};
   std::int8_t on_ground{};
   std::int32_t portal_cooldown{};
   std::int32_t score{};
   std::int32_t selected_item_slot{};
   std::int16_t sleep_timer{};
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
   std::int32_t previous_player_game_type{};
   RecipeBook recipe_book{};
   std::int8_t seen_credits{};
   Player() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Player deserialize_no_header(minecpp::nbt::Reader &r);
   static Player deserialize(std::istream &in);
};

class GameRules {
 public:
   std::string announce_advancements{};
   std::string command_block_output{};
   std::string disable_elytra_movement_check{};
   std::string disable_raids{};
   std::string do_daylight_cycle{};
   std::string do_entity_drops{};
   std::string do_fire_tick{};
   std::string do_immediate_respawn{};
   std::string do_insomnia{};
   std::string do_limited_crafting{};
   std::string do_mob_loot{};
   std::string do_mob_spawning{};
   std::string do_patrol_spawning{};
   std::string do_tile_drops{};
   std::string do_trader_spawning{};
   std::string do_weather_cycle{};
   std::string drowning_damage{};
   std::string fall_damage{};
   std::string fire_damage{};
   std::string forgive_dead_players{};
   std::string keep_inventory{};
   std::string log_admin_commands{};
   std::string max_command_chain_length{};
   std::string max_entity_cramming{};
   std::string mob_griefing{};
   std::string natural_regeneration{};
   std::string random_tick_speed{};
   std::string reduced_debug_info{};
   std::string send_command_feedback{};
   std::string show_death_messages{};
   std::string spawn_radius{};
   std::string spectators_generate_chunks{};
   std::string universal_anger{};
   GameRules() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static GameRules deserialize_no_header(minecpp::nbt::Reader &r);
   static GameRules deserialize(std::istream &in);
};

class LevelData {
 public:
   double border_center_x{};
   double border_center_z{};
   double border_damage_per_block{};
   double border_safe_zone{};
   double border_size{};
   double border_size_lerp_target{};
   std::int64_t border_size_lerp_time{};
   double border_warning_blocks{};
   double border_warning_time{};
   CustomBossEvents custom_boss_events{};
   DataPacks data_packs{};
   std::int32_t data_version{};
   std::int64_t day_time{};
   std::int8_t difficulty{};
   std::int8_t difficulty_locked{};
   DragonFight dragon_fight{};
   GameRules game_rules{};
   std::int32_t game_type{};
   std::int64_t last_played{};
   std::string level_name{};
   Player player{};
   std::int32_t spawn_x{};
   std::int32_t spawn_y{};
   std::int32_t spawn_z{};
   std::int64_t time{};
   Version version{};
   std::int32_t wandering_trader_spawn_chance{};
   std::int32_t wandering_trader_spawn_delay{};
   std::int8_t was_modded{};
   WorldGen world_gen_settings{};
   std::int8_t allow_commands{};
   std::int32_t clear_weather_time{};
   std::int8_t hardcore{};
   std::int8_t initialized{};
   std::int32_t rain_time{};
   std::int8_t raining{};
   std::int32_t thunder_time{};
   std::int8_t thundering{};
   std::int32_t version2{};
   LevelData() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static LevelData deserialize_no_header(minecpp::nbt::Reader &r);
   static LevelData deserialize(std::istream &in);
};

class Level {
 public:
   LevelData data{};
   Level() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Level deserialize_no_header(minecpp::nbt::Reader &r);
   static Level deserialize(std::istream &in);
};

}
