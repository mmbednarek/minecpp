#include <minecpp/entity/component/Health.h>
#include <minecpp/entity/component/Location.h>
#include <minecpp/entity/component/Player.h>
#include <minecpp/entity/component/Projectile.h>
#include <minecpp/entity/component/Velocity.h>

namespace minecpp::entity::component {

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

   auto &health  = other_entity.component<Health>();
   health.health = std::max(0.0f, health.health - 2.0f);

   world.dispatcher().animate_entity(other_entity.id(), other_entity.component<Location>().position(),
                                     game::EntityAnimation::TakeDamage);

   if (other_entity.has_component<Velocity>()) {
      auto &velocity = other_entity.component<Velocity>();
      velocity.set_velocity(world.dispatcher(), other_entity.component<Location>().position(), entity.component<Velocity>().velocity().normalize());
   }

   if (other_entity.has_component<Player>()) {
      world.dispatcher().set_health_and_food(other_entity.component<Player>().id(),
                                             health.health, 20, 5.0f);
   }

   world.kill_entity(entity.id());
}

}// namespace minecpp::entity::component
