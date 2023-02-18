#include "EntitySpace.h"
#include <minecpp/entity/component/Health.h>
#include <minecpp/entity/component/Location.h>
#include <minecpp/entity/component/Player.h>
#include <minecpp/game/Concepts.h>
#include <minecpp/entity/EntitySystem.h>

namespace minecpp::entity {

EntitySystem::EntitySystem() :
    m_storage(std::make_unique<EntitySpace>())
{
   game::register_component<component::Location>();
   game::register_component<component::Player>();
   game::register_component<component::Health>();
   game::register_component<component::Rotation>();
}

game::Entity EntitySystem::create_spatial_entity(math::Vector3 position, math::Vector3 extent)
{
   auto entity_id = m_registry.create();
   auto entity = this->entity(static_cast<game::EntityId>(entity_id));

   entity.add_component<component::Location>(position, extent);
   m_storage->register_entity(entity.id(), position, extent);

   return entity;
}

std::optional<game::EntityId> EntitySystem::find_nearest_to(math::Vector3 position)
{
   return m_storage->find_nearest(position);
}

IEntitySpace &EntitySystem::space()
{
   return *m_storage;
}

std::vector<game::EntityId> EntitySystem::list_entities_in(math::Vector3 min, math::Vector3 max)
{
   return m_storage->list_entities_in(min, max);
}

game::Entity EntitySystem::entity(game::EntityId id)
{
   return {m_registry, id};
}

void EntitySystem::destroy_entity(game::EntityId id)
{
   m_registry.destroy(static_cast<entt::entity>(id));
}

std::vector<game::EntityId> EntitySystem::list_entities_in_view_distance(math::Vector3 position)
{
   return this->list_entities_in({position.x() - m_view_distance, m_min_y, position.z() - m_view_distance}, {position.x() + m_view_distance, m_max_y, position.z() + m_view_distance});
}

}// namespace minecpp::entity
