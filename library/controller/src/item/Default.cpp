#include <minecpp/controller/item/Default.h>

namespace minecpp::controller::item {

void Default::on_item_use(game::IWorld & /*world*/, game::PlayerId /*player_id*/,
                          game::EntityId /*player_entity_id*/, game::ItemId /*item_id*/)
{
}

void Default::on_interact(minecpp::game::IWorld & /*world*/, game::ItemId /*item_id*/,
                          game::InteractionType /*interaction_type*/, game::EntityId /*player_entity_id*/,
                          game::EntityId /*interaction_entity_id*/, const math::Vector3f & /*position*/,
                          bool /*is_offhand*/)
{
}

void Default::on_released_item(game::IWorld &world, game::ItemId item_id, game::EntityId player_entity_id) {}

}// namespace minecpp::controller::item
