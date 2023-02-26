#pragma once
#include <minecpp/game/Entity.h>
#include <minecpp/util/Uuid.h>

namespace minecpp::entity::component {

class UniqueId
{
 public:
   UniqueId();

   void serialize_to_proto(proto::entity::v1::Entity *entity) const;

 private:
   util::uuid m_id;
};

}// namespace minecpp::entity::component