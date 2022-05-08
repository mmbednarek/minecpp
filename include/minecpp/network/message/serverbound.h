#pragma once
#include "file.h"
#include <minecpp/game/direction.h>
#include <minecpp/game/hand.h>
#include <minecpp/network/chat.h>
#include <string>

namespace minecpp::network::message {

// 0x03

struct ChatMessage {
   std::string message;
};
void deserialize(Reader &r, ChatMessage &msg);

// 0x05
struct ClientSettings {
   std::string lang;
   uint8_t view;
   ChatVisibility visibility;
   bool enable_colors;
   uint8_t model_part_flags;
   game::HandSide hand_side;
   bool enable_text_filtering;
   bool allow_server_listing;
};
void deserialize(Reader &r, ClientSettings &msg);

// 0x0f
struct KeepAliveClient {
   uint64_t time;
};
void deserialize(Reader &r, KeepAliveClient &msg);

// 0x11
struct PlayerPosition {
   double x, y, z;
   bool on_ground;
};
void deserialize(Reader &r, PlayerPosition &msg);

// 0x12
struct PlayerPositionRotation {
   double x, y, z;
   float yaw, pitch;
   bool on_ground;
};
void deserialize(Reader &r, PlayerPositionRotation &msg);

// 0x13
struct PlayerRotation {
   float yaw, pitch;
    bool on_ground;
};
void deserialize(Reader &r, PlayerRotation &msg);

// 0x1a
struct PlayerDigging {
   game::PlayerDiggingState action{};
   uint64_t position{};
   game::Face facing{};
};
void deserialize(Reader &r, PlayerDigging &msg);

enum class PlayerHand : uint8_t {
   Main,
   Off
};

// 0x2c
struct AnimateHandClient {
   PlayerHand hand;
};
void deserialize(Reader &r, AnimateHandClient &msg);

// 0x2e
struct PlayerBlockPlacement {
   PlayerHand hand{};
   uint64_t position{};
   game::Face facing{};
   float x, y, z;
   bool inside_block;
};
void deserialize(Reader &r, PlayerBlockPlacement &msg);


}// namespace minecpp::network::message
