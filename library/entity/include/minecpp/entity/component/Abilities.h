#pragma once
#include "../Abilities.h"
#include <minecpp/proto/entity/v1/Entity.pb.h>

namespace minecpp::entity::component {

struct Abilities
{
   entity::Abilities abilities;

   void serialize_to_proto(proto::entity::v1::Entity *entity) const;
};

}// namespace minecpp::entity::component
