#pragma once

#include "Entity.h"
#include "IEntitySpace.h"
#include <entt/entt.hpp>
#include <minecpp/game/Game.h>
#include <minecpp/proto/entity/v1/Entity.pb.h>

namespace minecpp::entity {

class EntitySystem
{
 public:
   EntitySystem();

   Entity create_spatial_entity(math::Vector3 position, math::Vector3 extent);
   std::vector<game::EntityId> list_entities_in(math::Vector3 min, math::Vector3 max);
   std::optional<game::EntityId> find_nearest_to(math::Vector3 position);
   IEntitySpace &space();
   Entity entity(game::EntityId id);

 private:
   entt::registry m_registry;
   std::unique_ptr<IEntitySpace> m_storage;
};

class IEntityFactory
{
 public:
   virtual ~IEntityFactory() = default;

   virtual game::EntityId create_entity(EntitySystem &entity_system) = 0;
};

}// namespace minecpp::entity
