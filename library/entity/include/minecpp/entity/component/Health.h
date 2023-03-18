#pragma once
#include <minecpp/game/Delegate.hpp>
#include <minecpp/game/Entity.h>
#include <minecpp/game/Health.h>
#include <minecpp/game/IWorld.hpp>

namespace minecpp::entity::component {

constexpr game::Health g_max_health{20.0f};

class Health
{
 public:
   using Dead = game::Delegate<game::IWorld & /*world*/, game::Entity & /*entity*/,
                               const game::Damage & /*damage*/>;

   Dead on_dead;

   explicit Health(float health);

   [[nodiscard]] game::Health health() const;

   void on_attached_to_world(game::IWorld *world, game::Entity *entity, const math::Vector3 &position,
                             const math::Vector3 &extent);
   void apply_damage(game::IWorld &world, const game::Damage &damage);
   void heal(game::IWorld &world, game::Entity &entity, game::Health amount);

 private:
   game::Health m_health{g_max_health};
};

struct Food
{
   int food{};
   float saturation{};
};

}// namespace minecpp::entity::component
