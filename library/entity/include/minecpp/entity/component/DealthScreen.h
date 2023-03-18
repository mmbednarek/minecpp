#pragma once
#include <minecpp/entity/component/Health.h>
#include <minecpp/game/Entity.h>

namespace minecpp::entity::component {

class DeathScreen
{
 public:
   void on_attached(game::Entity &entity);
   void on_dead(game::IWorld &world, game::Entity &entity, const game::Damage &damage);
   void on_killed(game::IWorld *world, game::Entity *entity);

 private:
   [[nodiscard]] static std::string format_death_message(game::IEntitySystem &entity_system,
                                                         const game::Damage &damage);

   Health::Dead::OptSink<DeathScreen> m_dead_sink;
   bool m_displayed_death_screen = false;
};

}// namespace minecpp::entity::component
