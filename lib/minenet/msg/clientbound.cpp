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

Writer serialize(SpawnPlayer msg) {
   Writer w;
   w.write_byte(0x04);
   w.write_varint(msg.entity_id);
   w.write_uuid(msg.id);
   w.write_double(msg.x);
   w.write_double(msg.y);
   w.write_double(msg.z);
   w.write_byte(msg.yaw / 360.0f * 256.0f);
   w.write_byte(msg.pitch / 360.0f * 256.0f);
   return w;
}

Writer serialize(AnimateHand msg) {
   Writer w;
   w.write_byte(0x05);
   w.write_varint(msg.entity_id);
   w.write_byte(msg.type);
   return w;
}

Writer serialize(MultiBlockChange msg) {
   Writer w;
   w.write_byte(0x0f);
   w.write_big_endian(msg.chunk_x);
   w.write_big_endian(msg.chunk_z);
   w.write_varint(msg.changes.size());

   for (const auto &change : msg.changes) {
      w.write_big_endian(change.offset);
      w.write_varint(change.state);
   }
   return w;
}

Writer serialize(Difficulty msg) {
   Writer w;
   w.write_byte(0x0d);
   w.write_byte(msg.difficulty);
   w.write_byte(msg.locked);
   return w;
}

Writer serialize(Chat msg) {
   Writer w;
   w.write_byte(0x0e);
   w.write_string(msg.message);
   w.write_byte(static_cast<uint8_t>(msg.type));
   w.write_uuid(msg.user_id);
   return w;
}

Writer serialize(EntityStatus msg) {
   Writer w;
   w.write_byte(0x1b);
   w.write_big_endian(msg.entity_id);
   w.write_byte(msg.opcode);
   return w;
}

Writer serialize(KeepAlive msg) {
   Writer w;
   w.write_byte(0x20);
   w.write_big_endian(msg.time);
   return w;
}

Writer serialize(ChunkData msg) {
   Writer w;
   w.write_byte(0x21);
   write_chunk(w, msg.chunk);
   return w;
}

Writer serialize(UpdateLight msg) {
   Writer w;
   w.write_byte(0x24);
   write_light(w, msg.chunk);
   return w;
}

Writer serialize(ServerBrand msg) {
   Writer w;
   w.write_byte(0x18);
   w.write_string("minecraft:brand");
   w.write_string(msg.brand);
   return w;
}

Writer serialize(Disconnect msg) {
   Writer w;
   w.write_byte(0x1a);
   w.write_string(msg.reason);
   return w;
}

Writer serialize(JoinGame msg) {
   Writer w;
   w.write_byte(0x25);
   w.write_big_endian(msg.player_id);
   w.write_byte(msg.game_mode);
   w.write_byte(msg.player_game_mode);

   w.write_varint(msg.available_dimensions.size());
   for (const auto &d : msg.available_dimensions) {
      w.write_string(d);
   }
   w.write_bytes(msg.dimension_props.data(), msg.dimension_props.size());
   w.write_string(msg.dimension_type);
   w.write_string(msg.dimension);
   w.write_big_endian(msg.seed);
   w.write_byte(msg.max_players);
   w.write_varint(msg.view_distance);
   w.write_byte(msg.reduced_debug_info);
   w.write_byte(!msg.immediate_respawn);
   w.write_byte(0); // not sure what's that for
   w.write_byte(0);
   return w;
}

Writer serialize(EntityRelativeMove msg) {
   Writer w;
   w.write_byte(0x28);
   w.write_varint(msg.entity_id);
   w.write_big_endian<short>(msg.x);
   w.write_big_endian<short>(msg.y);
   w.write_big_endian<short>(msg.z);
   w.write_byte(msg.on_ground);
   return w;
}

Writer serialize(EntityMove msg) {
   Writer w;
   w.write_byte(0x29);
   w.write_varint(msg.entity_id);
   w.write_big_endian<short>(msg.x);
   w.write_big_endian<short>(msg.y);
   w.write_big_endian<short>(msg.z);
   w.write_byte(msg.yaw * 256.0f / 360.0f);
   w.write_byte(msg.pitch * 256.0f / 360.0f);
   w.write_byte(msg.on_ground);
   return w;
}

Writer serialize(EntityLook msg) {
   Writer w;
   w.write_byte(0x2a);
   w.write_varint(msg.entity_id);
   w.write_byte(msg.yaw * 256.0f / 360.0f);
   w.write_byte(msg.pitch * 256.0f / 360.0f);
   w.write_byte(msg.on_ground);
   return w;
}

Writer serialize(AddPlayer msg) {
   Writer w;
   w.write_byte(0x33);
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

Writer serialize(RemovePlayer msg) {
   Writer w;
   w.write_byte(0x33);
   w.write_byte(0x04);
   w.write_varint(1);
   w.write_uuid(msg.id);
   return w;
}

Writer serialize(PlayerPositionLook msg) {
   Writer w;
   w.write_byte(0x35);
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
   w.write_byte(0x36);
   w.write_byte(static_cast<uint8_t>(msg.state));
   w.write_byte(msg.gui_open);
   w.write_byte(msg.filtering_craftable);
   w.write_byte(msg.furnace_gui_open);
   w.write_byte(msg.furnace_filtering_craftable);
   w.write_byte(0x00); // TODO: Support custom recipes
   w.write_byte(0x00);
   return w;
}

Writer serialize(DestroyEntity msg) {
   Writer w;
   w.write_byte(0x37);
   w.write_varint(1);
   w.write_varint(msg.entity_id);
   return w;
}

Writer serialize(EntityHeadLook msg) {
   Writer w;
   w.write_byte(0x3b);
   w.write_varint(msg.entity_id);
   w.write_byte(msg.yaw * 256.0f / 360.0f);
   return w;
}

Writer serialize(PlayerAbilities msg) {
   Writer w;
   w.write_byte(0x31);
   w.write_byte(msg.flags);
   w.write_float(msg.fly_speed);
   w.write_float(msg.walk_speed);
   return w;
}

Writer serialize(HeldItem msg) {
   Writer w;
   w.write_byte(0x3f);
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
   w.write_byte(0x40);
   w.write_varint(msg.x);
   w.write_varint(msg.z);
   return w;
}

} // namespace MineNet::Message
