#pragma once
#include "minecpp/game/Game.h"
#include "Writer.h"
#include <boost/uuid/uuid.hpp>
#include <cstdint>
#include <map>
#include <mb/int.h>
#include <minecpp/chat/Chat.h>
#include <minecpp/proto/chunk/v1/Chunk.pb.h>
#include <string_view>

namespace minecpp::network::message {

using boost::uuids::uuid;

// 0x00
struct SpawnEntity
{
   uint32_t entity_id;
   uuid unique_id;
   int entity_type;
   double x, y, z;
   float yaw, pitch, head_yaw;
   int data;
   uint16_t vel_x, vel_y, vel_z;

   [[nodiscard]] Writer serialize() const;
};

// 0x01
struct SpawnExperienceOrb
{
   uint32_t entity_id;
   double x, y, z;
   uint16_t xp_value;

   [[nodiscard]] Writer serialize() const;
};

// 0x02
struct SpawnPlayer
{
   mb::u32 entity_id;
   boost::uuids::uuid id;
   double x, y, z;
   float yaw, pitch;

   [[nodiscard]] Writer serialize() const;
};

// 0x05
struct AnimateEntity
{
   int entity_id;
   uint8_t type;

   [[nodiscard]] Writer serialize() const;
};

// 0x05
struct AcknowledgeBlockChanges
{
   int sequence_id;
   [[nodiscard]] Writer serialize() const;
};

struct BlockChange
{
   mb::u64 block_position{};
   mb::u32 block_id{};

   [[nodiscard]] Writer serialize() const;
};

// 0x0f
struct MultiBlockChange
{
   mb::u64 chunk_position{};
   bool distrust_edges = true;
   std::vector<mb::u64> block_changes{};

   [[nodiscard]] Writer serialize() const;
};

// 0x0d
struct Difficulty
{
   uint8_t difficulty;
   bool locked;

   [[nodiscard]] Writer serialize() const;
};

// 0x0e
struct SystemChat
{
   std::string message;
   chat::MessageType type;

   [[nodiscard]] Writer serialize() const;
};

struct SetSlot
{
   uint8_t window_id;
   int state_id;
   short slot;
   int item_id;
   uint8_t count;

   [[nodiscard]] Writer serialize() const;
};

// 0x18
struct ServerBrand
{
   std::string_view brand;

   [[nodiscard]] Writer serialize() const;
};

// 0x1a
struct Disconnect
{
   std::string_view reason;

   [[nodiscard]] Writer serialize() const;
};

// 0x1b
struct EntityStatus
{
   uint32_t entity_id;
   uint8_t opcode;

   [[nodiscard]] Writer serialize() const;
};

// 0x20
struct KeepAlive
{
   uint64_t time;

   [[nodiscard]] Writer serialize() const;
};

// 0x21
struct ChunkData
{
   const minecpp::proto::chunk::v1::Chunk &chunk;

   [[nodiscard]] Writer serialize() const;
};

struct UnloadChunk
{
   mb::i32 chunk_x;
   mb::i32 chunk_z;

   [[nodiscard]] Writer serialize() const;
};

// 0x25
struct UpdateLight
{
   minecpp::proto::chunk::v1::Chunk &chunk;

   [[nodiscard]] Writer serialize() const;
};

struct UpdateBlockLight
{
   game::ChunkPosition chunk_position;
   std::map<int, std::vector<char>> block_light;

   [[nodiscard]] Writer serialize() const;
};

// 0x26
struct JoinGame
{
   uint32_t player_id{};
   bool is_hardcore{};
   uint8_t game_mode{};
   uint8_t previous_game_mode{};
   std::vector<std::string> available_dimensions{};
   std::string dimension_codec{};
   std::string dimension_name{};
   std::string world_name{};
   uint64_t seed{};
   uint8_t max_players{};
   uint32_t view_distance{};
   uint32_t simulation_distance{};
   bool reduced_debug_info{};
   bool immediate_respawn{};
   bool has_last_death_location{};
   bool is_debug{};
   bool is_flat{};
   std::uint64_t last_death_position{};

   [[nodiscard]] Writer serialize() const;
};

// 0x29
struct EntityRelativeMove
{
   int entity_id;
   short x, y, z;
   bool on_ground;

   [[nodiscard]] Writer serialize() const;
};

// 0x2a
struct EntityMove
{
   int entity_id;
   short x, y, z;
   float yaw, pitch;
   bool on_ground;

   [[nodiscard]] Writer serialize() const;
};

// 0x2b
struct EntityLook
{
   int entity_id;
   float yaw, pitch;
   bool on_ground;

   [[nodiscard]] Writer serialize() const;
};

enum PlayerAbilityFlag : uint8_t
{
   Invulnerable = 1u << 0u,
   IsFlying     = 1u << 1u,
   AllowFlying  = 1u << 2u,
   CreativeMode = 1u << 3u,
};

// 0x32
struct PlayerAbilities
{
   uint8_t flags;
   float fly_speed, field_of_view;

   [[nodiscard]] Writer serialize() const;
};

// 0x34 0x00
struct AddPlayer
{
   uuid id;
   std::string_view name;
   std::map<std::string, std::string> properties;
   uint8_t game_mode;
   uint32_t ping;

   [[nodiscard]] Writer serialize() const;
};

// 0x34 0x04
struct RemovePlayer
{
   uuid id;

   [[nodiscard]] Writer serialize() const;
};

// 0x36
struct PlayerPositionLook
{
   double x, y, z;
   float yaw, pitch;
   uint8_t flags;
   int tp_id;
   bool dismount_vehicle;

   [[nodiscard]] Writer serialize() const;
};

enum RecipeBookState
{
   Init,
   Add,
   Remove
};

// 0x37
struct RecipeBook
{
   RecipeBookState state;
   bool gui_open;
   bool filtering_craftable;
   bool furnace_gui_open;
   bool furnace_filtering_craftable;

   [[nodiscard]] Writer serialize() const;
};

// 0x38 0x01
struct DestroyEntity
{
   uint32_t entity_id;

   [[nodiscard]] Writer serialize() const;
};

// 0x3c
struct EntityHeadLook
{
   int entity_id;
   float yaw;

   [[nodiscard]] Writer serialize() const;
};

// 0x40
struct HeldItem
{
   uint8_t item;

   [[nodiscard]] Writer serialize() const;
};

// 0x41
struct UpdateChunkPosition
{
   int x, z;

   [[nodiscard]] Writer serialize() const;
};

// 0x4c
struct SetDefaultSpawnPosition
{
   std::uint64_t position{};
   float angle;

   [[nodiscard]] Writer serialize() const;
};

struct SetEquipment
{
   std::uint32_t entity_id{};
   std::uint8_t slot{};
   bool present{};
   std::uint32_t item_id{};
   int count{};

   [[nodiscard]] Writer serialize() const;
};

struct SetHealth
{
   float health{};
   int food{};
   float food_saturation{};

   [[nodiscard]] Writer serialize() const;
};

struct EntityMetadataSlot
{
   std::uint32_t entity_id{};
   std::uint8_t index{};
   std::uint32_t item_id{};
   int count{};

   [[nodiscard]] Writer serialize() const;
};

struct PickupItem
{
   std::uint32_t collected_entity_id{};
   std::uint32_t collector_entity_id{};
   std::uint32_t count{};

   [[nodiscard]] Writer serialize() const;
};

struct SetEntityVelocity
{
   std::uint32_t entity_id{};
   math::Vector3s velocity{};

   [[nodiscard]] Writer serialize() const;
};

struct Raw
{
   size_t size;
   const char *data;

   [[nodiscard]] Writer serialize() const;
};

}// namespace minecpp::network::message
