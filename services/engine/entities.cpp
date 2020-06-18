#include "entities.h"

namespace Engine {

EntityId EntityManager::spawn(Entity e) {
   EntityId id = entities.size();
   e.set_id(id);
   entities.emplace_back(std::move(e));
   return id;
}

Entity &EntityManager::get_entity(EntityId id) {
   return entities.at(id);
}

} // namespace Engine
