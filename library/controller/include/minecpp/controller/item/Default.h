#pragma once

#include <minecpp/game/IItemController.hpp>

namespace minecpp::controller::item {

class Default : public game::IItemController
{
 public:
   void on_item_use(game::IWorld &world, game::PlayerId player_id, game::EntityId player_entity_id,
                    game::ItemId item_id) override;
   void on_interact(game::IWorld &world, game::ItemId item_id, game::InteractionType interaction_type,
                    game::EntityId player_entity_id, game::EntityId interaction_entity_id,
                    const math::Vector3f &position, bool is_offhand) override;
   void on_released_item(game::IWorld &world, game::ItemId item_id, game::EntityId player_entity_id) override;
};

}// namespace minecpp::controller::item