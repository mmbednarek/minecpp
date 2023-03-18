#include <minecpp/entity/component/Health.h>
#include <minecpp/entity/component/Location.h>
#include <minecpp/entity/component/Player.h>
#include <minecpp/entity/component/Projectile.h>
#include <minecpp/entity/component/Team.h>
#include <minecpp/entity/component/Velocity.h>

namespace minecpp::entity::component {

Projectile::Projectile(game::EntityId owner, float damage) :
    m_owner(owner),
    m_damage(damage)
{
}

void Projectile::on_attached(game::Entity &entity)
{
   assert(entity.has_component<Location>());
   assert(entity.has_component<Velocity>());

   auto &location = entity.component<Location>();
   location.on_begin_intersect.connect_to<&Projectile::on_begin_intersect>(m_begin_intersect_sink, this);
   location.on_hit_ground.connect_to<&Projectile::on_hit_ground>(m_hit_ground_sink, this);

   auto &velocity = entity.component<Velocity>();
   velocity.on_velocity_change.connect_to<&Projectile::on_velocity_change>(m_velocity_change_sink, this);
}

void Projectile::serialize_to_proto(proto::entity::v1::Entity *entity) const
{
   entity->set_entity_type(static_cast<game::EntityId>(m_entity_type_id));
}

void Projectile::on_begin_intersect(game::IWorld &world, game::Entity &entity, game::Entity &other_entity)
{
   if (not other_entity.has_component<Health>())
      return;
   if (not other_entity.has_component<Location>())
      return;

   auto &health = other_entity.component<Health>();
   health.apply_damage(world, game::Damage{
                                      .amount        = m_damage,
                                      .source        = game::DamageSourceValue::Projectile,
                                      .source_entity = entity.id(),
                                      .target_entity = other_entity.id(),
                                      .vector        = entity.component<Velocity>().velocity().normalize(),
                              });

   world.kill_entity(entity.id());
}

game::EntityId Projectile::owner() const
{
   return m_owner;
}

void Projectile::on_hit_ground(game::IWorld &world, game::Entity &entity,
                               const math::Vector3 & /*position*/) const
{
   assert(this);
   world.kill_entity(entity.id());
}

void Projectile::on_velocity_change(game::IWorld &world, game::Entity &entity,
                                    const math::Vector3 &velocity) const
{
   assert(entity.has_component<Location>());
   assert(entity.has_component<Rotation>());

   entity.component<Rotation>().set_rotation(
           world.dispatcher(), entity.component<Location>().logical_position(),
           math::Rotation::from_vector3(velocity.cast<float>()).reverse_yaw());
}

}// namespace minecpp::entity::component
