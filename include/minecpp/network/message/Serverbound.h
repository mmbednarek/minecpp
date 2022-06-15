#pragma once
#include "File.h"
#include <minecpp/game/Hand.h>
#include <minecpp/chat/Chat.h>
#include <string>

namespace minecpp::network::message {

// 0x03

struct ChatCommand
{
   std::string command;
   mb::u64 timestamp;
   mb::u64 salt;
   std::map<std::string, std::string> argument_signatures;
   bool preview;
};

void deserialize(Reader &r, ChatCommand &msg);

// 0x04

struct ChatMessage
{
   std::string message;
   mb::u64 timestamp;
   mb::u64 salt;
   std::string salt_data;
   bool preview;
};

void deserialize(Reader &r, ChatMessage &msg);

// 0x05
struct ClientSettings
{
   std::string lang;
   uint8_t view;
   chat::ChatVisibility visibility;
   bool enable_colors;
   uint8_t model_part_flags;
   game::HandSide hand_side;
   bool enable_text_filtering;
   bool allow_server_listing;
};

void deserialize(Reader &r, ClientSettings &msg);

// 0x08
struct ClickWindow
{
   struct Slot
   {
      short slot_id;
      int item_id;
      uint8_t count;
   };

   uint8_t window_id;
   int state_id;
   short slot;
   uint8_t button;
   int mode;
   std::vector<Slot> slots;
   int carried_item_id;
   uint8_t carried_count;
};

void deserialize(Reader &r, ClickWindow &msg);

// 0x0a
struct PluginMessage
{
   std::string channel;
   std::string data;
};

void deserialize(Reader &r, PluginMessage &msg);

// 0x0f
struct KeepAliveClient
{
   uint64_t time;
};

void deserialize(Reader &r, KeepAliveClient &msg);

// 0x11
struct PlayerPosition
{
   double x, y, z;
   bool on_ground;
};

void deserialize(Reader &r, PlayerPosition &msg);

// 0x12
struct PlayerPositionRotation
{
   double x, y, z;
   float yaw, pitch;
   bool on_ground;
};

void deserialize(Reader &r, PlayerPositionRotation &msg);

// 0x13
struct PlayerRotation
{
   float yaw, pitch;
   bool on_ground;
};

void deserialize(Reader &r, PlayerRotation &msg);

// 0x1a
struct PlayerDigging
{
   game::PlayerDiggingState action{};
   uint64_t position{};
   game::Face facing{};
   int sequence_id{};
};

void deserialize(Reader &r, PlayerDigging &msg);

struct HeldItemChange
{
   short slot;
};

void deserialize(Reader &r, HeldItemChange &msg);

enum class PlayerHand : uint8_t
{
   Main,
   Off
};

// 0x2c
struct AnimateHandClient
{
   PlayerHand hand;
};

void deserialize(Reader &r, AnimateHandClient &msg);

// 0x2e
struct PlayerBlockPlacement
{
   PlayerHand hand{};
   uint64_t position{};
   game::Face facing{};
   float x, y, z;
   bool inside_block;
   int sequence_id;
};

void deserialize(Reader &r, PlayerBlockPlacement &msg);


}// namespace minecpp::network::message
