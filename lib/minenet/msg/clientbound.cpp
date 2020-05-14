#include "clientbound.h"

namespace MineNet::Message {

Writer serialize(SpawnObject msg) {
   Writer w;
   w.write_byte(0x00);
   w.write_varint(msg.entity_id);
   w.write_uuid(msg.unique_id);
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

Writer serialize(Difficulty msg) {
   Writer w;
   w.write_byte(0x0e);
   w.write_byte(msg.difficulty);
   w.write_byte(msg.locked);
   return w;
}

Writer serialize(ServerBrand msg) {
   Writer w;
   w.write_byte(0x19);
   w.write_string("brand");
   w.write_string(msg.brand);
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

}
