#include <minecpp/controller/item/Item.h>
#include <minecpp/controller/item/Bow.h>
#include <minecpp/controller/item/Food.h>
#include <minecpp/controller/item/Sword.h>
#include "minecpp/repository/Item.h"
#include <minecpp/controller/RootItem.h>

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