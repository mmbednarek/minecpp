#ifndef MINECPP_NBT_LEVEL_V1_LEVEL_H
#define MINECPP_NBT_LEVEL_V1_LEVEL_H
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

class Memories
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
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

class Brain
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
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

class Abilities
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
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

class RecipeBook
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
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
   RecipeBook() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static RecipeBook deserialize_no_header(minecpp::nbt::Reader &r);
   static RecipeBook deserialize(std::istream &in);
};

class Version
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::int32_t>) {
         if (in_field_name == "Id") {
            this->id = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int8_t>) {
         if (in_field_name == "Snapshot") {
            this->snapshot = std::forward<T>(in_value);
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
   std::int32_t id{};
   std::string name{};
   std::int8_t snapshot{};
   Version() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Version deserialize_no_header(minecpp::nbt::Reader &r);
   static Version deserialize(std::istream &in);
};

class BiomeSource
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::int64_t>) {
         if (in_field_name == "seed") {
            this->seed = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int8_t>) {
         if (in_field_name == "large_biomes") {
            this->large_biomes = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (in_field_name == "preset") {
            this->preset = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "type") {
            this->type = std::forward<T>(in_value);
            return;
         }
         return;
      }
   }

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

class Generator
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, BiomeSource>) {
         if (in_field_name == "biome_source") {
            this->biome_source = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int64_t>) {
         if (in_field_name == "seed") {
            this->seed = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (in_field_name == "settings") {
            this->settings = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "type") {
            this->type = std::forward<T>(in_value);
            return;
         }
         return;
      }
   }

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

class DimentionData
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, Generator>) {
         if (in_field_name == "generator") {
            this->generator = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (in_field_name == "type") {
            this->type = std::forward<T>(in_value);
            return;
         }
         return;
      }
   }

 public:
   Generator generator{};
   std::string type{};
   DimentionData() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static DimentionData deserialize_no_header(minecpp::nbt::Reader &r);
   static DimentionData deserialize(std::istream &in);
};

class Dimentions
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, DimentionData>) {
         if (in_field_name == "minecraft:overworld") {
            this->overworld = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "minecraft:the_end") {
            this->the_end = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "minecraft:the_nether") {
            this->the_nether = std::forward<T>(in_value);
            return;
         }
         return;
      }
   }

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

class WorldGen
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, Dimentions>) {
         if (in_field_name == "dimensions") {
            this->dimensions = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int64_t>) {
         if (in_field_name == "seed") {
            this->seed = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int8_t>) {
         if (in_field_name == "bonus_chest") {
            this->bonus_chest = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "generate_features") {
            this->generate_features = std::forward<T>(in_value);
            return;
         }
         return;
      }
   }

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

class DataPacks
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::vector<std::int64_t>>) {
         if (in_field_name == "Disabled") {
            this->disabled = std::forward<T>(in_value);
            return;
         }
         return;
      }
   }

 public:
   std::vector<std::int64_t> disabled{};
   DataPacks() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static DataPacks deserialize_no_header(minecpp::nbt::Reader &r);
   static DataPacks deserialize(std::istream &in);
};

class DragonFight
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::int8_t>) {
         if (in_field_name == "DragonKilled") {
            this->dragon_killed = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "PreviouslyKilled") {
            this->previously_killed = std::forward<T>(in_value);
            return;
         }
         return;
      }
   }

 public:
   std::int8_t dragon_killed{};
   std::int8_t previously_killed{};
   DragonFight() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static DragonFight deserialize_no_header(minecpp::nbt::Reader &r);
   static DragonFight deserialize(std::istream &in);
};

class CustomBossEvents
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
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
   CustomBossEvents() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static CustomBossEvents deserialize_no_header(minecpp::nbt::Reader &r);
   static CustomBossEvents deserialize(std::istream &in);
};

class Player
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
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
         if (in_field_name == "previousPlayerGameType") {
            this->previous_player_game_type = std::forward<T>(in_value);
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

class GameRules
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (in_field_name == "announceAdvancements") {
            this->announce_advancements = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "commandBlockOutput") {
            this->command_block_output = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "disableElytraMovementCheck") {
            this->disable_elytra_movement_check = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "disableRaids") {
            this->disable_raids = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "doDaylightCycle") {
            this->do_daylight_cycle = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "doEntityDrops") {
            this->do_entity_drops = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "doFireTick") {
            this->do_fire_tick = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "doImmediateRespawn") {
            this->do_immediate_respawn = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "doInsomnia") {
            this->do_insomnia = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "doLimitedCrafting") {
            this->do_limited_crafting = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "doMobLoot") {
            this->do_mob_loot = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "doMobSpawning") {
            this->do_mob_spawning = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "doPatrolSpawning") {
            this->do_patrol_spawning = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "doTileDrops") {
            this->do_tile_drops = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "doTraderSpawning") {
            this->do_trader_spawning = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "doWeatherCycle") {
            this->do_weather_cycle = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "drowningDamage") {
            this->drowning_damage = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "fallDamage") {
            this->fall_damage = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "fireDamage") {
            this->fire_damage = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "forgiveDeadPlayers") {
            this->forgive_dead_players = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "keepInventory") {
            this->keep_inventory = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "logAdminCommands") {
            this->log_admin_commands = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "maxCommandChainLength") {
            this->max_command_chain_length = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "maxEntityCramming") {
            this->max_entity_cramming = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "mobGriefing") {
            this->mob_griefing = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "naturalRegeneration") {
            this->natural_regeneration = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "randomTickSpeed") {
            this->random_tick_speed = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "reducedDebugInfo") {
            this->reduced_debug_info = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "sendCommandFeedback") {
            this->send_command_feedback = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "showDeathMessages") {
            this->show_death_messages = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "spawnRadius") {
            this->spawn_radius = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "spectatorsGenerateChunks") {
            this->spectators_generate_chunks = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "universalAnger") {
            this->universal_anger = std::forward<T>(in_value);
            return;
         }
         return;
      }
   }

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

class LevelData
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, CustomBossEvents>) {
         if (in_field_name == "CustomBossEvents") {
            this->custom_boss_events = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, DataPacks>) {
         if (in_field_name == "DataPacks") {
            this->data_packs = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, DragonFight>) {
         if (in_field_name == "DragonFight") {
            this->dragon_fight = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, GameRules>) {
         if (in_field_name == "GameRules") {
            this->game_rules = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, Player>) {
         if (in_field_name == "Player") {
            this->player = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, Version>) {
         if (in_field_name == "Version") {
            this->version = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, WorldGen>) {
         if (in_field_name == "WorldGenSettings") {
            this->world_gen_settings = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, double>) {
         if (in_field_name == "BorderCenterX") {
            this->border_center_x = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "BorderCenterZ") {
            this->border_center_z = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "BorderDamagePerBlock") {
            this->border_damage_per_block = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "BorderSafeZone") {
            this->border_safe_zone = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "BorderSize") {
            this->border_size = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "BorderSizeLerpTarget") {
            this->border_size_lerp_target = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "BorderWarningBlocks") {
            this->border_warning_blocks = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "BorderWarningTime") {
            this->border_warning_time = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int32_t>) {
         if (in_field_name == "DataVersion") {
            this->data_version = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "GameType") {
            this->game_type = std::forward<T>(in_value);
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
         if (in_field_name == "WanderingTraderSpawnChance") {
            this->wandering_trader_spawn_chance = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "WanderingTraderSpawnDelay") {
            this->wandering_trader_spawn_delay = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "clearWeatherTime") {
            this->clear_weather_time = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "rainTime") {
            this->rain_time = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "thunderTime") {
            this->thunder_time = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "version2") {
            this->version2 = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int64_t>) {
         if (in_field_name == "BorderSizeLerpTime") {
            this->border_size_lerp_time = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "DayTime") {
            this->day_time = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "LastPlayed") {
            this->last_played = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "Time") {
            this->time = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::int8_t>) {
         if (in_field_name == "Difficulty") {
            this->difficulty = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "DifficultyLocked") {
            this->difficulty_locked = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "WasModded") {
            this->was_modded = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "allowCommands") {
            this->allow_commands = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "hardcore") {
            this->hardcore = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "initialized") {
            this->initialized = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "raining") {
            this->raining = std::forward<T>(in_value);
            return;
         }
         if (in_field_name == "thundering") {
            this->thundering = std::forward<T>(in_value);
            return;
         }
         return;
      }
      if constexpr (std::is_same_v<TDc, std::string>) {
         if (in_field_name == "LevelName") {
            this->level_name = std::forward<T>(in_value);
            return;
         }
         return;
      }
   }

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

class Level
{

   template<typename T>
   void set_property(const std::string &in_field_name, T &&in_value)
   {
      using TDc = typename std::decay<T>::type;
      if constexpr (std::is_same_v<TDc, LevelData>) {
         if (in_field_name == "Data") {
            this->data = std::forward<T>(in_value);
            return;
         }
         return;
      }
   }

 public:
   LevelData data{};
   Level() = default;
   void serialize_no_header(minecpp::nbt::Writer &w) const;
   void serialize(std::ostream &out_stream, std::string_view in_compound_name) const;
   static Level deserialize_no_header(minecpp::nbt::Reader &r);
   static Level deserialize(std::istream &in);
};

}// namespace minecpp::nbt::level::v1
#endif//MINECPP_NBT_LEVEL_V1_LEVEL_H
