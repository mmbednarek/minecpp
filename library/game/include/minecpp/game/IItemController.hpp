#pragma once

#include "Game.h"
#include "IWorld.hpp"

namespace minecpp::game {

class IItemController
{
 public:
   virtual ~IItemController() noexcept = default;

   virtual void on_item_use(IWorld &world, PlayerId player_id, EntityId player_entity_id, ItemId item_id) = 0;
};

}// namespace minecpp::game