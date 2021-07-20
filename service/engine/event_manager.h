#pragma once
#include <minecpp/game/events.h>
#include <minecpp/util/static_queue.h>
#include <minepb/engine.pb.h>
#include <queue>
#include <spdlog/spdlog.h>
#include <string>

namespace minecpp::service::engine {

class EventManager {
   using Queue = minecpp::util::StaticQueue<minecpp::engine::Event, 256>;
   std::unordered_map<std::string, Queue> queues;

 public:
   EventManager() = default;

   void post(auto &e) {
      auto event_kind = minecpp::game::Event(e.GetTypeName().substr(15).c_str()).index();
      auto serialized_event = e.SerializeAsString();

      for (auto &q : queues) {
         minecpp::engine::Event event;
         event.set_recipient(minecpp::engine::EventRecipient::EVERYONE);
         event.set_kind(event_kind);
         event.set_data(serialized_event);
         q.second.push(std::move(event));
      }
   }

   Queue &create_queue(const std::string &front_id);
};

} // namespace minecpp::service::engine
