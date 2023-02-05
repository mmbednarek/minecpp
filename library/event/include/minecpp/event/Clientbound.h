#ifndef MINECPP_CLIENTBOUND_H
#define MINECPP_CLIENTBOUND_H
#include <minecpp/game/player/Player.h>
#include <minecpp/proto/event/clientbound/v1/Clientbound.pb.h>

namespace minecpp::event {

namespace clientbound_v1 = proto::event::clientbound::v1;

template<typename T>
concept ClientboundVisitor =
        requires(T t) {
           t.handle_add_player(clientbound_v1::AddPlayer(), std::vector<game::PlayerId>());
           t.handle_spawn_player(clientbound_v1::SpawnPlayer(), std::vector<game::PlayerId>());
           t.handle_entity_move(clientbound_v1::EntityMove(), std::vector<game::PlayerId>());
           t.handle_entity_look(clientbound_v1::EntityLook(), std::vector<game::PlayerId>());
           t.handle_remove_player(clientbound_v1::RemovePlayer(), std::vector<game::PlayerId>());
           t.handle_update_block(clientbound_v1::UpdateBlock(), std::vector<game::PlayerId>());
           t.handle_chat(clientbound_v1::Chat(), std::vector<game::PlayerId>());
           t.handle_animate_hand(clientbound_v1::AnimateHand(), std::vector<game::PlayerId>());
           t.handle_acknowledge_block_change(clientbound_v1::AcknowledgeBlockChange(),
                                             std::vector<game::PlayerId>());
           t.handle_load_terrain(clientbound_v1::LoadTerrain(), std::vector<game::PlayerId>());
           t.handle_transfer_player(clientbound_v1::TransferPlayer(), std::vector<game::PlayerId>());
           t.handle_unload_chunk(clientbound_v1::UnloadChunk(), std::vector<game::PlayerId>());
           t.handle_player_list(clientbound_v1::PlayerList(), std::vector<game::PlayerId>());
           t.handle_entity_list(clientbound_v1::EntityList(), std::vector<game::PlayerId>());
           t.handle_accept_player(clientbound_v1::AcceptPlayer(), std::vector<game::PlayerId>());
           t.handle_deny_player(clientbound_v1::DenyPlayer(), std::vector<game::PlayerId>());
           t.handle_set_inventory_slot(clientbound_v1::SetInventorySlot(), std::vector<game::PlayerId>());
           t.handle_update_block_light(clientbound_v1::UpdateBlockLight(), std::vector<game::PlayerId>());
           t.handle_chunk_data(clientbound_v1::ChunkData(), std::vector<game::PlayerId>());
           t.handle_set_center_chunk(clientbound_v1::SetCenterChunk(), std::vector<game::PlayerId>());
        };

std::vector<game::PlayerId> read_recipients(const clientbound_v1::Event &event);

#define MINECPP_EVENT_HANDLE_CLIENTBOUND(event_type, handler_method) \
   if (event.payload().Is<clientbound_v1::event_type>()) {           \
      clientbound_v1::event_type _event;                             \
      event.payload().UnpackTo(&_event);                             \
      visitor.handler_method(_event, read_recipients(event));        \
      return;                                                        \
   }

template<typename T>
   requires ClientboundVisitor<T>

void visit_clientbound(const clientbound_v1::Event &event, T &visitor)
{
   if (!event.has_payload())
      return;

   MINECPP_EVENT_HANDLE_CLIENTBOUND(AddPlayer, handle_add_player);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(SpawnPlayer, handle_spawn_player);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(EntityMove, handle_entity_move);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(EntityLook, handle_entity_look);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(RemovePlayer, handle_remove_player);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(UpdateBlock, handle_update_block);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(Chat, handle_chat);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(AnimateHand, handle_animate_hand);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(AcknowledgeBlockChange, handle_acknowledge_block_change);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(LoadTerrain, handle_load_terrain);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(TransferPlayer, handle_transfer_player);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(UnloadChunk, handle_unload_chunk);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(PlayerList, handle_player_list);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(EntityList, handle_entity_list);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(AcceptPlayer, handle_accept_player);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(DenyPlayer, handle_deny_player);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(SetInventorySlot, handle_set_inventory_slot);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(UpdateBlockLight, handle_update_block_light);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(ChunkData, handle_chunk_data);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(SetCenterChunk, handle_set_center_chunk);
}

}// namespace minecpp::event

#endif//MINECPP_CLIENTBOUND_H
