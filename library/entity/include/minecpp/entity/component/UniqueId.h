#pragma once

#include "minecpp/game/Entity.h"
#include "minecpp/game/EntityData.hpp"
#include "minecpp/util/Uuid.h"

namespace minecpp::entity::component {

class UniqueId
{
 public:
   UniqueId();

   void serialize_to_net(game::NetworkEntity *net_entity) const;

 private:
   util::Uuid m_id;
};

}// namespace minecpp::entity::component