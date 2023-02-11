#pragma once
#include "minecpp/game/player/Id.h"
#include <boost/uuid/uuid.hpp>
#include <map>
#include <minecpp/game/Notifier.h>
#include <minecpp/math/Vector3.h>
#include <minecpp/proto/entity/v1/Entity.pb.h>

namespace minecpp::nbt::player::v1 {
class Player;
}

namespace minecpp::game::entity {

using boost::uuids::uuid;
using minecpp::math::Vector3;

typedef std::string AttributeName;
typedef std::string Type;

extern std::string g_player_type;
extern std::array<std::string, 7> known_attributes;

AttributeName to_attribute_name(const std::string &s);

class Attributes
{
   std::map<AttributeName, double> attributes;

 public:
   void set_attribute(AttributeName name, double value);
};

struct Tracking
{
   int64_t x, y, z;
};

struct Movement
{
   short x, y, z;

   [[nodiscard]] inline proto::entity::v1::Movement to_proto() const
   {
      proto::entity::v1::Movement result;
      result.set_x(x);
      result.set_y(y);
      result.set_z(z);
      return result;
   }
};

class Entity
{
   uint32_t id{};
   uuid uid;
   Type type;

   Attributes attributes;
   Tracking tracking{};

   float health            = 20.0f;
   float absorption_amount = 0.0f;
   float fall_distance     = 0;

   short air        = 300;
   short death_time = 0;
   short fire       = -1;
   short hurt_time  = 0;

   bool can_pick_up_loot     = false;
   bool fall_flying          = false;
   bool hurt_by_timestamp    = false;
   bool invulnerable         = false;
   bool left_handed          = false;
   bool on_ground            = true;
   bool persistence_required = false;

   math::Vector3 motion;
   math::Vector3 pos;
   float yaw = 0.0f, pitch = 0.0f;

 public:
   Entity(uuid uid, const Type &type);

   [[nodiscard]] math::Vector3 get_pos() const;
   [[nodiscard]] float get_yaw() const;
   [[nodiscard]] float get_pitch() const;
   void set_pos(Notifier &n, math::Vector3 pos);
   void set_rot(float yaw, float pitch);
   void set_id(uint32_t id);
   uint32_t get_id();
   void damage(float value);
   [[nodiscard]] float get_health() const;

   Movement process_movement();
   void sync_tracking();

   [[nodiscard]] inline proto::entity::v1::Entity to_proto() const
   {
      proto::entity::v1::Entity entity;
      entity.set_entity_id(id);
      entity.mutable_rotation()->set_yaw(yaw);
      entity.mutable_rotation()->set_pitch(pitch);
      entity.mutable_position()->set_x(pos.x());
      entity.mutable_position()->set_y(pos.y());
      entity.mutable_position()->set_z(pos.z());
      *entity.mutable_id() = game::player::write_id_to_proto(uid);
      return entity;
   }

   static Entity from_player_nbt(const nbt::player::v1::Player &player);
};

struct Rotation
{
   float yaw, pitch;

   constexpr Rotation(float yaw, float pitch) :
       yaw(yaw),
       pitch(pitch)
   {
   }

   [[nodiscard]] inline proto::common::v1::Rotation to_proto() const
   {
      proto::common::v1::Rotation result;
      result.set_yaw(yaw);
      result.set_pitch(pitch);
      return result;
   }
};

}// namespace minecpp::game::entity
