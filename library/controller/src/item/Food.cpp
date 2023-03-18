#include <minecpp/controller/item/Food.h>
#include <minecpp/entity/Aliases.hpp>
#include <minecpp/entity/component/Health.h>
#include <minecpp/entity/component/Inventory.h>
#include <minecpp/game/IEntitySystem.hpp>

namespace minecpp::controller::item {

void Food::on_item_use(game::IWorld &world, game::PlayerId /*player_id*/, game::EntityId player_entity_id,
                       game::ItemId /*item_id*/)
{
   auto entity = world.entity_system().entity(player_entity_id);
   if (not entity.has_component<HealthComponent>())
      return;

   auto &health = entity.component<HealthComponent>();
   if (health.health() == entity::component::g_max_health)
      return;

   health.heal(world, entity, 2.0f);

   assert(entity.has_component<InventoryComponent>());
   auto &inventory = entity.component<InventoryComponent>();

   inventory.take_from_active_slot(world.dispatcher(), 1);
}

}// namespace minecpp::controller::item
