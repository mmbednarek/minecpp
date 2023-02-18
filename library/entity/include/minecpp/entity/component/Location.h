#pragma once
#include <entt/entt.hpp>
#include <minecpp/game/Entity.h>
#include <minecpp/game/World.h>
#include <minecpp/math/Vector3.h>
#include <minecpp/proto/entity/v1/Entity.pb.h>

namespace minecpp::entity::component {

struct TrackedPosition
{
   math::Vector3l position;

   void apply_movement(const game::Movement &movement);

   [[nodiscard]] static TrackedPosition from_vector3(const math::Vector3 &position);
   [[nodiscard]] math::Vector3 to_vector3() const;
};

class Location
{
 public:
   entt::delegate<void(game::World &world, game::Entity &entity, const math::Vector3 &, const math::Vector3 &)> on_position_change;

   Location(const math::Vector3 &position, const math::Vector3 &extent);

   [[nodiscard]] math::Vector3 position() const;
   [[nodiscard]] math::Vector3 extent() const;

   void set_position(game::World &world, game::Entity &entity, const math::Vector3 &position);

   void serialize_to_proto(proto::entity::v1::Entity *entity) const;

 private:
   math::Vector3 m_position{};
   math::Vector3 m_extent{};
   TrackedPosition m_tracked_position{};
};

class Rotation
{
 public:
   Rotation(float yaw, float pitch);

   void serialize_to_proto(proto::entity::v1::Entity *entity) const;

   [[nodiscard]] game::Rotation rotation() const;
   [[nodiscard]] float yaw() const;
   [[nodiscard]] float pitch() const;
   void set_yaw(float yaw);
   void set_pitch(float pitch);

 private:
   float m_yaw{};
   float m_pitch{};
};

}// namespace minecpp::entity::component