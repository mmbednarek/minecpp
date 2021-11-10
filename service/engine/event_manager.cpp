#include "event_manager.h"
#include <minecpp/game/events.h>

namespace minecpp::service::engine {

EventManager::Queue &EventManager::create_queue(const std::string &front_id) {
   return m_queues[front_id];
}

} // namespace minecpp::service::engine
