#include "Dispatcher.h"
#include <minecpp/chat/Chat.h>
#include <minecpp/game/player/Player.h>
#include <minecpp/proto/event/clientbound/v1/Clientbound.pb.h>
#include <minecpp/service/engine/Api.h>
#include <minecpp/util/Uuid.h>

namespace minecpp::service::engine {

namespace clientbound_v1 = proto::event::clientbound::v1;

Dispatcher::Dispatcher(EventManager<BidiStream> &events) :
    m_events(events)
{
}

void Dispatcher::load_terrain(game::PlayerId player_id, const game::ChunkPosition &central_chunk,
                              std::vector<minecpp::game::ChunkPosition> coords)
{
   clientbound_v1::LoadTerrain event;
   *event.mutable_central_chunk() = central_chunk.to_proto();
   for (const auto &c : coords) {
      *event.add_coords() = c.to_proto();
   }
   m_events.send_to(event, player_id);
}

void Dispatcher::transfer_player(game::PlayerId player_id, boost::uuids::uuid target_engine)
{
   clientbound_v1::TransferPlayer event;
   event.set_engine_instance_id(0);// TODO: Set engine id
   m_events.send_to(event, player_id);
}

void Dispatcher::entity_move(game::PlayerId player_id, game::EntityId entity_id,
                             const game::entity::Movement &movement, const game::entity::Rotation &rotation)
{
   clientbound_v1::EntityMove event;
   event.set_entity_id(entity_id);
   *event.mutable_player_id() = game::player::write_id_to_proto(player_id);
   *event.mutable_movement()  = movement.to_proto();
   *event.mutable_rotation()  = rotation.to_proto();
   m_events.send_to_all(event);
}

void Dispatcher::add_player(game::PlayerId player_id, const std::string &name, mb::u32 ping)
{
   clientbound_v1::AddPlayer add_player;
   *add_player.mutable_player_id() = game::player::write_id_to_proto(player_id);
   add_player.set_name(name);
   add_player.set_ping(ping);
   m_events.send_to_all(add_player);
}

void Dispatcher::spawn_player(game::PlayerId player_id, game::EntityId entity_id,
                              minecpp::util::Vec3 position, const game::entity::Rotation &rotation)
{
   clientbound_v1::SpawnPlayer spawn_player;
   *spawn_player.mutable_player_id() = game::player::write_id_to_proto(player_id);
   spawn_player.set_entity_id(entity_id);
   *spawn_player.mutable_position() = game::entity::write_entity_position(position);
   *spawn_player.mutable_rotation() = rotation.to_proto();
   m_events.send_to_all(spawn_player);
}

void Dispatcher::send_chat(chat::MessageType msg_type, const std::string &msg)
{
   clientbound_v1::Chat chat;
   chat.set_type(static_cast<google::protobuf::int32>(msg_type));
   chat.set_message(msg);
   m_events.send_to_all(chat);
}

void Dispatcher::entity_look(game::PlayerId player_id, mb::u32 entity_id,
                             const game::entity::Rotation &rotation)
{
   clientbound_v1::EntityLook event;
   *event.mutable_player_id() = game::player::write_id_to_proto(player_id);
   event.set_entity_id(entity_id);
   *event.mutable_rotation() = rotation.to_proto();
   m_events.send_to_all(event);
}

void Dispatcher::remove_player(game::PlayerId player_id, mb::u32 entity_id)
{
   clientbound_v1::RemovePlayer remove_player;
   *remove_player.mutable_player_id() = game::player::write_id_to_proto(player_id);
   remove_player.set_entity_id(entity_id);
   m_events.send_to_all(remove_player);
}

void Dispatcher::update_block(minecpp::game::BlockPosition block, game::BlockStateId state)
{
   clientbound_v1::UpdateBlock update_block;
   update_block.set_block_position(block.as_long());
   update_block.set_state(state);
   m_events.send_to_all(update_block);
}

void Dispatcher::animate_hand(game::PlayerId player_id, mb::u32 entity_id, mb::u32 hand)
{
   clientbound_v1::AnimateHand animate;
   *animate.mutable_player_id() = game::player::write_id_to_proto(player_id);
   animate.set_entity_id(entity_id);
   animate.set_hand(hand);
   m_events.send_to_all(animate);
}

void Dispatcher::acknowledge_block_change(game::PlayerId player_id, int sequence_id)
{
   clientbound_v1::AcknowledgeBlockChange digging;
   digging.set_sequence_id(sequence_id);
   m_events.send_to(digging, player_id);
}

void Dispatcher::unload_chunk(game::PlayerId player, const game::ChunkPosition &chunk_position)
{
   clientbound_v1::UnloadChunk unload;
   *unload.mutable_player_id()      = game::player::write_id_to_proto(player);
   *unload.mutable_chunk_position() = chunk_position.to_proto();
   m_events.send_to_all(unload);
}

void Dispatcher::accept_player(const game::player::Player &player, const game::entity::Entity &entity)
{
   clientbound_v1::AcceptPlayer accept_player;
   accept_player.mutable_gameplay()->set_view_distance(32);
   *accept_player.mutable_player() = player.to_proto(entity);
   m_events.send_to(accept_player, player.id());
}

void Dispatcher::deny_player(const game::PlayerId &player_id, const std::string &reason)
{
   clientbound_v1::DenyPlayer deny_player;
   deny_player.set_denial_reason(reason);
   m_events.send_to(deny_player, player_id);
}

void Dispatcher::player_list(game::PlayerId player_id, const std::vector<game::player::Status> &status_list)
{
   clientbound_v1::PlayerList player_list;
   player_list.mutable_list()->Reserve(static_cast<int>(status_list.size()));
   for (const auto &status : status_list) {
      *player_list.add_list() = status.to_proto();
   }
   m_events.send_to(player_list, player_id);
}

void Dispatcher::entity_list(game::PlayerId player_id, const std::vector<game::entity::Entity> &entity_list)
{
   clientbound_v1::EntityList list;
   list.mutable_list()->Reserve(static_cast<int>(entity_list.size()));
   for (const auto &entity : entity_list) {
      *list.add_list() = entity.to_proto();
   }
   spdlog::info("sending {} entities to the player", entity_list.size());
   m_events.send_to(list, player_id);
}

void Dispatcher::set_inventory_slot(game::PlayerId player_id, game::ItemId item_id,
                                    game::SlotId slot_id, std::size_t count)
{
   clientbound_v1::SetInventorySlot set_slot;
   set_slot.mutable_slot()->set_slot_id(slot_id);
   set_slot.mutable_slot()->set_count(static_cast<uint32_t>(count));
   set_slot.mutable_slot()->mutable_item_id()->set_id(static_cast<uint32_t>(item_id));
   m_events.send_to(set_slot, player_id);
}

}// namespace minecpp::service::engine
