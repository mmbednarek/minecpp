#pragma once

#include "minecpp/game/Delegate.hpp"
#include "minecpp/game/Entity.h"
#include "minecpp/game/EntityData.hpp"
#include "minecpp/game/Entt.hpp"
#include "minecpp/game/IWorld.hpp"
#include "minecpp/math/Rotation.h"
#include "minecpp/math/Vector3.h"
#include "minecpp/proto/entity/Entity.pb.h"

#include <mutex>
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
   using PositionChange =
           game::Delegate<game::IWorld & /*world*/, game::Entity & /*entity*/,
                          const math::Vector3 & /*old_position*/, const math::Vector3 & /*new_position*/>;

   using BeginIntersect = game::Delegate<game::IWorld & /*world*/, game::Entity & /*entity*/,
                                         game::Entity & /*other_entity*/>;

   using HitGround = game::Delegate<game::IWorld & /*world*/, game::Entity & /*entity*/,
                                    const math::Vector3 & /*position*/>;

   PositionChange on_position_change;
   BeginIntersect on_begin_intersect;
   HitGround on_hit_ground;

   Location(const math::Vector3 &position, const math::Vector3 &extent);

   [[nodiscard]] math::Vector3 position() const;
   [[nodiscard]] math::Vector3 logical_position() const;
   [[nodiscard]] math::Vector3 extent() const;
   [[nodiscard]] bool is_on_ground() const;

   void on_killed(game::IWorld *world, game::Entity *entity);
   void reset_position_and_extent(const math::Vector3 &position, const math::Vector3 &extent);

   void set_position(game::IWorld &world, game::Entity &entity, const math::Vector3 &position,
                     bool is_on_ground);
   void teleport_player(game::IWorld &world, game::Entity &entity, const math::Vector3 &position);
   void set_is_on_ground(game::IWorld &world, game::Entity &entity, bool is_on_ground);

   void serialize_to_proto(proto::entity::Entity *entity) const;
   void serialize_player_to_proto(proto::entity::PlayerEntity *entity) const;

   void serialize_to_net(game::NetworkEntity *net_entity) const;
   void serialize_to_net_player(game::NetworkPlayer *net_player) const;


 private:
   math::Vector3l set_logical_position(game::IWorld &world, game::EntityId entity_id,
                                       const math::Vector3 &position);

   math::Vector3 m_position{};
   math::Vector3 m_extent{};
   TrackedPosition m_tracked_position{};
   std::set<game::EntityId> m_entities_intersecting_with;
   bool m_is_detached{false};
   int m_refresh_count{0};
   bool m_is_on_ground{false};
   std::mutex m_mutex;
};

class Rotation
{
 public:
   Rotation(math::Radians yaw, math::Radians pitch);
   explicit Rotation(const math::Rotation &rotation);

   void on_attached(game::Entity &entity);

   void serialize_to_proto(proto::entity::Entity *entity) const;
   void serialize_player_to_proto(proto::entity::PlayerEntity *entity) const;

   [[nodiscard]] math::Rotation rotation() const;
   [[nodiscard]] math::Degrees yaw_degrees() const;
   [[nodiscard]] math::Degrees pitch_degrees() const;
   void set_yaw_degrees(math::Degrees yaw);
   void set_pitch_degrees(math::Degrees pitch);

   [[nodiscard]] math::Radians yaw() const;
   [[nodiscard]] math::Radians pitch() const;
   void set_yaw(math::Radians yaw);
   void set_pitch(math::Radians pitch);
   void set_rotation(game::IDispatcher &dispatcher, const math::Vector3 &position,
                     const math::Rotation &rotation);

   void serialize_to_net(game::NetworkEntity *net_entity) const;
   void serialize_to_net_player(game::NetworkPlayer *net_player) const;

 private:
   math::Rotation m_rotation{};
   game::EntityId m_entity_id{};
};

}// namespace minecpp::entity::component