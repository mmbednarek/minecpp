#include "../packet/writer.h"
#include "play_client.h"

namespace Front::Protocol {

PlayClient::PlayClient(Connection &c) : conn(c) {}

void PlayClient::spawn_object(Message::SpawnObject msg) {
   Packet::Writer w(conn);
   w.write_big_endian<uint16_t>(0x00);

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

   w.send();
}

void PlayClient::spawn_experience_orb(Message::SpawnExperienceOrb msg) {
   Packet::Writer w(conn);
   w.write_big_endian<uint16_t>(0x01);

   w.write_varint(msg.entity_id);
   w.write_double(msg.x);
   w.write_double(msg.y);
   w.write_double(msg.z);
   w.write_big_endian(msg.xp_value);

   w.send();
}

void PlayClient::join_game(Message::JoinGame msg) {
   Packet::Writer w(conn);
   w.write_big_endian<uint16_t>(0x26);

   w.write_big_endian(msg.player_id);
   w.write_byte(msg.game_mode);
   w.write_big_endian(msg.dimension);
   w.write_big_endian(msg.seed);
   w.write_byte(msg.max_players);
   w.write_string(msg.world_type);
   w.write_varint(msg.view_distance);
   w.write_byte(msg.reduced_debug_info);
   w.write_byte(msg.immediate_respawn);

   w.send();
}

}
