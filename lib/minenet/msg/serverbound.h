#pragma once
#include "../chat.h"
#include "reader.h"
#include <game/direction.h>
#include <game/hand.h>
#include <string>

namespace MineNet::Message {

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
   Game::HandSide hand_side;
};
void deserialize(Reader &r, ClientSettings &msg);

// 0x11
struct PlayerPosition {
   double x, y, z;
};
void deserialize(Reader &r, PlayerPosition &msg);

// 0x12
struct PlayerPositionRotation {
   double x, y, z;
   float yaw, pitch;
};
void deserialize(Reader &r, PlayerPositionRotation &msg);

// 0x13
struct PlayerRotation {
   float yaw, pitch;
};
void deserialize(Reader &r, PlayerRotation &msg);

enum class DiggingAction : uint8_t {
   StartDestroyBlock,
   AbortDestroyBlock,
   StopDestroyBlock,
   DropAllItems,
   DropItem,
   ReleaseUseItem,
   SwapHeldItems,
};

// 0x1a
struct PlayerDigging {
   DiggingAction action;
   uint64_t position;
   Game::Direction facing;
};
void deserialize(Reader &r, PlayerDigging &msg);

} // namespace MineNet::Message
