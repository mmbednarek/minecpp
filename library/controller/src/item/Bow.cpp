#include <minecpp/controller/item/Bow.h>
#include <minecpp/entity/Aliases.hpp>
#include <minecpp/entity/component/Inventory.h>
#include <minecpp/entity/component/Location.h>
#include <minecpp/entity/component/Player.h>
#include <minecpp/entity/component/Team.h>
#include <minecpp/entity/factory/Arrow.h>
#include <minecpp/math/Math.h>
#include <minecpp/repository/Item.h>

namespace minecpp::controller::item {

using minecpp::entity::factory::Arrow;

math::Radians normalize_rot(math::Radians rot)
{
   while (rot > 2 * math::g_pi) {
      rot -= 2 * math::g_pi;
   }
   while (rot < 0.0f) {
      rot += 2 * math::g_pi;
   }
   return rot;
}

void Bow::on_item_use(game::IWorld &world, game::PlayerId /*player_id*/, game::EntityId player_entity_id,
                      game::ItemId /*item_id*/)
{
   auto player_entity = world.entity_system().entity(player_entity_id);
   assert(player_entity.has_component<PlayerComponent>());

   player_entity.component<PlayerComponent>().begin_use_item();
}

void Bow::on_released_item(game::IWorld &world, game::ItemId /*item_id*/, game::EntityId player_entity_id)
{
   using std::chrono::duration_cast;
   using std::chrono::milliseconds;

   auto player_entity = world.entity_system().entity(player_entity_id);
   assert(player_entity.has_component<PlayerComponent>());

   const auto duration = player_entity.component<PlayerComponent>().end_use_item();
   const auto count    = math::crop(duration_cast<milliseconds>(duration).count(), 0l, 1000l);

   Bow::fire(world, player_entity, static_cast<double>(count) / 1000.0);
}

void Bow::fire(game::IWorld &world, game::Entity &player_entity, double strength)
{
   assert(player_entity.has_component<InventoryComponent>());

   auto arrow_id = repository::Item::the().lookup_id("minecraft:arrow");
   assert(arrow_id.ok());

   auto &inventory = player_entity.component<InventoryComponent>();
   if (inventory.take_item(world.dispatcher(), *arrow_id, 1) != 1)
      return;

   const auto rotation       = player_entity.component<RotationComponent>().rotation();
   const auto direction      = rotation.vector3<double>();
   const auto velocity_value = math::lerp(strength, 0.75, 3.0);
   const auto damage_value   = math::lerp(static_cast<float>(strength), 1.0f, 7.0f);

   auto initial_position =
           player_entity.component<LocationComponent>().position() + math::Vector3{0, 1.6, 0} + direction;

   world.spawn<Arrow>(initial_position, direction * velocity_value, rotation.reverse(), player_entity.id(),
                      damage_value);

   player_entity.component<PlayerComponent>().begin_use_item();
}

}// namespace minecpp::controller::item