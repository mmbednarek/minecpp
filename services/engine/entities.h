#pragma once
#include <vector>
#include <minecpp/game/entities/entity.h>

namespace Engine {

using Game::Entity::Entity;

typedef uint32_t EntityId;

class EntityManager {
   std::vector<Entity> entities;

 public:
   // NOTICE: Entity is moved
   EntityId spawn(Entity e);
   Entity &get_entity(EntityId id);
};

}
