#pragma once

#include "Default.h"

namespace minecpp::controller::item {

class Food : public Default
{
 public:
   void on_item_use(game::IWorld &world, game::PlayerId player_id, game::EntityId player_entity_id,
                    game::ItemId item_id) override;
};

}// namespace minecpp::controller::item