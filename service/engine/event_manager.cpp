#include "event_manager.h"
#include <minecpp/game/events.h>
#include <utility>

namespace Engine {

EventManager::Queue &EventManager::create_queue(const std::string &front_id) {
   return queues[front_id];
}

} // namespace Engine
