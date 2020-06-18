#include "clientbound.h"
#include "chunk.h"

namespace MineNet::Message {

Writer serialize(SpawnObject msg) {
   Writer w;
   w.write_byte(0x00);
   w.write_varint(msg.entity_id);
   w.write_uuid_str(msg.unique_id);
   w.write_varint(msg.entity_type);
   w.write_double(msg.x);
   w.write_double(msg.y);
   w.write_double(msg.z);
   w.write_byte(msg.pitch);
   w.write_byte(msg.yaw);
   w.write_big_endian(msg.data);
   w.write_big_endian(msg.vel_x);
   w.write_big_endian(msg.vel_y);
   w.write_big_endian(msg.vel_z);
   return w;
}

Writer serialize(SpawnExperienceOrb msg) {
   Writer w;
   w.write_byte(0x01);
   w.write_varint(msg.entity_id);
   w.write_double(msg.x);
   w.write_double(msg.y);
   w.write_double(msg.z);
   w.write_big_endian(msg.xp_value);
   return w;
}

Writer Message::serialize(SpawnPlayer msg) {
   Writer w;
   w.write_byte(0x05);
   w.write_varint(msg.entity_id);
   w.write_uuid(msg.id);
   w.write_double(msg.x);
   w.write_double(msg.y);
   w.write_double(msg.z);
   w.write_byte(msg.yaw / 360.0f * 256.0f);
   w.write_byte(msg.pitch / 360.0f * 256.0f);
   return w;
}

Writer serialize(Difficulty msg) {
   Writer w;
   w.write_byte(0x0e);
   w.write_byte(msg.difficulty);
   w.write_byte(msg.locked);
   return w;
}

Writer serialize(Chat msg) {
   Writer w;
   w.write_byte(0x0f);
   w.write_string(msg.message);
   w.write_byte(static_cast<uint8_t>(msg.type));
   return w;
}

Writer serialize(EntityStatus msg) {
   Writer w;
   w.write_byte(0x1c);
   w.write_big_endian(msg.entity_id);
   w.write_byte(msg.opcode);
   return w;
}

Writer serialize(ChunkData msg) {
   Writer w;
   w.write_byte(0x22);
   write_chunk(w, msg.chunk);
   return w;
}

Writer serialize(UpdateLight msg) {
   Writer w;
   w.write_byte(0x25);
   write_light(w, msg.chunk);
   return w;
}

Writer serialize(ServerBrand msg) {
   Writer w;
   w.write_byte(0x19);
   w.write_string("minecraft:brand");
   w.write_string(msg.brand);
   return w;
}

Writer serialize(Disconnect msg) {
   Writer w;
   w.write_byte(0x1b);
   w.write_string(msg.reason);
   return w;
}

Writer serialize(JoinGame msg) {
   Writer w;
   w.write_byte(0x26);
   w.write_big_endian(msg.player_id);
   w.write_byte(msg.game_mode);
   w.write_big_endian(msg.dimension);
   w.write_big_endian(msg.seed);
   w.write_byte(msg.max_players);
   w.write_string(msg.world_type);
   w.write_varint(msg.view_distance);
   w.write_byte(msg.reduced_debug_info);
   w.write_byte(msg.immediate_respawn);
   return w;
}

Writer Message::serialize(EntityRelativeMove msg) {
   Writer w;
   w.write_byte(0x29);
   w.write_varint(msg.entity_id);
   w.write_big_endian<short>(msg.x);
   w.write_big_endian<short>(msg.y);
   w.write_big_endian<short>(msg.z);
   w.write_byte(msg.on_ground);
   return w;
}

Writer Message::serialize(EntityMove msg) {
   Writer w;
   w.write_byte(0x2a);
   w.write_varint(msg.entity_id);
   w.write_big_endian<short>(msg.x);
   w.write_big_endian<short>(msg.y);
   w.write_big_endian<short>(msg.z);
   w.write_byte(msg.yaw * 256.0f / 360.0f);
   w.write_byte(msg.pitch * 256.0f / 360.0f);
   w.write_byte(msg.on_ground);
   return w;
}

Writer Message::serialize(EntityLook msg) {
   Writer w;
   w.write_byte(0x2b);
   w.write_varint(msg.entity_id);
   w.write_byte(msg.yaw * 256.0f / 360.0f);
   w.write_byte(msg.pitch * 256.0f / 360.0f);
   w.write_byte(msg.on_ground);
   return w;
}

Writer serialize(AddPlayer msg) {
   Writer w;
   w.write_byte(0x34);
   w.write_byte(0x00);
   w.write_varint(1);
   w.write_uuid(msg.id);
   w.write_string(msg.name);

   w.write_varint(msg.properties.size());
   for (const auto &pair : msg.properties) {
      w.write_string(pair.first);
      w.write_string(pair.second);
      w.write_byte(0x00); // TODO: Add signature
   }

   w.write_byte(msg.game_mode);
   w.write_varint(msg.ping);
   w.write_byte(0x00); // TODO: Support name aliases

   return w;
}

Writer serialize(PlayerPositionLook msg) {
   Writer w;
   w.write_byte(0x36);
   w.write_double(msg.x);
   w.write_double(msg.y);
   w.write_double(msg.z);
   w.write_float(msg.yaw);
   w.write_float(msg.pitch);
   w.write_byte(msg.flags);
   w.write_varint(msg.tp_id);
   return w;
}

Writer serialize(RecipeBook msg) {
   Writer w;
   w.write_byte(0x37);
   w.write_byte(static_cast<uint8_t>(msg.state));
   w.write_byte(msg.gui_open);
   w.write_byte(msg.filtering_craftable);
   w.write_byte(msg.furnace_gui_open);
   w.write_byte(msg.furnace_filtering_craftable);
   w.write_byte(0x00); // TODO: Support custom recipes
   w.write_byte(0x00);
   return w;
}

Writer Message::serialize(EntityHeadLook msg) {
   Writer w;
   w.write_byte(0x3c);
   w.write_varint(msg.entity_id);
   w.write_byte(msg.yaw * 256.0f / 360.0f);
   return w;
}

Writer serialize(PlayerAbilities msg) {
   Writer w;
   w.write_byte(0x32);
   w.write_byte(msg.flags);
   w.write_float(msg.fly_speed);
   w.write_float(msg.walk_speed);
   return w;
}

Writer serialize(HeldItem msg) {
   Writer w;
   w.write_byte(0x40);
   w.write_byte(msg.item);
   return w;
}

Writer serialize(Raw msg) {
   Writer w;
   w.write_bytes(msg.data, msg.size);
   return w;
}

Writer serialize(UpdateChunkPosition msg) {
   Writer w;
   w.write_byte(0x41);
   w.write_varint(msg.x);
   w.write_varint(msg.z);
   return w;
}

} // namespace MineNet::Message
