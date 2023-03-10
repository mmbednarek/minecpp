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
      world.dispatcher().animate_entity(damage.target_entity, entity.component<Location>().position(),
                                        game::EntityAnimation::TakeDamage);
      if (killed) {
         world.dispatcher().animate_entity(damage.target_entity, entity.component<Location>().position(),
                                           game::EntityAnimation::CriticalEffect);
      }
   }

   if (entity.has_component<Player>()) {
      assert(entity.has_component<Food>());

      const auto player_id = entity.component<Player>().id();
      const auto &food     = entity.component<Food>();

      world.dispatcher().set_health_and_food(player_id, target_health, food.food, food.saturation);

      if (killed) {
         auto msg = this->format_death_message(world.entity_system(), damage);
         world.dispatcher().display_death_screen(player_id, damage.target_entity,
                                                 damage.source_entity.value_or(-1), msg);
         world.dispatcher().send_chat(chat::MessageType::PlayerMessage, msg);
      }
   }

   if (entity.has_component<Velocity>()) {
      assert(entity.has_component<Location>());
      auto &velocity = entity.component<Velocity>();
      velocity.set_velocity(world.dispatcher(), entity.component<Location>().position(), damage.vector);
   }

   m_health = target_health;

   if (killed) {
      world.kill_entity(damage.target_entity);
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

std::string Health::format_death_message(game::IEntitySystem &entity_system, const game::Damage &damage) const
{
   format::Builder builder;

   if (not damage.source_entity.has_value())
      return builder.to_string();

   auto source_entity = entity_system.entity(*damage.source_entity);
   auto target_entity = entity_system.entity(damage.target_entity);

   auto &player = target_entity.component<Player>();

   builder.bold(format::Color::Yellow, player.name());

   switch (damage.source.value()) {
   case game::DamageSourceValue::PlayerAttack: {
      builder.text(" has been slain by ");
      if (source_entity.has_component<Player>()) {
         builder.bold(format::Color::Yellow, source_entity.component<Player>().name());
      }
   } break;
   case game::DamageSourceValue::Projectile: {
      builder.text(" has been shot to death by ");
      if (source_entity.has_component<Projectile>()) {
         auto projectile_owner = entity_system.entity(source_entity.component<Projectile>().owner());
         if (projectile_owner.has_component<Player>()) {
            builder.bold(format::Color::Yellow, projectile_owner.component<Player>().name());
         }
      }
   } break;
   default: break;
   }

   return builder.to_string();
}

}// namespace minecpp::entity::component
