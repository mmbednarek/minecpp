#pragma once
#include <minecpp/nbt/reader.h>

namespace Game {

struct Rules {
	bool announce_advancements;
	bool command_block_output;
	bool disable_elytra_movement_check;
	bool disable_raids;
	bool do_daylight_cycle;
	bool do_entity_drops;
	bool do_fire_tick;
	bool do_immediate_respawn;
	bool do_insomnia;
	bool do_limited_crafting;
	bool do_mob_loot;
	bool do_mob_spawning;
	bool do_patrol_spawning;
	bool do_tile_drops;
	bool do_trader_spawning;
	bool do_weather_cycle;
	bool do_drowning_damage;
	bool do_fall_damage;
	bool do_fire_damage;
	bool keep_inventory;
	bool log_admin_commands;
	int max_command_chain_length;
	int max_entity_cramming;
	bool mob_griefing;
	bool natural_regeneration;
	int random_tick_speed;
	bool reduced_debug_info;
	bool send_command_feedback;
	bool show_death_message;
	int spawn_radius;
	bool spectator_generate_chunks;
};

}
