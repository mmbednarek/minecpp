#pragma once
#include "writer.h"
#include <boost/uuid/uuid.hpp>
#include <cstdint>
#include <map>
#include <mineutils/buffer.h>
#include <string_view>

namespace MineNet::Message {

using boost::uuids::uuid;

// 0x00
struct SpawnObject {
   uint32_t entity_id;
   uuid unique_id;
   int entity_type;
   double x, y, z;
   uint8_t pitch, yaw;
   int data;
   uint16_t vel_x, vel_y, vel_z;
};
Writer serialize(SpawnObject msg);

// 0x01
struct SpawnExperienceOrb {
   uint32_t entity_id;
   double x, y, z;
   uint16_t xp_value;
};
Writer serialize(SpawnExperienceOrb msg);

// 0x0e
struct Difficulty {
   uint8_t difficulty;
   bool locked;
};
Writer serialize(Difficulty msg);

// 0x19
struct ServerBrand {
   std::string_view brand;
};
Writer serialize(ServerBrand msg);

// 0x1c
struct EntityStatus {
   uint32_t entity_id;
   uint8_t opcode;
};
Writer serialize(EntityStatus msg);

// 0x25
struct UpdateLight {
   int chunk_x, chunk_z;
   int sky_update_mask;
   int block_update_mask;
   int sky_reset_mask;
   int block_reset_mask;
   Utils::BasicBuffer sky;
   Utils::BasicBuffer blocks;
};
Writer serialize(UpdateLight msg);

// 0x26
struct JoinGame {
   uint32_t player_id{};
   uint8_t game_mode{};
   uint32_t dimension{};
   uint64_t seed{};
   uint8_t max_players{};
   std::string_view world_type{};
   uint32_t view_distance{};
   bool reduced_debug_info{};
   bool immediate_respawn{};
};
Writer serialize(JoinGame msg);

enum PlayerAbilityFlag : uint8_t {
   Invulnerable = 1u << 0u,
   IsFlying = 1u << 1u,
   AllowFlying = 1u << 2u,
   CreativeMode = 1u << 3u,
};

// 0x32
struct PlayerAbilities {
   uint8_t flags;
   float fly_speed, walk_speed;
};
Writer serialize(PlayerAbilities msg);

// 0x34 0x00
struct AddPlayer {
   uuid id;
   std::string_view name;
   std::map<std::string, std::string> properties;
   uint8_t game_mode;
   uint32_t ping;
};
Writer serialize(AddPlayer msg);

// 0x36
struct PlayerPositionLook {
   double x, y, z;
   float yaw, pitch;
   uint8_t flags;
   int tp_id;
};
Writer serialize(PlayerPositionLook msg);

enum RecipeBookState { Init, Add, Remove };

// 0x37
struct RecipeBook {
   RecipeBookState state;
   bool gui_open;
   bool filtering_craftable;
   bool furnace_gui_open;
   bool furnace_filtering_craftable;
};
Writer serialize(RecipeBook msg);

// 0x40
struct HeldItem {
   uint8_t item;
};
Writer serialize(HeldItem msg);

// 0x41
struct UpdateChunkPosition {
   int x, z;
};
Writer serialize(UpdateChunkPosition msg);

struct Raw {
   size_t size;
   const char *data;
};
Writer serialize(Raw msg);

} // namespace MineNet::Message
