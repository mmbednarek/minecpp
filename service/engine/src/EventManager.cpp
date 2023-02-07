#include "EventManager.h"

namespace minecpp::service::engine {

void EventManager::send_to(const EventManager::Message &message, game::PlayerId player_id)
{
   for (auto &q : m_queues) {
      q.second->send_to_player(message, player_id);
   }
}

void EventManager::send_to_all(const EventManager::Message &message)
{
   for (auto &q : m_queues) {
      q.second->send_to_all(message);
   }
}

IConnection *EventManager::client(ConnectionId id)
{
   if (m_queues.contains(id)) {
      return m_queues.at(id).get();
   }
   return nullptr;
}

void EventManager::add_client(std::unique_ptr<IConnection> stream)
{
   std::lock_guard<std::mutex> lock(m_queue_mutex);
   m_queues.emplace(m_top_connection_id, std::move(stream));
   ++m_top_connection_id;
}

void EventManager::send_to_all_excluding(const EventManager::Message &message, game::PlayerId player_id)
{
   for (auto &q : m_queues) {
      q.second->send_to_all_excluding(message, player_id);
   }
}

}// namespace minecpp::service::engine
