#pragma once

#include "Game.h"
#include "IWorld.hpp"

namespace minecpp::game {

class IItemController
{
 public:
   virtual ~IItemController() noexcept = default;

   virtual void on_item_use(IWorld &world, PlayerId player_id, EntityId player_entity_id, ItemId item_id) = 0;
   virtual void on_interact(IWorld &world, ItemId item_id, InteractionType interaction_type,
                            EntityId player_entity_id, EntityId interaction_entity_id,
                            const math::Vector3f &position, bool is_offhand)                              = 0;
   virtual void on_released_item(IWorld &world, ItemId item_id, EntityId player_entity_id)                = 0;
};

}// namespace minecpp::game