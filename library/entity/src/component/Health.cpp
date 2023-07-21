#include <minecpp/entity/component/Health.h>
#include <minecpp/entity/component/Location.h>
#include <minecpp/entity/component/Player.h>
#include <minecpp/entity/component/Projectile.h>
#include <minecpp/entity/component/Velocity.h>

namespace minecpp::entity::component {

Health::Health(float health) :
    m_health(health)
{
}

void Health::apply_damage(game::IWorld &world, const game::Damage &damage)
{
   const auto target_health = std::max(m_health - damage.amount, 0.0f);
   const auto killed{target_health == 0.0f};

   auto entity = world.entity_system().entity(damage.target_entity);

   if (entity.has_component<Location>()) {
      world.dispatcher().send_damage_event(damage.target_entity, 0, damage.source_entity, damage.source_entity, entity.component<Location>().position());
   }

   if (killed) {
      this->on_dead.publish(world, entity, damage);
   }

   m_health = target_health;

   if (entity.has_component<Player>()) {
      assert(entity.has_component<Food>());

      const auto player_id = entity.component<Player>().id();
      const auto &food     = entity.component<Food>();

      world.dispatcher().set_health_and_food(player_id, target_health, food.food, food.saturation);
   }

   if (killed) {
      world.kill_entity(damage.target_entity);
      return;
   }

   if (entity.has_component<Velocity>()) {
      assert(entity.has_component<Location>());
      auto &velocity = entity.component<Velocity>();
      velocity.set_velocity(world, entity, damage.vector);
   }
}

game::Health Health::health() const
{
   return m_health;
}

void Health::on_attached_to_world(game::IWorld * /*world*/, game::Entity * /*entity*/,
                                  const math::Vector3 & /*position*/, const math::Vector3 & /*extent*/)
{
   m_health = 20.0f;
}

void Health::heal(game::IWorld &world, game::Entity &entity, game::Health amount)
{
   m_health = std::min(m_health + amount, g_max_health);

   if (entity.has_component<Player>()) {
      assert(entity.has_component<Food>());

      const auto player_id = entity.component<Player>().id();
      const auto &food     = entity.component<Food>();

      world.dispatcher().set_health_and_food(player_id, m_health, food.food, food.saturation);
   }
}

}// namespace minecpp::entity::component
