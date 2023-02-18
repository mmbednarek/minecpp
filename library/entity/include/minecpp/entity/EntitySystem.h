#pragma once

#include "IEntitySpace.h"
#include <entt/entt.hpp>
#include <minecpp/game/Entity.h>
#include <minecpp/game/Game.h>
#include <minecpp/game/IEntitySystem.hpp>
#include <minecpp/proto/entity/v1/Entity.pb.h>

namespace minecpp::entity {

class EntitySystem final : public game::IEntitySystem
{
 public:
   EntitySystem();

   game::Entity create_spatial_entity(math::Vector3 position, math::Vector3 extent) override;
   std::vector<game::EntityId> list_entities_in(math::Vector3 min, math::Vector3 max) override;
   std::optional<game::EntityId> find_nearest_to(math::Vector3 position) override;
   game::Entity entity(game::EntityId id) override;
   void destroy_entity(game::EntityId id) override;
   std::vector<game::EntityId> list_entities_in_view_distance(math::Vector3 position) override;
   IEntitySpace &space();

 private:
   entt::registry m_registry;
   std::unique_ptr<IEntitySpace> m_storage;
   double m_view_distance{16.0};
   double m_min_y{-64.0};
   double m_max_y{1024.0};
};

class IEntityFactory
{
 public:
   virtual ~IEntityFactory() = default;

   virtual game::Entity create_entity(EntitySystem &entity_system) = 0;
};

}// namespace minecpp::entity
