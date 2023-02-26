#pragma once

#include <minecpp/game/Entity.h>

namespace minecpp::entity::component {

class Projectile
{
 public:
   void serialize_to_proto(proto::entity::v1::Entity *entity) const;

 private:
   int m_entity_type_id{3};
};

}// namespace minecpp::entity::component