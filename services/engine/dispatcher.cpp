#include "dispatcher.h"
#include <minecpp/util/uuid.h>
#include <minepb/events.pb.h>

namespace Engine {

Dispatcher::Dispatcher(EventManager &events) : events(events) {}

void Dispatcher::load_terrain(boost::uuids::uuid player, minecpp::game::block::ChunkPos central_chunk,
                              std::vector<minecpp::game::block::ChunkPos> coords) {
   minecpp::events::LoadTerrain event;
   event.set_uuid(player.data, player.size());
   event.mutable_central_chunk()->set_x(central_chunk.x);
   event.mutable_central_chunk()->set_z(central_chunk.z);
   for (const auto &c : coords) {
      auto new_coord = event.add_coords();
      new_coord->set_x(c.x);
      new_coord->set_z(c.z);
   }
   events.post(event);
}

void Dispatcher::transfer_player(boost::uuids::uuid player, boost::uuids::uuid target_engine) {
   minecpp::events::TransferPlayer event;
   event.set_player(player.data, player.size());
   event.set_target_engine(target_engine.data, target_engine.size());
   events.post(event);
}

void Dispatcher::entity_move(int eid, uuid id, minecpp::game::entity::Movement movement, float yaw, float pitch) {
   minecpp::events::EntityMove event;
   event.set_id(eid);
   event.set_uuid(id.data, id.size());
   event.set_x(movement.x);
   event.set_y(movement.y);
   event.set_z(movement.z);
   event.set_yaw(yaw);
   event.set_pitch(pitch);
   events.post(event);
}

void Dispatcher::add_player(uuid player, const std::string &name, mb::u32 ping) {
   minecpp::events::AddPlayer add_player;
   add_player.set_uuid(player.data, player.size());
   add_player.set_name(name);
   add_player.set_ping(ping);
   events.post(add_player);
}

void Dispatcher::spawn_player(uuid player, mb::u32 entity_id, minecpp::util::Vec3 position, mb::f32 yaw, mb::f32 pitch) {
   minecpp::events::SpawnPlayer spawn_player;
   spawn_player.set_uuid(player.data, player.size());
   spawn_player.set_id(entity_id);
   spawn_player.set_x(position.x);
   spawn_player.set_y(position.y);
   spawn_player.set_z(position.z);
   spawn_player.set_yaw(yaw);
   spawn_player.set_pitch(pitch);
   events.post(spawn_player);
}

void Dispatcher::send_chat(mb::i32 msg_type, const std::string &msg) {
   minecpp::events::Chat chat;
   chat.set_type(msg_type);
   chat.set_message(msg);
   events.post(chat);
}

void Dispatcher::entity_look(uuid player, mb::u32 entity_id, mb::f32 yaw, mb::f32 pitch) {
   minecpp::events::EntityLook event;
   event.set_uuid(minecpp::util::uuid_to_string(player));
   event.set_id(entity_id);
   event.set_yaw(yaw);
   event.set_pitch(pitch);
   events.post(event);
}

void Dispatcher::remove_player(uuid player, mb::u32 entity_id) {
   minecpp::events::RemovePlayer remove_player;
   remove_player.set_uuid(minecpp::util::uuid_to_string(player));
   remove_player.set_entity_id(entity_id);
   events.post(remove_player);
}

void Dispatcher::update_block(minecpp::game::block::Position block, mb::u32 state) {
   minecpp::events::UpdateBlock update_block;
   update_block.set_block_position(block.as_long());
   update_block.set_state(0);
   events.post(update_block);
}

void Dispatcher::update_block(mb::i32 x, mb::i32 y, mb::i32 z, mb::u32 state) {
   minecpp::events::UpdateBlock update_block;
   update_block.set_block_position(minecpp::game::block::Position(x, y, z).as_long());
   update_block.set_state(0);
   events.post(update_block);
}

void Dispatcher::animate_hand(uuid player, mb::u32 entity_id, mb::u32 hand) {
   minecpp::events::AnimateHand animate;
   animate.set_uuid(minecpp::util::uuid_to_string(player));
   animate.set_entity_id(entity_id);
   animate.set_hand(hand);
   events.post(animate);
}

void Dispatcher::unload_chunk(uuid player, mb::i32 x, mb::i32 z) {
   minecpp::events::UnloadChunk unload;
   unload.set_uuid(minecpp::util::uuid_to_string(player));
   unload.set_x(x);
   unload.set_z(z);
   events.post(unload);
}

}// namespace Engine
