#include "rules.h"

namespace Game {

Rules read_rules(NBT::Reader &r) {
   return Rules{
       .announce_advancements = r.find_bool_str("announceAdvancements", true),
       .command_block_output = r.find_bool_str("commandBlockOutput", true),
       .disable_elytra_movement_check =
           r.find_bool_str("disableElytraMovementCheck", false),
       .disable_raids = r.find_bool_str("disableRaids", false),
       .do_daylight_cycle = r.find_bool_str("doDaylightCycle", true),
       .do_entity_drops = r.find_bool_str("doEntityDrops", true),
       .do_fire_tick = r.find_bool_str("doFireTick", true),
       .do_immediate_respawn = r.find_bool_str("doImmediateRespawn", false),
       .do_insomnia = r.find_bool_str("doInsomnia", true),
       .do_limited_crafting = r.find_bool_str("doLimitedCrafting", false),
       .do_mob_loot = r.find_bool_str("doMobLoot", true),
       .do_mob_spawning = r.find_bool_str("doMobSpawning", true),
       .do_patrol_spawning = r.find_bool_str("doPatrolSpawning", true),
       .do_tile_drops = r.find_bool_str("doTileDrops", true),
       .do_trader_spawning = r.find_bool_str("doTraderSpawning", true),
       .do_weather_cycle = r.find_bool_str("doWeatherCycle", true),
       .do_drowning_damage = r.find_bool_str("doDrowningDamage", true),
       .do_fall_damage = r.find_bool_str("doFallDamage", true),
       .do_fire_damage = r.find_bool_str("doFireDamage", true),
       .keep_inventory = r.find_bool_str("keepInventory", false),
       .log_admin_commands = r.find_bool_str("logAdminCommands", true),
       .max_command_chain_length = std::stoi(
           r.find_value<NBT::String>("maxCommandChainLength", "65536")),
       .max_entity_cramming =
           std::stoi(r.find_value<NBT::String>("maxEntityCramming", "24")),
       .mob_griefing = r.find_bool_str("mobGriefing", true),
       .natural_regeneration = r.find_bool_str("naturalRegeneration", true),
       .random_tick_speed =
           std::stoi(r.find_value<NBT::String>("randomTickSpeed", "3")),
       .reduced_debug_info = r.find_bool_str("reducedDebugInfo", false),
       .send_command_feedback = r.find_bool_str("sendCommandFeedback", true),
       .show_death_message = r.find_bool_str("showDeathMessage", true),
       .spawn_radius =
           std::stoi(r.find_value<NBT::String>("spawnRadius", "10")),
       .spectator_generate_chunks =
           r.find_bool_str("spectatorGenerateChunks", true),
   };
}

} // namespace Game
