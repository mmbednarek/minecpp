#ifndef MINECPP_SERVERBOUND_H
#define MINECPP_SERVERBOUND_H
#include <minecpp/player/player.h>
#include <minecpp/proto/event/serverbound/v1/serverbound.pb.h>

namespace minecpp::event {

namespace serverbound_v1 = proto::event::serverbound::v1;

template<typename T>
concept ServerboundVisitor = requires(T t) {
   t.handle_accept_player(serverbound_v1::AcceptPlayer(), player::Id());
   t.handle_set_player_position(serverbound_v1::SetPlayerPosition(), player::Id());
   t.handle_set_player_rotation(serverbound_v1::SetPlayerRotation(), player::Id());
   t.handle_chat_message(serverbound_v1::ChatMessage(), player::Id());
   t.handle_remove_player(serverbound_v1::RemovePlayer(), player::Id());
   t.handle_destroy_block(serverbound_v1::DestroyBlock(), player::Id());
   t.handle_update_ping(serverbound_v1::UpdatePing(), player::Id());
   t.handle_animate_hand(serverbound_v1::AnimateHand(), player::Id());
   t.handle_load_initial_chunks(serverbound_v1::LoadInitialChunks(), player::Id());
};

#define MINECPP_EVENT_HANDLE_SERVICEBOUND(event_type, handler_method)                \
   if (event.payload().Is<serverbound_v1::event_type>()) {                           \
      serverbound_v1::event_type _event;                                             \
      event.payload().UnpackTo(&_event);                                             \
      visitor.handler_method(_event, player::read_id_from_proto(event.player_id())); \
      return;                                                                        \
   }

template<typename T>
requires ServerboundVisitor<T>
void visit_serverbound(const serverbound_v1::Event &event, T &visitor) {
   if (!event.has_payload())
      return;

   MINECPP_EVENT_HANDLE_SERVICEBOUND(AcceptPlayer, handle_accept_player);
   MINECPP_EVENT_HANDLE_SERVICEBOUND(SetPlayerPosition, handle_set_player_position);
   MINECPP_EVENT_HANDLE_SERVICEBOUND(SetPlayerRotation, handle_set_player_rotation);
   MINECPP_EVENT_HANDLE_SERVICEBOUND(ChatMessage, handle_chat_message);
   MINECPP_EVENT_HANDLE_SERVICEBOUND(RemovePlayer, handle_remove_player);
   MINECPP_EVENT_HANDLE_SERVICEBOUND(DestroyBlock, handle_destroy_block);
   MINECPP_EVENT_HANDLE_SERVICEBOUND(UpdatePing, handle_update_ping);
   MINECPP_EVENT_HANDLE_SERVICEBOUND(AnimateHand, handle_animate_hand);
   MINECPP_EVENT_HANDLE_SERVICEBOUND(LoadInitialChunks, handle_load_initial_chunks);
}

}// namespace minecpp::event

#endif//MINECPP_SERVERBOUND_H
