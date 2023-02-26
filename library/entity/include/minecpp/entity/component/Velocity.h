#pragma once
#include <minecpp/game/Entity.h>
#include <minecpp/game/IWorld.hpp>
#include <minecpp/math/Vector3.h>

namespace minecpp::entity::component {

class Velocity
{
 public:
   explicit Velocity(const math::Vector3 &velocity);
   Velocity(const math::Vector3 &velocity, bool is_on_ground);

   void on_attached(game::Entity &entity);
   void tick(game::IWorld &world, game::Entity &entity, double delta_time);
   void serialize_to_proto(proto::entity::v1::Entity *entity) const;
   void set_falling();
   void set_velocity(game::IDispatcher &dispatcher, const math::Vector3 &position,
                     const math::Vector3 &velocity);

 private:
   game::EntityId m_entity_id{};
   math::Vector3 m_velocity;
   bool m_is_on_ground{false};
};

}// namespace minecpp::entity::component
