#include "event_manager.h"
#include <game/events.h>

namespace Engine {

minecpp::engine::Event EventManager::pop() {
   auto front = event_queue.front();
   event_queue.pop();
   return front;
}

bool EventManager::has_events() { return !event_queue.empty(); }

} // namespace Engine
