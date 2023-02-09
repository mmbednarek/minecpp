#include "Entities.h"

namespace minecpp::service::engine {

game::EntityId EntityManager::spawn(Entity e)
{
   auto id = m_top_entity_id;
   ++m_top_entity_id;
   e.set_id(id);
   m_entities.emplace(id, std::move(e));
   return id;
}

mb::result<Entity &> EntityManager::get_entity(game::EntityId id)
{
   if (not m_entities.contains(id)) {
      return mb::error("invalid entity id");
   }
   return m_entities.at(id);
}

mb::emptyres EntityManager::remove_entity(game::EntityId id)
{
   auto it = m_entities.find(id);
   if (it == m_entities.end()) {
      return mb::error("invalid entity id");
   }
   m_entities.erase(it);
   return mb::ok;
}

EntityManager::Iterator EntityManager::begin()
{
   return m_entities.begin();
}

EntityManager::Iterator EntityManager::end()
{
   return m_entities.end();
}

mb::size EntityManager::total_count()
{
   return m_entities.size();
}

}// namespace minecpp::service::engine
