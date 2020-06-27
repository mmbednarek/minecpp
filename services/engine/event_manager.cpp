#include "event_manager.h"
#include <game/events.h>

namespace Engine {

EventManager::Queue &EventManager::create_queue(const std::string &front_id) {
   queues[front_id] = Queue();
   return queues[front_id];
}

} // namespace Engine
