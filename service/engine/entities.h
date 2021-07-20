#pragma once
#include <mb/result.h>
#include <minecpp/game/entity/entity.h>
#include <vector>

namespace minecpp::service::engine {

using minecpp::game::entity::Entity;

typedef uint32_t EntityId;

class EntityManager {
   std::vector<Entity> entities;

 public:
   // NOTICE: Entity is moved
   EntityId spawn(Entity e);
   mb::result<Entity &> get_entity(EntityId id);
};

}// namespace minecpp::service::engine
