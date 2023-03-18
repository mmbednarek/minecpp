#pragma once

#include "Location.h"
#include "Velocity.h"

#include <minecpp/game/Entity.h>
#include <minecpp/game/IWorld.hpp>
#include <minecpp/game/Team.h>

namespace minecpp::entity::component {

class Projectile
{
 public:
   explicit Projectile(game::EntityId owner, float damage);

   void on_attached(game::Entity &entity);

   void serialize_to_proto(proto::entity::v1::Entity *entity) const;
   void on_begin_intersect(game::IWorld &world, game::Entity &entity, game::Entity &other_entity);
   void on_hit_ground(game::IWorld &world, game::Entity &entity, const math::Vector3 &position) const;
   void on_velocity_change(game::IWorld &world, game::Entity &entity, const math::Vector3 &velocity) const;

   [[nodiscard]] game::EntityId owner() const;

 private:
   Location::BeginIntersect::OptSink<Projectile> m_begin_intersect_sink;
   Location::HitGround::OptSink<Projectile> m_hit_ground_sink;
   Velocity::VelocityChange::OptSink<Projectile> m_velocity_change_sink;
   int m_entity_type_id{3};
   game::EntityId m_owner;
   float m_damage{1.0f};
};

}// namespace minecpp::entity::component