#include <minecpp/entity/component/Inventory.h>
#include <minecpp/entity/component/Player.h>
#include <minecpp/entity/component/Team.h>
#include <minecpp/entity/component/Trader.h>
#include <minecpp/repository/Item.h>

namespace minecpp::entity::component {

void Trader::serialize_to_proto(proto::entity::v1::Entity *entity) const
{
   entity->set_entity_type(m_entity_type_id);
}

void Trader::on_interact(game::IWorld &world, game::Entity &self, game::Entity &other)
{
   if (not other.has_component<Player>())
      return;

   assert(other.has_component<Inventory>());
   assert(other.has_component<Team>());
   auto &inventory = other.component<Inventory>();

   auto apple_id = repository::Item::the().lookup_id("minecraft:apple");
   assert(apple_id.ok());

   auto arrow_id = repository::Item::the().lookup_id("minecraft:arrow");
   assert(arrow_id.ok());

   auto &team        = other.component<Team>();
   int apples_to_add = team.used_apple_count();
   int arrows_to_add = team.used_arrow_count();

   if (apples_to_add != 0) {
      other.component<Inventory>().add_item(world.dispatcher(), *apple_id, apples_to_add);
   }
   if (arrows_to_add != 0) {
      other.component<Inventory>().add_item(world.dispatcher(), *arrow_id, arrows_to_add);
   }

   team.reset_counters();
}

}// namespace minecpp::entity::component