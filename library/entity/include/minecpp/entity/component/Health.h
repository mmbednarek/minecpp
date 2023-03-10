#pragma once
#include <minecpp/game/Entity.h>
#include <minecpp/game/Health.h>
#include <minecpp/game/IWorld.hpp>

namespace minecpp::entity::component {

class Health
{
 public:
   explicit Health(float health);

   [[nodiscard]] game::Health health() const;

   void on_attached_to_world(game::IWorld *world, game::Entity *entity, const math::Vector3 &position,
                             const math::Vector3 &extent);
   void apply_damage(game::IWorld &world, const game::Damage &damage);
   [[nodiscard]] std::string format_death_message(game::IEntitySystem &entity_system,
                                                  const game::Damage &damage) const;

 private:
   game::Health m_health{20.0f};
};

struct Food
{
   int food{};
   float saturation{};
};

}// namespace minecpp::entity::component
