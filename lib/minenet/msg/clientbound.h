#pragma once
#include "writer.h"
#include <boost/uuid/uuid.hpp>
#include <cstdint>
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
Writer serialize(ServerBrand  msg);

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

// 0x40
struct HeldItem {
   uint8_t item;
};
Writer serialize(HeldItem msg);

} // namespace MineNet::Message
