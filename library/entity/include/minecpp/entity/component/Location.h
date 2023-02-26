#pragma once
#include <entt/entt.hpp>
#include <minecpp/game/Entity.h>
#include <minecpp/game/IWorld.hpp>
#include <minecpp/math/Rotation.h>
#include <minecpp/math/Vector3.h>
#include <minecpp/proto/entity/v1/Entity.pb.h>
#include <set>

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
   entt::sigh<void(game::IWorld &world, game::Entity &entity, const math::Vector3 &, const math::Vector3 &)>
           on_position_change;
   entt::sigh<void(game::IWorld &world, game::Entity &entity, game::Entity &other_entity)> on_begin_intersect;

   Location(const math::Vector3 &position, const math::Vector3 &extent);

   [[nodiscard]] math::Vector3 position() const;
   [[nodiscard]] math::Vector3 logical_position() const;
   [[nodiscard]] math::Vector3 extent() const;

   void set_position(game::IWorld &world, game::Entity &entity, const math::Vector3 &position);

   void serialize_to_proto(proto::entity::v1::Entity *entity) const;
   void serialize_player_to_proto(proto::entity::v1::PlayerEntity *entity) const;

 private:
   math::Vector3 m_position{};
   math::Vector3 m_extent{};
   TrackedPosition m_tracked_position{};
   std::set<game::EntityId> m_entities_intersecting_with;
};

class Rotation
{
 public:
   Rotation(float yaw, float pitch);

   void on_attached(game::Entity &entity);

   void serialize_to_proto(proto::entity::v1::Entity *entity) const;
   void serialize_player_to_proto(proto::entity::v1::PlayerEntity *entity) const;

   [[nodiscard]] game::Rotation rotation() const;
   [[nodiscard]] math::Degrees yaw_degrees() const;
   [[nodiscard]] math::Degrees pitch_degrees() const;
   void set_yaw_degrees(math::Degrees yaw);
   void set_pitch_degrees(math::Degrees pitch);

   [[nodiscard]] math::Radians yaw() const;
   [[nodiscard]] math::Radians pitch() const;
   void set_yaw(math::Radians yaw);
   void set_pitch(math::Radians pitch);
   void set_rotation(game::IDispatcher &dispatcher, const math::Vector3 &position, math::Radians yaw,
                     math::Radians pitch);

 private:
   math::Radians m_yaw{};
   math::Radians m_pitch{};
   game::EntityId m_entity_id{};
};

}// namespace minecpp::entity::component