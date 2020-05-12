#include "../connection.h"
#include "play_client.h"
#include "../../common/packet/writer.h"

namespace Front::Protocol {

PlayClient::PlayClient(Connection &c) : conn(c) {}

void PlayClient::spawn_object(Message::SpawnObject msg) {
   Packet::Writer w;
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

   conn.send(w);
}

void PlayClient::spawn_experience_orb(Message::SpawnExperienceOrb msg) {
   Packet::Writer w;
   w.write_big_endian<uint16_t>(0x01);

   w.write_varint(msg.entity_id);
   w.write_double(msg.x);
   w.write_double(msg.y);
   w.write_double(msg.z);
   w.write_big_endian(msg.xp_value);

   conn.send(w);
}

void PlayClient::difficulty(uint8_t diff, bool locked) {
   Packet::Writer w;
   w.write_byte(diff);
   w.write_byte(locked);
   conn.send(w);
}

void PlayClient::server_brand(std::string_view brand) {
   Packet::Writer w;
   w.write_big_endian<uint16_t>(0x19);
   w.write_string("brand");
   w.write_string(brand);
   conn.send(w);
}

void PlayClient::join_game(Message::JoinGame msg) {
   Packet::Writer w;
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

   conn.send(w);
}
void PlayClient::player_abilities(Message::PlayerAbilities msg) {
   Packet::Writer w;
   w.write_big_endian<uint16_t>(0x32);

   w.write_byte(msg.flags);
   w.write_float(msg.fly_speed);
   w.write_float(msg.walk_speed);

   conn.send(w);
}

void PlayClient::held_item(uint8_t item) {
   Packet::Writer w;
   w.write_big_endian<uint16_t>(0x40);
   w.write_byte(item);
   conn.send(w);
}

}
