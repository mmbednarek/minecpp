#include <mb/int.h>
#include <minecpp/network/message/chunk.h>
#include <minecpp/network/message/clientbound.h>

namespace minecpp::network::message {

Writer SpawnObject::serialize() const
{
   // 1.18.2 OK
   Writer w;
   w.write_byte(0x00);
   w.write_varint(entity_id);
   w.write_uuid(unique_id);
   w.write_varint(entity_type);
   w.write_double(x);
   w.write_double(y);
   w.write_double(z);
   w.write_byte(pitch);
   w.write_byte(yaw);
   w.write_big_endian(data);
   w.write_big_endian(vel_x);
   w.write_big_endian(vel_y);
   w.write_big_endian(vel_z);
   return w;
}

Writer SpawnExperienceOrb::serialize() const
{
   // 1.18.2 OK
   Writer w;
   w.write_byte(0x01);
   w.write_varint(entity_id);
   w.write_double(x);
   w.write_double(y);
   w.write_double(z);
   w.write_big_endian(xp_value);
   return w;
}

Writer SpawnPlayer::serialize() const
{
   // 1.18.2 OK
   Writer w;
   w.write_byte(0x04);
   w.write_varint(entity_id);
   w.write_uuid(id);
   w.write_double(x);
   w.write_double(y);
   w.write_double(z);
   w.write_byte(yaw / 360.0f * 256.0f);
   w.write_byte(pitch / 360.0f * 256.0f);
   return w;
}

Writer AcknowledgePlayerDigging::serialize() const
{
   // 1.18.2 ok
   Writer w;
   w.write_byte(0x08);
   w.write_long(position);
   w.write_varint(block);
   w.write_varint(static_cast<int>(state));
   w.write_byte(successful);
   return w;
}

Writer AnimateHand::serialize() const
{
   // 1.18.2 OK
   Writer w;
   w.write_byte(0x06);
   w.write_varint(entity_id);
   w.write_byte(type);
   return w;
}

Writer BlockChange::serialize() const
{
   // 1.18.2 ok
   Writer w;
   w.write_byte(0x0c);
   w.write_big_endian(block_position);
   w.write_varint(block_id);
   return w;
}

Writer Difficulty::serialize() const
{
   // 1.18.2 ok
   Writer w;
   w.write_byte(0x0e);
   w.write_byte(difficulty);
   w.write_byte(locked);
   return w;
}

Writer Chat::serialize() const
{
   // 1.18.2 ok
   Writer w;
   w.write_byte(0x0f);
   w.write_string(message);
   w.write_byte(static_cast<uint8_t>(type));
   w.write_uuid(user_id);
   return w;
}

Writer ServerBrand::serialize() const
{
   // 1.18.2 ok
   Writer w;
   w.write_byte(0x18);
   w.write_string("minecraft:brand");
   w.write_string(brand);
   return w;
}

Writer Disconnect::serialize() const
{
   // 1.18.2 ok
   Writer w;
   w.write_byte(0x1a);
   w.write_string(reason);
   return w;
}

Writer EntityStatus::serialize() const
{
   // 1.18.2 ok
   Writer w;
   w.write_byte(0x1b);
   w.write_big_endian(entity_id);
   w.write_byte(opcode);
   return w;
}

Writer UnloadChunk::serialize() const
{
   // 1.18.2 ok
   Writer w;
   w.write_byte(0x1d);
   w.write_big_endian(chunk_x);
   w.write_big_endian(chunk_z);
   return w;
}

Writer KeepAlive::serialize() const
{
   // 1.18.2 ok
   Writer w;
   w.write_byte(0x21);
   w.write_big_endian(time);
   return w;
}

Writer ChunkData::serialize() const
{
   // 1.18.2 ok
   Writer w;
   w.write_byte(0x22);
   write_chunk(w, chunk);
   return w;
}

Writer UpdateLight::serialize() const
{
   // 1.18.2 ok
   Writer w;
   w.write_byte(0x25);
   write_light(w, chunk);
   return w;
}

Writer JoinGame::serialize() const
{
   // 1.18.2 OK
   Writer w;
   w.write_byte(0x26);
   w.write_big_endian(player_id);
   w.write_byte(is_hardcore);
   w.write_byte(game_mode);
   w.write_byte(previous_game_mode);

   w.write_varint(available_dimensions.size());
   for (const auto &d : available_dimensions) { w.write_string(d); }

   w.write_bytes(dimension_codec.data(), dimension_codec.size());
   w.write_bytes(dimension_type.data(), dimension_type.size());
   w.write_string(world_name);
   w.write_big_endian(seed);
   w.write_byte(max_players);
   w.write_varint(view_distance);
   w.write_varint(simulation_distance);
   w.write_byte(reduced_debug_info);
   w.write_byte(!immediate_respawn);
   w.write_byte(0);// is debug
   w.write_byte(0);// is flat
   return w;
}

Writer EntityRelativeMove::serialize() const
{
   // 1.18.2 ok
   Writer w;
   w.write_byte(0x29);
   w.write_varint(entity_id);
   w.write_big_endian<short>(x);
   w.write_big_endian<short>(y);
   w.write_big_endian<short>(z);
   w.write_byte(on_ground);
   return w;
}

Writer EntityMove::serialize() const
{
   // 1.18.2 ok
   Writer w;
   w.write_byte(0x2a);
   w.write_varint(entity_id);
   w.write_big_endian<short>(x);
   w.write_big_endian<short>(y);
   w.write_big_endian<short>(z);
   w.write_byte(yaw * 256.0f / 360.0f);
   w.write_byte(pitch * 256.0f / 360.0f);
   w.write_byte(on_ground);
   return w;
}

Writer EntityLook::serialize() const
{
   // 1.18.2 OK
   Writer w;
   w.write_byte(0x2b);
   w.write_varint(entity_id);
   w.write_byte(yaw * 256.0f / 360.0f);
   w.write_byte(pitch * 256.0f / 360.0f);
   w.write_byte(on_ground);
   return w;
}

Writer PlayerAbilities::serialize() const
{
   // 1.18.2 ok
   Writer w;
   w.write_byte(0x32);
   w.write_byte(flags);
   w.write_float(fly_speed);
   w.write_float(walk_speed);
   return w;
}

Writer AddPlayer::serialize() const
{
   // 1.18.2 ok
   Writer w;
   w.write_byte(0x36);
   w.write_byte(0x00);
   w.write_varint(1);
   w.write_uuid(id);
   w.write_string(name);

   w.write_varint(properties.size());
   for (const auto &pair : properties) {
      w.write_string(pair.first);
      w.write_string(pair.second);
      w.write_byte(0x00);// TODO: Add signature
   }

   w.write_byte(game_mode);
   w.write_varint(ping);
   w.write_byte(0x00);// TODO: Support name aliases

   return w;
}

Writer RemovePlayer::serialize() const
{
   // 1.18.2 ok
   Writer w;
   w.write_byte(0x36);
   w.write_byte(0x04);
   w.write_varint(1);
   w.write_uuid(id);
   return w;
}

Writer PlayerPositionLook::serialize() const
{
   // 1.18.2 ok
   Writer w;
   w.write_byte(0x38);
   w.write_double(x);
   w.write_double(y);
   w.write_double(z);
   w.write_float(yaw);
   w.write_float(pitch);
   w.write_byte(flags);
   w.write_varint(tp_id);
   w.write_byte(dismount_vehicle);
   return w;
}

Writer RecipeBook::serialize() const
{
   // 1.18.2 ok kina
   Writer w;
   w.write_byte(0x39);
   w.write_byte(static_cast<uint8_t>(state));
   w.write_byte(gui_open);
   w.write_byte(filtering_craftable);
   w.write_byte(furnace_gui_open);
   w.write_byte(furnace_filtering_craftable);
   w.write_byte(furnace_gui_open);// blast
   w.write_byte(furnace_filtering_craftable);
   w.write_byte(furnace_gui_open);// smoker
   w.write_byte(furnace_filtering_craftable);
   w.write_byte(0x00);// TODO: Support custom recipes
   if (state == 0)
      w.write_byte(0x00);
   return w;
}

Writer DestroyEntity::serialize() const
{
   // 1.18.2 ok
   Writer w;
   w.write_byte(0x3a);
   w.write_varint(1);
   w.write_varint(entity_id);
   return w;
}

Writer EntityHeadLook::serialize() const
{
   // 1.18,2 ok
   Writer w;
   w.write_byte(0x3e);
   w.write_varint(entity_id);
   w.write_byte(yaw * 256.0f / 360.0f);
   return w;
}

Writer MultiBlockChange::serialize() const
{
   // 1.18.2 ok
   Writer w;
   w.write_byte(0x3f);
   w.write_big_endian(chunk_position);
   w.write_byte(distrust_edges);
   w.write_varint(block_changes.size());
   for (const auto &change : block_changes) { w.write_varlong(change); }
   return w;
}

Writer HeldItem::serialize() const
{
   // 1.18.2 ok
   Writer w;
   w.write_byte(0x48);
   w.write_byte(item);
   return w;
}

Writer Raw::serialize() const
{
   Writer w;
   w.write_bytes(data, size);
   return w;
}

Writer UpdateChunkPosition::serialize() const
{
   // 1.18.2 ok
   Writer w;
   w.write_byte(0x49);
   w.write_varint(x);
   w.write_varint(z);
   return w;
}
}// namespace minecpp::network::message
