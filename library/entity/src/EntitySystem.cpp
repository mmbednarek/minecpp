#include "EntitySpace.h"
#include <minecpp/entity/component/Health.h>
#include <minecpp/entity/component/Location.h>
#include <minecpp/entity/component/Player.h>
#include <minecpp/entity/Concepts.h>
#include <minecpp/entity/EntitySystem.h>

namespace minecpp::entity {

EntitySystem::EntitySystem() :
    m_storage(std::make_unique<EntitySpace>())
{
   register_component<component::Location>();
   register_component<component::Player>();
   register_component<component::Health>();
   register_component<component::Rotation>();
}

Entity EntitySystem::create_spatial_entity(math::Vector3 position, math::Vector3 extent)
{
   auto entity = m_registry.create();
   m_registry.emplace<component::Location>(entity, position, extent);

   auto entity_id = static_cast<game::EntityId>(entity);
   m_storage->register_entity(entity_id, position, extent);
   return this->entity(entity_id);
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

Entity EntitySystem::entity(game::EntityId id)
{
   return {m_registry, id};
}

}// namespace minecpp::entity
