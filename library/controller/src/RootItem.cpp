#include <minecpp/controller/RootItem.h>

namespace minecpp::controller {

void RootItem::on_item_use(game::IWorld &world, game::PlayerId player_id, game::EntityId player_entity_id,
                           game::ItemId item_id)
{
   if (this->has_controller_for(item_id)) {
      this->controller(item_id).on_item_use(world, player_id, player_entity_id, item_id);
   }
}

game::IItemController &RootItem::controller(game::ItemId item_id)
{
   return *m_controllers[item_id];
}

bool RootItem::has_controller_for(game::ItemId item_id) const
{
   return m_controllers.contains(item_id);
}
}// namespace minecpp::controller
