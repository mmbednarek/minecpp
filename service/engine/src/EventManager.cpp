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

void EventManager::add_client(ConnectionId id, std::unique_ptr<IConnection> stream)
{
   std::lock_guard<std::mutex> lock(m_queue_mutex);
   m_queues.emplace(id, std::move(stream));
}

void EventManager::send_to_all_excluding(const EventManager::Message &message, game::PlayerId player_id)
{
   for (auto &q : m_queues) {
      q.second->send_to_all_excluding(message, player_id);
   }
}

void EventManager::send_to_many(const EventManager::Message &message, std::span<game::PlayerId> player_id)
{
   for (auto &q : m_queues) {
      q.second->send_to_many(message, player_id);
   }
}

void EventManager::remove_client(ConnectionId id)
{
   m_queues.erase(id);
}

}// namespace minecpp::service::engine
