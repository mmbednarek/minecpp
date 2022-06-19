#include "Entities.h"

namespace minecpp::service::engine {

game::EntityId EntityManager::spawn(Entity e)
{
   auto id = static_cast<game::EntityId>(m_entities.size());
   e.set_id(id);
   m_entities.emplace_back(std::move(e));
   return id;
}

mb::result<Entity &> EntityManager::get_entity(game::EntityId id)
{
   if (id >= m_entities.size()) {
      return mb::error("invalid entity id");
   }
   return m_entities.at(id);
}

}// namespace minecpp::service::engine