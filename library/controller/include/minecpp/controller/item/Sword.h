#pragma once

#include "Default.h"

namespace minecpp::controller::item {

class Sword : public Default
{
 public:
   void on_interact(game::IWorld &world, game::ItemId item_id, game::InteractionType interaction_type,
                    game::EntityId player_entity_id, game::EntityId interaction_entity_id,
                    const math::Vector3f &position, bool is_offhand) override;
};

}// namespace minecpp::controller::item
