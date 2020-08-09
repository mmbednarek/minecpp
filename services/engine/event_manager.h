#pragma once
#include <error/result.h>
#include <game/events.h>
#include <minepb/engine.pb.h>
#include <queue>
#include <string>

namespace Engine {

class EventManager {
   typedef std::queue<minecpp::engine::Event> Queue;
   std::map<std::string, Queue> queues;

 public:
   EventManager() = default;

   void post(auto &e) {
      minecpp::engine::Event event;
      event.set_recipient(minecpp::engine::EventRecipient::EVERYONE);
      event.set_kind(Game::Event(e.GetTypeName().substr(15).c_str()).index());
      event.set_data(e.SerializeAsString());

      for (auto &q : queues) {
         q.second.push(event);
      }
   }

   Queue &create_queue(const std::string &front_id);
};

} // namespace Engine
