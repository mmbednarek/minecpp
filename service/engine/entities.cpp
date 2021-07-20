#include "entities.h"

namespace minecpp::service::engine {

EntityId EntityManager::spawn(Entity e) {
   EntityId id = entities.size();
   e.set_id(id);
   entities.emplace_back(std::move(e));
   return id;
}

mb::result<Entity &> EntityManager::get_entity(EntityId id) {
   if (id >= entities.size()) {
      return mb::error("invalid entity id");
   }
   return entities.at(id);
}

} // namespace minecpp::service::engine
