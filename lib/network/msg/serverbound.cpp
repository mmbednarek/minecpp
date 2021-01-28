#include <minecpp/network/msg/serverbound.h>

namespace MineNet::Message {

void deserialize(Reader &r, ChatMessage &msg) {
   msg.message = r.read_string();
}

void deserialize(Reader &r, ClientSettings &msg) {
   msg.lang = r.read_string();
   msg.view = r.read_byte();
   msg.visibility = static_cast<ChatVisibility>(r.read_byte());
   msg.enable_colors = r.read_byte();
   msg.model_part_flags = r.read_byte();
   msg.hand_side = static_cast<Game::HandSide>(r.read_byte());
}

void deserialize(Reader &r, KeepAliveClient &msg) {
   msg.time = r.read_big_endian<uint64_t>();
}

void deserialize(Reader &r, PlayerPosition &msg) {
   msg.x = r.read_double();
   msg.y = r.read_double();
   msg.z = r.read_double();
}

void deserialize(Reader &r, PlayerPositionRotation &msg) {
   msg.x = r.read_double();
   msg.y = r.read_double();
   msg.z = r.read_double();
   msg.yaw = r.read_float();
   msg.pitch = r.read_float();
}

void deserialize(Reader &r, PlayerRotation &msg) {
   msg.yaw = r.read_float();
   msg.pitch = r.read_float();
}

void deserialize(Reader &r, PlayerDigging &msg) {
   msg.action = static_cast<DiggingAction>(r.read_varint());
   msg.position = r.read_big_endian<uint64_t>();
   msg.facing = Game::Direction(r.read_byte());
}

void deserialize(Reader &r, AnimateHandClient &msg) {
   msg.hand = static_cast<PlayerHand>(r.read_varint());
}

} // namespace MineNet::Message
