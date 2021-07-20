#ifndef MINECPP_ENTITY_H
#define MINECPP_ENTITY_H
#include <mb/int.h>
#include <minecpp/proto/entity/v1/entity.pb.h>
#include <minecpp/util/vec.h>

namespace minecpp::entity {

using Id = mb::u32;

constexpr util::Vec3 read_entity_position(const proto::entity::v1::Position &pos) {
   return util::Vec3(pos.x(), pos.y(), pos.z());
}

inline proto::entity::v1::Position write_entity_position(const util::Vec3 &pos) {
   proto::entity::v1::Position result;
   result.set_x(pos.x);
   result.set_y(pos.y);
   result.set_z(pos.z);
   return result;
}

}

#endif//MINECPP_ENTITY_H
