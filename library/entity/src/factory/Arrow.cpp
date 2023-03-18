#include <minecpp/entity/component/Location.h>
#include <minecpp/entity/component/Projectile.h>
#include <minecpp/entity/component/Ticker.h>
#include <minecpp/entity/component/UniqueId.h>
#include <minecpp/entity/component/Velocity.h>
#include <minecpp/entity/factory/Arrow.h>

namespace minecpp::entity::factory {

Arrow::Arrow(const math::Vector3 &initial_velocity, const math::Rotation &rotation, game::EntityId owner_id,
             float damage) :
    m_initial_velocity(initial_velocity),
    m_initial_rotation(rotation),
    m_owner_id(owner_id),
    m_damage(damage)
{
}

game::Entity Arrow::create_entity(const math::Vector3 &position, game::IEntitySystem &entity_system)
{
   auto arrow_entity = entity_system.create_spatial_entity(position, {0.5, 0.5, 0.5});

   arrow_entity.add_component<component::UniqueId>();
   arrow_entity.add_component<component::Rotation>(m_initial_rotation);
   arrow_entity.add_component<component::Ticker>();
   arrow_entity.add_component<component::Velocity>(m_initial_velocity);
   arrow_entity.add_component<component::Projectile>(m_owner_id, m_damage);

   return arrow_entity;
}

}// namespace minecpp::entity::factory
