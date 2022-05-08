#include "minecpp/game/game.h"
#include <minecpp/network/message/serverbound.h>

namespace minecpp::network::message {

void deserialize(Reader &r, ChatMessage &msg) {
   //  1.18.2 OK
   msg.message = r.read_string();
}

void deserialize(Reader &r, ClientSettings &msg) {
   // 1.18.2 OK
   msg.lang = r.read_string();
   msg.view = r.read_byte();
   msg.visibility = static_cast<ChatVisibility>(r.read_byte());
   msg.enable_colors = r.read_byte();
   msg.model_part_flags = r.read_byte();
   msg.hand_side = static_cast<game::HandSide>(r.read_byte());
   msg.enable_text_filtering = r.read_byte();
   msg.allow_server_listing = r.read_byte();
}

void deserialize(Reader &r, KeepAliveClient &msg) {
   // 1.18.2 OK
   msg.time = r.read_big_endian<uint64_t>();
}

void deserialize(Reader &r, PlayerPosition &msg) {
   // 1.18.2 OK
   msg.x = r.read_double();
   msg.y = r.read_double();
   msg.z = r.read_double();
   msg.on_ground = r.read_byte();
}

void deserialize(Reader &r, PlayerPositionRotation &msg) {
   // 1.18.2 OK
   msg.x = r.read_double();
   msg.y = r.read_double();
   msg.z = r.read_double();
   msg.yaw = r.read_float();
   msg.pitch = r.read_float();
   msg.on_ground = r.read_byte();
}

void deserialize(Reader &r, PlayerRotation &msg) {
   // 1.18.2 OK
   msg.yaw = r.read_float();
   msg.pitch = r.read_float();
   msg.on_ground = r.read_byte();
}

void deserialize(Reader &r, PlayerDigging &msg) {
   // 1.18.2 OK
   msg.action = static_cast<game::PlayerDiggingState>(r.read_varint());
   msg.position = r.read_big_endian<uint64_t>();
   msg.facing = static_cast<game::Face>(r.read_byte());
}

void deserialize(Reader &r, AnimateHandClient &msg) {
   // 1.18.2 OK
   msg.hand = static_cast<PlayerHand>(r.read_varint());
}

} // namespace minecpp::network::Message
