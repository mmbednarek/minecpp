#include "item/Item.h"
#include "item/Bow.h"
#include "item/Food.h"
#include "item/Sword.h"
#include "minecpp/repository/Item.h"
#include "RootItem.h"

namespace minecpp::controller::item {

void register_item_controllers(RootItem &root_controller)
{
   if (auto item_id = repository::Item::the().find_id_by_tag("minecraft:bow"); item_id.ok()) {
      root_controller.register_controller<controller::item::Bow>(*item_id);
   }
   if (auto item_id = repository::Item::the().find_id_by_tag("minecraft:apple"); item_id.ok()) {
      root_controller.register_controller<controller::item::Food>(*item_id);
   }
   if (auto item_id = repository::Item::the().find_id_by_tag("minecraft:iron_sword"); item_id.ok()) {
      root_controller.register_controller<controller::item::Sword>(*item_id);
   }
}

}// namespace minecpp::controller::item