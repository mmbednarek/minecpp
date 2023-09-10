#pragma once

#include "Ticker.h"

#include "minecpp/game/Delegate.hpp"
#include "minecpp/game/Entity.h"
#include "minecpp/game/EntityData.hpp"
#include "minecpp/game/IWorld.hpp"
#include "minecpp/math/Vector3.h"

namespace minecpp::entity::component {

class Velocity
{
 public:
   using VelocityChange = game::Delegate<game::IWorld & /*world*/, game::Entity & /*entity*/,
                                         const math::Vector3 & /*velocity*/>;
   VelocityChange on_velocity_change;

   explicit Velocity(const math::Vector3 &velocity);

   void on_attached(game::Entity &entity);
   void tick(game::IWorld &world, game::Entity &entity, double delta_time);
   void serialize_to_net(game::NetworkEntity *net_entity) const;
   void set_velocity(game::IWorld &world, game::Entity &entity, const math::Vector3 &velocity);
   [[nodiscard]] const math::Vector3 &velocity() const;

 private:
   Ticker::Tick::OptSink<Velocity> m_tick_sink;
   game::EntityId m_entity_id{};
   math::Vector3 m_velocity;
};

}// namespace minecpp::entity::component
