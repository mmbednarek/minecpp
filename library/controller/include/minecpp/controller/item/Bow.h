#pragma once

#include "Default.h"

namespace minecpp::game {
class Entity;
}

namespace minecpp::controller::item {

class Bow : public Default
{
 public:
   void on_item_use(game::IWorld &world, game::PlayerId player_id, game::EntityId player_entity_id,
                    game::ItemId item_id) override;
   void on_released_item(game::IWorld &world, game::ItemId item_id, game::EntityId player_entity_id) override;

 private:
   static void fire(game::IWorld &world, game::Entity &player_entity, double strength);
};

}// namespace minecpp::controller::item