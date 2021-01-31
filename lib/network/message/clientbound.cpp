#include <mb/int.h>
#include <minecpp/network/message/chunk.h>
#include <minecpp/network/message/clientbound.h>

namespace minecpp::network::message {

Writer serialize(SpawnObject msg) {
   // 1.16.5 ok
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
   // 1.16.5 ok
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
   // 1.16.5 ok
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
   // 1.16.5 ok
   Writer w;
   w.write_byte(0x05);
   w.write_varint(msg.entity_id);
   w.write_byte(msg.type);
   return w;
}

Writer serialize(BlockChange msg) {
   // 1.16.5 ok
   Writer w;
   w.write_byte(0x0b);
   w.write_big_endian(msg.block_position);
   w.write_varint(msg.block_id);
   return w;
}

Writer serialize(Difficulty msg) {
   // 1.16.5 ok
   Writer w;
   w.write_byte(0x0d);
   w.write_byte(msg.difficulty);
   w.write_byte(msg.locked);
   return w;
}

Writer serialize(Chat msg) {
   // 1.16.5 ok
   Writer w;
   w.write_byte(0x0e);
   w.write_string(msg.message);
   w.write_byte(static_cast<uint8_t>(msg.type));
   w.write_uuid(msg.user_id);
   return w;
}

Writer serialize(ServerBrand msg) {
   // 1.16.5 ok
   Writer w;
   w.write_byte(0x17);
   w.write_string("minecraft:brand");
   w.write_string(msg.brand);
   return w;
}

Writer serialize(Disconnect msg) {
   // 1.16.5 ok
   Writer w;
   w.write_byte(0x19);
   w.write_string(msg.reason);
   return w;
}

Writer serialize(EntityStatus msg) {
   // 1.16.5 ok
   Writer w;
   w.write_byte(0x1a);
   w.write_big_endian(msg.entity_id);
   w.write_byte(msg.opcode);
   return w;
}

Writer serialize(UnloadChunk msg) {
   // 1.16.5 ok
   Writer w;
   w.write_byte(0x1c);
   w.write_big_endian(msg.chunk_x);
   w.write_big_endian(msg.chunk_z);
   return w;
}

Writer serialize(KeepAlive msg) {
   // 1.16.5 ok
   Writer w;
   w.write_byte(0x1f);
   w.write_big_endian(msg.time);
   return w;
}

Writer serialize(ChunkData msg) {
   // 1.16.5 ok
   Writer w;
   w.write_byte(0x20);
   write_chunk(w, msg.chunk);
   return w;
}

Writer serialize(UpdateLight msg) {
   // 1.16.5 ok
   Writer w;
   w.write_byte(0x23);
   write_light(w, msg.chunk);
   return w;
}

Writer serialize(JoinGame msg) {
   // 1.16.5 ok
   Writer w;
   w.write_byte(0x24);
   w.write_big_endian(msg.player_id);
   w.write_byte(msg.is_hardcore);
   w.write_byte(msg.game_mode);
   w.write_byte(msg.previous_game_mode);

   w.write_varint(msg.available_dimensions.size());
   for (const auto &d : msg.available_dimensions) {
      w.write_string(d);
   }

   w.write_bytes(msg.dimension_codec.data(), msg.dimension_codec.size());
   w.write_bytes(msg.dimension_type.data(), msg.dimension_type.size());
   w.write_string(msg.world_name);
   w.write_big_endian(msg.seed);
   w.write_byte(msg.max_players);
   w.write_varint(msg.view_distance);
   w.write_byte(msg.reduced_debug_info);
   w.write_byte(!msg.immediate_respawn);
   w.write_byte(0);// is debug
   w.write_byte(0);// is flat
   return w;
}

Writer serialize(EntityRelativeMove msg) {
   // 1.16.5 ok
   Writer w;
   w.write_byte(0x27);
   w.write_varint(msg.entity_id);
   w.write_big_endian<short>(msg.x);
   w.write_big_endian<short>(msg.y);
   w.write_big_endian<short>(msg.z);
   w.write_byte(msg.on_ground);
   return w;
}

Writer serialize(EntityMove msg) {
   // 1.16.5 ok
   Writer w;
   w.write_byte(0x28);
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
   // 1.16.5 ok
   Writer w;
   w.write_byte(0x29);
   w.write_varint(msg.entity_id);
   w.write_byte(msg.yaw * 256.0f / 360.0f);
   w.write_byte(msg.pitch * 256.0f / 360.0f);
   w.write_byte(msg.on_ground);
   return w;
}

Writer serialize(PlayerAbilities msg) {
   // 1.16.5 ok
   Writer w;
   w.write_byte(0x30);
   w.write_byte(msg.flags);
   w.write_float(msg.fly_speed);
   w.write_float(msg.walk_speed);
   return w;
}

Writer serialize(AddPlayer msg) {
   // 1.16.5 ok
   Writer w;
   w.write_byte(0x32);
   w.write_byte(0x00);
   w.write_varint(1);
   w.write_uuid(msg.id);
   w.write_string(msg.name);

   w.write_varint(msg.properties.size());
   for (const auto &pair : msg.properties) {
      w.write_string(pair.first);
      w.write_string(pair.second);
      w.write_byte(0x00);// TODO: Add signature
   }

   w.write_byte(msg.game_mode);
   w.write_varint(msg.ping);
   w.write_byte(0x00);// TODO: Support name aliases

   return w;
}

Writer serialize(RemovePlayer msg) {
   // 1.16.5 ok
   Writer w;
   w.write_byte(0x32);
   w.write_byte(0x04);
   w.write_varint(1);
   w.write_uuid(msg.id);
   return w;
}

Writer serialize(PlayerPositionLook msg) {
   // 1.16.5 ok
   Writer w;
   w.write_byte(0x34);
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
   // 1.16.5 ok kina
   Writer w;
   w.write_byte(0x35);
   w.write_byte(static_cast<uint8_t>(msg.state));
   w.write_byte(msg.gui_open);
   w.write_byte(msg.filtering_craftable);
   w.write_byte(msg.furnace_gui_open);
   w.write_byte(msg.furnace_filtering_craftable);
   w.write_byte(msg.furnace_gui_open);// blast
   w.write_byte(msg.furnace_filtering_craftable);
   w.write_byte(msg.furnace_gui_open);// smoker
   w.write_byte(msg.furnace_filtering_craftable);
   w.write_byte(0x00);// TODO: Support custom recipes
   w.write_byte(0x00);
   return w;
}

Writer serialize(DestroyEntity msg) {
   // 1.16.5 ok
   Writer w;
   w.write_byte(0x36);
   w.write_varint(1);
   w.write_varint(msg.entity_id);
   return w;
}

Writer serialize(EntityHeadLook msg) {
   // 1.16.5 ok
   Writer w;
   w.write_byte(0x3a);
   w.write_varint(msg.entity_id);
   w.write_byte(msg.yaw * 256.0f / 360.0f);
   return w;
}

Writer serialize(MultiBlockChange msg) {
   // 1.16.5 ok
   Writer w;
   w.write_byte(0x3b);
   w.write_big_endian(msg.chunk_position);
   w.write_byte(msg.distrust_edges);
   w.write_varint(msg.block_changes.size());
   for (const auto &change : msg.block_changes) {
      w.write_varlong(change);
   }
   return w;
}

Writer serialize(HeldItem msg) {
   // 1.16.5 ok
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
   // 1.16.5 ok
   Writer w;
   w.write_byte(0x40);
   w.write_varint(msg.x);
   w.write_varint(msg.z);
   return w;
}

}// namespace minecpp::network::message
