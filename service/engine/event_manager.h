#pragma once
#include <minecpp/game/events.h>
#include <minecpp/player/id.h>
#include <minecpp/proto/event/clientbound/v1/clientbound.pb.h>
#include <minecpp/util/static_queue.h>
#include <queue>
#include <spdlog/spdlog.h>
#include <string>

namespace minecpp::service::engine {


class EventManager {
 public:
   using Event = proto::event::clientbound::v1::Event;
   using Queue = minecpp::util::StaticQueue<Event, 256>;

 private:
   std::unordered_map<std::string, Queue> m_queues;

 public:
   EventManager() = default;

   void send_to(auto &event, player::Id player_id) {
      for (auto &q : m_queues) {
         Event proto_event;
         *proto_event.mutable_single_player()->mutable_player_id() = player::write_id_to_proto(player_id);
         proto_event.mutable_payload()->PackFrom(event);
         // TODO: Get front id from player manager
         q.second.push(std::move(proto_event));
      }
   }

   void send_to_all(auto &event) {
      for (auto &q : m_queues) {
         Event proto_event;
         *proto_event.mutable_all_players() = proto::event::clientbound::v1::RecipientAllPlayers();
         proto_event.mutable_payload()->PackFrom(event);
         q.second.push(std::move(proto_event));
      }
   }

   Queue &create_queue(const std::string &front_id);
};

}// namespace minecpp::service::engine
