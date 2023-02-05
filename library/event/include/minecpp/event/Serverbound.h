#ifndef MINECPP_SERVERBOUND_H
#define MINECPP_SERVERBOUND_H
#include <minecpp/game/player/Player.h>
#include <minecpp/proto/event/serverbound/v1/Serverbound.pb.h>

namespace minecpp::event {

namespace serverbound_v1 = proto::event::serverbound::v1;

template<typename T>
concept ServerboundVisitor =
        requires(T t) {
           t.handle_accept_player(serverbound_v1::AcceptPlayer(), game::PlayerId());
           t.handle_set_player_position(serverbound_v1::SetPlayerPosition(), game::PlayerId());
           t.handle_set_player_rotation(serverbound_v1::SetPlayerRotation(), game::PlayerId());
           t.handle_chat_message(serverbound_v1::ChatMessage(), game::PlayerId());
           t.handle_remove_player(serverbound_v1::RemovePlayer(), game::PlayerId());
           t.handle_player_digging(serverbound_v1::PlayerDigging(), game::PlayerId());
           t.handle_update_ping(serverbound_v1::UpdatePing(), game::PlayerId());
           t.handle_animate_hand(serverbound_v1::AnimateHand(), game::PlayerId());
           t.handle_load_initial_chunks(serverbound_v1::LoadInitialChunks(), game::PlayerId());
           t.handle_block_placement(serverbound_v1::BlockPlacement(), game::PlayerId());
           t.handle_change_inventory_item(serverbound_v1::ChangeInventoryItem(), game::PlayerId());
           t.handle_change_held_item(serverbound_v1::ChangeHeldItem(), game::PlayerId());
           t.handle_issue_command(serverbound_v1::IssueCommand(), game::PlayerId());
        };

#define MINECPP_EVENT_HANDLE_SERVICEBOUND(event_type, handler_method)                      \
   if (event.payload().Is<serverbound_v1::event_type>()) {                                 \
      serverbound_v1::event_type _event;                                                   \
      event.payload().UnpackTo(&_event);                                                   \
      visitor.handler_method(_event, game::player::read_id_from_proto(event.player_id())); \
      return;                                                                              \
   }

template<typename T>
   requires ServerboundVisitor<T>

void visit_serverbound(const serverbound_v1::Event &event, T &visitor)
{
   if (!event.has_payload())
      return;

   MINECPP_EVENT_HANDLE_SERVICEBOUND(AcceptPlayer, handle_accept_player);
   MINECPP_EVENT_HANDLE_SERVICEBOUND(SetPlayerPosition, handle_set_player_position);
   MINECPP_EVENT_HANDLE_SERVICEBOUND(SetPlayerRotation, handle_set_player_rotation);
   MINECPP_EVENT_HANDLE_SERVICEBOUND(ChatMessage, handle_chat_message);
   MINECPP_EVENT_HANDLE_SERVICEBOUND(RemovePlayer, handle_remove_player);
   MINECPP_EVENT_HANDLE_SERVICEBOUND(PlayerDigging, handle_player_digging);
   MINECPP_EVENT_HANDLE_SERVICEBOUND(UpdatePing, handle_update_ping);
   MINECPP_EVENT_HANDLE_SERVICEBOUND(AnimateHand, handle_animate_hand);
   MINECPP_EVENT_HANDLE_SERVICEBOUND(LoadInitialChunks, handle_load_initial_chunks);
   MINECPP_EVENT_HANDLE_SERVICEBOUND(BlockPlacement, handle_block_placement);
   MINECPP_EVENT_HANDLE_SERVICEBOUND(ChangeInventoryItem, handle_change_inventory_item);
   MINECPP_EVENT_HANDLE_SERVICEBOUND(ChangeHeldItem, handle_change_held_item);
   MINECPP_EVENT_HANDLE_SERVICEBOUND(IssueCommand, handle_issue_command);
}

}// namespace minecpp::event

#endif//MINECPP_SERVERBOUND_H
