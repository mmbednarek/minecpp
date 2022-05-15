#ifndef MINECPP_ENTITY_H
#define MINECPP_ENTITY_H
#include <mb/int.h>
#include <minecpp/proto/entity/v1/entity.pb.h>
#include <minecpp/util/vec.h>

namespace minecpp::entity {

using Id = mb::u32;

inline util::Vec3 read_entity_position(const proto::entity::v1::Position &pos)
{
   return util::Vec3(pos.x(), pos.y(), pos.z());
}

inline proto::entity::v1::Position write_entity_position(const util::Vec3 &pos)
{
   proto::entity::v1::Position result;
   result.set_x(pos.x);
   result.set_y(pos.y);
   result.set_z(pos.z);
   return result;
}

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

struct Rotation
{
   float yaw, pitch;

   constexpr Rotation(float yaw, float pitch) : yaw(yaw), pitch(pitch) {}

   [[nodiscard]] inline proto::entity::v1::Rotation to_proto() const
   {
      proto::entity::v1::Rotation result;
      result.set_yaw(yaw);
      result.set_pitch(pitch);
      return result;
   }
};

}// namespace minecpp::entity

#endif//MINECPP_ENTITY_H
