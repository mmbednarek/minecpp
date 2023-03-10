#include <minecpp/entity/component/Health.h>
#include <minecpp/entity/component/Location.h>
#include <minecpp/entity/component/Player.h>
#include <minecpp/entity/component/Projectile.h>
#include <minecpp/entity/component/Velocity.h>

namespace minecpp::entity::component {

Projectile::Projectile(game::EntityId owner) :
    m_owner(owner)
{
}

void Projectile::on_attached(game::Entity &entity)
{
   if (entity.has_component<Location>()) {
      auto &location = entity.component<Location>();
      entt::sink sink{location.on_begin_intersect};
      sink.connect<&Projectile::on_begin_intersect>(this);
   }
}

void Projectile::serialize_to_proto(proto::entity::v1::Entity *entity) const
{
   entity->set_entity_type(m_entity_type_id);
}

void Projectile::on_begin_intersect(game::IWorld &world, game::Entity &entity, game::Entity &other_entity)
{
   if (not other_entity.has_component<Health>())
      return;
   if (not other_entity.has_component<Location>())
      return;

   auto &health = other_entity.component<Health>();
   health.apply_damage(world, game::Damage{
                                      .amount        = 2.0f,
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

}// namespace minecpp::entity::component
