#ifndef MINECPP_CLIENTBOUND_H
#define MINECPP_CLIENTBOUND_H
#include "Recipient.h"
#include <minecpp/game/player/Player.h>
#include <minecpp/proto/event/clientbound/Clientbound.pb.h>

namespace minecpp::event {

namespace clientbound_v1 = proto::event::clientbound;

template<typename T>
concept ClientboundVisitor =
        requires(T t) {
           t.handle_add_player(clientbound_v1::AddPlayer(), RecipientList{});
           t.handle_spawn_player(clientbound_v1::SpawnPlayer(), RecipientList{});
           t.handle_spawn_entity(clientbound_v1::SpawnEntity(), RecipientList{});
           t.handle_entity_move(clientbound_v1::EntityMove(), RecipientList{});
           t.handle_entity_look(clientbound_v1::EntityLook(), RecipientList{});
           t.handle_remove_player(clientbound_v1::RemovePlayer(), RecipientList{});
           t.handle_update_block(clientbound_v1::UpdateBlock(), RecipientList{});
           t.handle_chat(clientbound_v1::Chat(), RecipientList{});
           t.handle_animate_entity(clientbound_v1::AnimateEntity(), RecipientList{});
           t.handle_acknowledge_block_change(clientbound_v1::AcknowledgeBlockChange(), RecipientList{});
           t.handle_load_terrain(clientbound_v1::LoadTerrain(), RecipientList{});
           t.handle_unload_chunk(clientbound_v1::UnloadChunk(), RecipientList{});
           t.handle_player_list(clientbound_v1::PlayerList(), RecipientList{});
           t.handle_entity_list(clientbound_v1::EntityList(), RecipientList{});
           t.handle_accept_player(clientbound_v1::AcceptPlayer(), RecipientList{});
           t.handle_deny_player(clientbound_v1::DenyPlayer(), RecipientList{});
           t.handle_set_inventory_slot(clientbound_v1::SetInventorySlot(), RecipientList{});
           t.handle_update_block_light(clientbound_v1::UpdateBlockLight(), RecipientList{});
           t.handle_chunk_data(clientbound_v1::ChunkData(), RecipientList{});
           t.handle_set_center_chunk(clientbound_v1::SetCenterChunk(), RecipientList{});
           t.handle_player_position_rotation(clientbound_v1::PlayerPositionRotation(), RecipientList{});
           t.handle_set_spawn_position(clientbound_v1::SetSpawnPosition(), RecipientList{});
           t.handle_set_entity_equipment(clientbound_v1::SetEntityEquipment(), RecipientList{});
           t.handle_set_health(clientbound_v1::SetHealth(), RecipientList{});
           t.handle_collect_item(clientbound_v1::CollectItem(), RecipientList{});
           t.handle_remove_entity(clientbound_v1::RemoveEntity(), RecipientList{});
           t.handle_set_entity_velocity(clientbound_v1::SetEntityVelocity(), RecipientList{});
           t.handle_display_death_screen(clientbound_v1::DisplayDeathScreen(), RecipientList{});
           t.handle_respawn(clientbound_v1::Respawn(), RecipientList{});
           t.handle_teleport_entity(clientbound_v1::TeleportEntity(), RecipientList{});
           t.handle_set_abilities(clientbound_v1::SetAbilities(), RecipientList{});
           t.handle_raw_message(clientbound_v1::RawMessage(), RecipientList{});
        };

template<typename TEvent, typename TVisitor, typename TCallback>
void visit_event_type(const clientbound_v1::Event &event, TVisitor *visitor, TCallback callback)
{
   TEvent target_event;
   event.payload().UnpackTo(&target_event);

   switch (event.recipient_case()) {
   case proto::event::clientbound::Event::kSinglePlayer: {
      auto player_id = game::player::read_id_from_proto(event.single_player().player_id());
      std::invoke(callback, visitor, target_event,
                  RecipientList{
                          .type = RecipientType::Some,
                          .list{&player_id, &player_id + 1}
      });
      break;
   }
   case proto::event::clientbound::Event::kMultiplePlayers: {
      std::vector<game::PlayerId> result(static_cast<mb::size>(event.multiple_players().player_ids_size()));
      auto &player_ids = event.multiple_players().player_ids();
      std::transform(player_ids.begin(), player_ids.end(), result.begin(), game::player::read_id_from_proto);
      std::invoke(callback, visitor, target_event, RecipientList{.type = RecipientType::Some, .list{result}});
      break;
   }
   case proto::event::clientbound::Event::kAllPlayers: {
      std::invoke(callback, visitor, target_event, RecipientList{.type = RecipientType::All, .list{}});
      break;
   }
   case proto::event::clientbound::Event::kExcluding: {
      auto player_id = game::player::read_id_from_proto(event.excluding().player_id());
      std::invoke(callback, visitor, target_event,
                  RecipientList{
                          .type = RecipientType::Excluding,
                          .list{&player_id, &player_id + 1}
      });
      break;
   }
   default: break;
   }
}

#define MINECPP_EVENT_HANDLE_CLIENTBOUND(event_type, handler_method)                              \
   if (event.payload().Is<clientbound_v1::event_type>()) {                                        \
      visit_event_type<clientbound_v1::event_type>(event, &visitor, &VistorType::handler_method); \
      return;                                                                                     \
   }

template<typename T>
   requires ClientboundVisitor<T>
void visit_clientbound(const clientbound_v1::Event &event, T &visitor)
{
   using VistorType = std::decay_t<decltype(visitor)>;

   if (!event.has_payload())
      return;

   MINECPP_EVENT_HANDLE_CLIENTBOUND(AddPlayer, handle_add_player);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(SpawnPlayer, handle_spawn_player);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(SpawnEntity, handle_spawn_entity);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(EntityMove, handle_entity_move);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(EntityLook, handle_entity_look);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(RemovePlayer, handle_remove_player);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(UpdateBlock, handle_update_block);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(Chat, handle_chat);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(AnimateEntity, handle_animate_entity);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(AcknowledgeBlockChange, handle_acknowledge_block_change);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(LoadTerrain, handle_load_terrain);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(UnloadChunk, handle_unload_chunk);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(PlayerList, handle_player_list);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(EntityList, handle_entity_list);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(AcceptPlayer, handle_accept_player);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(DenyPlayer, handle_deny_player);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(SetInventorySlot, handle_set_inventory_slot);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(UpdateBlockLight, handle_update_block_light);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(ChunkData, handle_chunk_data);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(SetCenterChunk, handle_set_center_chunk);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(PlayerPositionRotation, handle_player_position_rotation);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(SetSpawnPosition, handle_set_spawn_position);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(SetEntityEquipment, handle_set_entity_equipment);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(SetHealth, handle_set_health);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(CollectItem, handle_collect_item);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(RemoveEntity, handle_remove_entity);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(SetEntityVelocity, handle_set_entity_velocity);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(DisplayDeathScreen, handle_display_death_screen);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(Respawn, handle_respawn);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(TeleportEntity, handle_teleport_entity);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(SetAbilities, handle_set_abilities);
   MINECPP_EVENT_HANDLE_CLIENTBOUND(RawMessage, handle_raw_message);
}

}// namespace minecpp::event

#endif//MINECPP_CLIENTBOUND_H
