#pragma once
#include <minecpp/game/Entity.h>
#include <minecpp/game/IWorld.hpp>
#include <minecpp/math/Vector3.h>

namespace minecpp::entity::component {

class Velocity
{
 public:
   explicit Velocity(const math::Vector3 &velocity);

   void on_attached(game::Entity &entity);
   void tick(game::IWorld &world, game::Entity &entity, double delta_time);
   void serialize_to_proto(proto::entity::v1::Entity *entity) const;
   void set_velocity(game::IDispatcher &dispatcher, const math::Vector3 &position,
                     const math::Vector3 &velocity);
   [[nodiscard]] const math::Vector3 &velocity() const;

 private:
   game::EntityId m_entity_id{};
   math::Vector3 m_velocity;
};

}// namespace minecpp::entity::component
