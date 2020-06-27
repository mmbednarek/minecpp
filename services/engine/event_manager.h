#pragma once
#include <game/events.h>
#include <minepb/engine.pb.h>
#include <queue>
#include <string>

template <typename T> concept Event = requires(T msg, std::string s) {
   s = msg.GetTypeName();
   s = msg.SerializeAsString();
};

namespace Engine {

class EventManager {
   std::queue<minecpp::engine::Event> event_queue;

 public:
   EventManager() = default;

   void post(Event auto &e) {
      minecpp::engine::Event event;
      event.set_recipient(minecpp::engine::EventRecipient::EVERYONE);
      event.set_kind(Game::Event(e.GetTypeName().substr(15).c_str()).index());
      event.set_data(e.SerializeAsString());
      event_queue.push(std::move(event));
   }
   minecpp::engine::Event pop();
   bool has_events();
};

} // namespace Engine
