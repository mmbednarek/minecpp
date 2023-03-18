#include <minecpp/entity/component/DealthScreen.h>
#include <minecpp/entity/component/Location.h>
#include <minecpp/entity/component/Player.h>
#include <minecpp/entity/component/Projectile.h>

namespace minecpp::entity::component {

void DeathScreen::on_attached(game::Entity &entity)
{
   assert(entity.has_component<Health>());
   auto &health = entity.component<Health>();
   health.on_dead.connect_to<&DeathScreen::on_dead>(m_dead_sink, this);
}

void DeathScreen::on_dead(game::IWorld &world, game::Entity &entity, const game::Damage &damage)
{
   assert(entity.has_component<Player>());

   auto msg = DeathScreen::format_death_message(world.entity_system(), damage);
   world.dispatcher().display_death_screen(entity.component<Player>().id(), damage.target_entity,
                                           damage.source_entity.value_or(-1), msg);
   world.dispatcher().send_chat(chat::MessageType::PlayerMessage, msg);
   m_displayed_death_screen = true;
}

void DeathScreen::on_killed(game::IWorld *world, game::Entity *entity)
{
   using format::Color;

   assert(world);
   assert(entity);

   if (m_displayed_death_screen) {
      m_displayed_death_screen = false;
      return;
   }

   assert(entity->has_component<Player>());

   auto msg = format::Builder()
                      .bold(Color::Yellow, entity->component<Player>().name())
                      .text(" died from unknown causes")
                      .to_string();
   world->dispatcher().display_death_screen(entity->component<Player>().id(), entity->id(),
                                            static_cast<game::EntityId>(-1), msg);
   world->dispatcher().send_chat(chat::MessageType::PlayerMessage, msg);


   m_displayed_death_screen = false;
}

std::string DeathScreen::format_death_message(game::IEntitySystem &entity_system, const game::Damage &damage)
{
   using format::Color;
   format::Builder builder;

   auto target_entity = entity_system.entity(damage.target_entity);
   auto &player       = target_entity.component<Player>();

   builder.bold(Color::Yellow, player.name());

   if (damage.source_entity.has_value()) {
      auto source_entity = entity_system.entity(*damage.source_entity);

      switch (damage.source.value()) {
      case game::DamageSourceValue::PlayerAttack: {
         if (not damage.source_entity.has_value())
            return builder.to_string();
         builder.text(" has been slain by ");
         if (source_entity.has_component<Player>()) {
            builder.bold(Color::Yellow, source_entity.component<Player>().name());
         }
      } break;
      case game::DamageSourceValue::Projectile: {
         if (not damage.source_entity.has_value())
            return builder.to_string();
         builder.text(" has been shot to death by ");
         if (source_entity.has_component<Projectile>()) {
            auto projectile_owner = entity_system.entity(source_entity.component<Projectile>().owner());
            if (projectile_owner.has_component<Player>()) {
               builder.bold(Color::Yellow, projectile_owner.component<Player>().name());
            }
         }
      } break;
      case game::DamageSourceValue::CommandKill: {
         if (source_entity.id() == target_entity.id()) {
            builder.text(" committed a sudoku");
         } else {
            builder.text(" is a victim of ");
            if (source_entity.has_component<Player>()) {
               builder.bold(Color::Yellow, source_entity.component<Player>().name());
            }
            builder.text("'s killing command");
         }
      } break;
      default: break;
      }
   } else {
      switch (damage.source.value()) {
      case game::DamageSourceValue::VoidDamage: {
         builder.text(" has fallen into void");
      } break;
      case game::DamageSourceValue::CommandKill: {
         builder.text(" fell out of admin's favor");
      } break;
      default: break;
      }
   }


   return builder.to_string();
}

}// namespace minecpp::entity::component
