#pragma once
#include <minecpp/game/events.h>
#include <minecpp/player/id.h>
#include <minecpp/proto/event/clientbound/v1/clientbound.pb.h>
#include <minecpp/util/static_queue.h>
#include <queue>
#include <spdlog/spdlog.h>
#include <string>

namespace minecpp::service::engine {

template<typename TStream>
class EventManager {
 public:
   using Event = proto::event::clientbound::v1::Event;
   using Queue = minecpp::util::StaticQueue<Event, 256>;

   struct Client {
      TStream stream;
      EventManager::Queue queue;
      std::atomic<bool> writing = false;

      explicit Client(TStream stream) : stream(stream) {}

      void write(Event event) {
         if(!writing) {
            writing = true;
            stream.write(event);
            return;
         }
         queue.push(std::move(event));
      }
   };

 private:
   std::unordered_map<std::string, Client> m_queues;
   std::mutex m_queue_mutex;

 public:
   EventManager() = default;

   void send_to(auto &event, player::Id player_id) {
      for (auto &q : m_queues) {
         Event proto_event;
         *proto_event.mutable_single_player()->mutable_player_id() = player::write_id_to_proto(player_id);
         proto_event.mutable_payload()->PackFrom(event);
         // TODO: Get front id from player manager
         q.second.write(std::move(proto_event));
      }
   }

   void send_to_all(auto &event) {
      for (auto &q : m_queues) {
         Event proto_event;
         *proto_event.mutable_all_players() = proto::event::clientbound::v1::RecipientAllPlayers();
         proto_event.mutable_payload()->PackFrom(event);
         q.second.write(std::move(proto_event));
      }
   }

   [[nodiscard]] Client *client(const std::string &tag) {
      if (m_queues.contains(tag)) {
         return &m_queues.at(tag);
      }
      return nullptr;
   }

   void add_client(TStream stream) {
      std::lock_guard<std::mutex> lock(m_queue_mutex);
      m_queues.emplace(stream.tag(), std::move(stream));
   }
};

}// namespace minecpp::service::engine
