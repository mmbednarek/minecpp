#include "dispatcher.h"
#include <minecpp/chat/chat.h>
#include <minecpp/player/player.h>
#include <minecpp/proto/event/clientbound/v1/clientbound.pb.h>
#include <minecpp/service/engine/api.h>
#include <minecpp/util/uuid.h>
#include <minepb/events.pb.h>

namespace minecpp::service::engine {

Dispatcher::Dispatcher(EventManager &events) : m_events(events) {}

void Dispatcher::load_terrain(player::Id player, minecpp::game::ChunkPosition central_chunk,
                              std::vector<minecpp::game::ChunkPosition> coords) {
   minecpp::events::LoadTerrain event;
   event.set_uuid(player.data, player.size());
   event.mutable_central_chunk()->set_x(central_chunk.x);
   event.mutable_central_chunk()->set_z(central_chunk.z);
   for (const auto &c : coords) {
      auto new_coord = event.add_coords();
      new_coord->set_x(c.x);
      new_coord->set_z(c.z);
   }
   m_events.post(event);
}

void Dispatcher::transfer_player(player::Id player, boost::uuids::uuid target_engine) {
   minecpp::events::TransferPlayer event;
   event.set_player(player.data, player.size());
   event.set_target_engine(target_engine.data, target_engine.size());
   m_events.post(event);
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
   m_events.post(event);
}

void Dispatcher::add_player(player::Id player, const std::string &name, mb::u32 ping) {
   minecpp::events::AddPlayer add_player;
   add_player.set_uuid(player.data, player.size());
   add_player.set_name(name);
   add_player.set_ping(ping);
   m_events.post(add_player);
}

void Dispatcher::spawn_player(player::Id player, mb::u32 entity_id, minecpp::util::Vec3 position, mb::f32 yaw, mb::f32 pitch) {
   minecpp::events::SpawnPlayer spawn_player;
   spawn_player.set_uuid(player.data, player.size());
   spawn_player.set_id(entity_id);
   spawn_player.set_x(position.x);
   spawn_player.set_y(position.y);
   spawn_player.set_z(position.z);
   spawn_player.set_yaw(yaw);
   spawn_player.set_pitch(pitch);
   m_events.post(spawn_player);
}

void Dispatcher::send_chat(chat::MessageType msg_type, const std::string &msg) {
   minecpp::events::Chat chat;
   chat.set_type(static_cast<google::protobuf::int32>(msg_type));
   chat.set_message(msg);
   m_events.post(chat);
}

void Dispatcher::entity_look(player::Id player, mb::u32 entity_id, mb::f32 yaw, mb::f32 pitch) {
   minecpp::events::EntityLook event;
   event.set_uuid(minecpp::util::uuid_to_string(player));
   event.set_id(entity_id);
   event.set_yaw(yaw);
   event.set_pitch(pitch);
   m_events.post(event);
}

void Dispatcher::remove_player(player::Id player, mb::u32 entity_id) {
   minecpp::events::RemovePlayer remove_player;
   remove_player.set_uuid(minecpp::util::uuid_to_string(player));
   remove_player.set_entity_id(entity_id);
   m_events.post(remove_player);
}

void Dispatcher::update_block(minecpp::game::BlockPosition block, mb::u32 state) {
   minecpp::events::UpdateBlock update_block;
   update_block.set_block_position(block.as_long());
   update_block.set_state(0);
   m_events.post(update_block);
}

void Dispatcher::update_block(mb::i32 x, mb::i32 y, mb::i32 z, mb::u32 state) {
   minecpp::events::UpdateBlock update_block;
   update_block.set_block_position(minecpp::game::BlockPosition(x, y, z).as_long());
   update_block.set_state(state);
   m_events.post(update_block);
}

void Dispatcher::animate_hand(player::Id player, mb::u32 entity_id, mb::u32 hand) {
   minecpp::events::AnimateHand animate;
   animate.set_uuid(minecpp::util::uuid_to_string(player));
   animate.set_entity_id(entity_id);
   animate.set_hand(hand);
   m_events.post(animate);
}

void Dispatcher::unload_chunk(player::Id player, mb::i32 x, mb::i32 z) {
   minecpp::events::UnloadChunk unload;
   unload.set_uuid(minecpp::util::uuid_to_string(player));
   unload.set_x(x);
   unload.set_z(z);
   m_events.post(unload);
}

void Dispatcher::accept_player(const player::Player &player, const game::entity::Entity &entity) {
   minecpp::proto::event::clientbound::v1::AcceptPlayer accept_player;
   *accept_player.mutable_player() = player.to_proto(entity);
   accept_player.set_challenge_id(0);

   accept_player.set_state(proto::event::clientbound::v1::PlayerAcceptState::ACCEPTED);
   minecpp::proto::event::clientbound::v1::Event event;
   *event.mutable_single_player()->mutable_player_id() = player::write_id_to_proto(player.id());
   event.mutable_payload()->PackFrom(accept_player);

   m_events.post(event);
}

void Dispatcher::deny_player(const player::Id &player_id, const std::string &reason) {
   minecpp::proto::event::clientbound::v1::AcceptPlayer accept_player;
   accept_player.set_challenge_id(0);
   accept_player.set_denial_reason(reason);

   accept_player.set_state(proto::event::clientbound::v1::PlayerAcceptState::DENIED);
   minecpp::proto::event::clientbound::v1::Event event;
   *event.mutable_single_player()->mutable_player_id() = player::write_id_to_proto(player_id);
   event.mutable_payload()->PackFrom(accept_player);

   m_events.post(event);
}

}// namespace minecpp::service::engine
