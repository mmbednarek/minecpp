#pragma once
#include <minecpp/math/Vector3.h>
#include <minecpp/proto/entity/v1/Entity.pb.h>

namespace minecpp::entity::component {

struct Location
{
   math::Vector3 position{};
   math::Vector3 extent{};

   void serialize_to_proto(proto::entity::v1::Entity *entity) const;
};

struct Rotation
{
   float yaw{};
   float pitch{};

   void serialize_to_proto(proto::entity::v1::Entity *entity) const;
};

}// namespace minecpp::entity::component