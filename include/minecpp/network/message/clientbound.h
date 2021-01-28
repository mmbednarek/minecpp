#pragma once
#include "writer.h"
#include <boost/uuid/uuid.hpp>
#include <cstdint>
#include <map>
#include <mb/int.h>
#include <minecpp/network/chat.h>
#include <minepb/chunk.pb.h>
#include <string_view>

namespace minecpp::network::message {

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

// 0x04
struct SpawnPlayer {
   int entity_id;
   boost::uuids::uuid id;
   double x, y, z;
   float yaw, pitch;
};
Writer serialize(SpawnPlayer msg);

// 0x05
struct AnimateHand {
   int entity_id;
   uint8_t type;
};
Writer serialize(AnimateHand msg);

struct BlockChange {
   mb::u64 block_position{};
   mb::u32 block_id{};
};
Writer serialize(BlockChange msg);

// 0x0f
struct MultiBlockChange {
   mb::u64 chunk_position{};
   bool distrust_edges = true;
   std::vector<mb::u64> block_changes{};
};
Writer serialize(MultiBlockChange msg);

// 0x0d
struct Difficulty {
   uint8_t difficulty;
   bool locked;
};
Writer serialize(Difficulty msg);

// 0x0e
struct Chat {
   std::string message;
   ChatType type;
   uuid user_id;
};
Writer serialize(Chat msg);

// 0x18
struct ServerBrand {
   std::string_view brand;
};
Writer serialize(ServerBrand msg);

// 0x1a
struct Disconnect {
   std::string_view reason;
};
Writer serialize(Disconnect msg);

// 0x1b
struct EntityStatus {
   uint32_t entity_id;
   uint8_t opcode;
};
Writer serialize(EntityStatus msg);

// 0x20
struct KeepAlive {
   uint64_t time;
};
Writer serialize(KeepAlive msg);

// 0x21
struct ChunkData {
   minecpp::chunk::NetChunk &chunk;
};
Writer serialize(ChunkData msg);

// 0x25
struct UpdateLight {
   minecpp::chunk::NetChunk &chunk;
};
Writer serialize(UpdateLight msg);

// 0x26
struct JoinGame {
   uint32_t player_id{};
   bool is_hardcore{};
   uint8_t game_mode{};
   uint8_t previous_game_mode{};
   std::vector<std::string> available_dimensions{};
   std::string dimension_codec{};
   std::string dimension_type{};
   std::string world_name{};
   uint64_t seed{};
   uint8_t max_players{};
   uint32_t view_distance{};
   bool reduced_debug_info{};
   bool immediate_respawn{};
};
Writer serialize(JoinGame msg);

// 0x29
struct EntityRelativeMove {
   int entity_id;
   short x, y, z;
   bool on_ground;
};
Writer serialize(EntityRelativeMove msg);

// 0x2a
struct EntityMove {
   int entity_id;
   short x, y, z;
   float yaw, pitch;
   bool on_ground;
};
Writer serialize(EntityMove msg);

// 0x2b
struct EntityLook {
   int entity_id;
   float yaw, pitch;
   bool on_ground;
};
Writer serialize(EntityLook msg);

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

// 0x34 0x04
struct RemovePlayer {
   uuid id;
};
Writer serialize(RemovePlayer msg);

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

// 0x38 0x01
struct DestroyEntity {
   uint32_t entity_id;
};
Writer serialize(DestroyEntity msg);

// 0x3c
struct EntityHeadLook {
   int entity_id;
   float yaw;
};
Writer serialize(EntityHeadLook msg);

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

} // namespace minecpp::network::Message
