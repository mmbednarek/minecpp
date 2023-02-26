#include <minecpp/entity/factory/Arrow.h>
#include <minecpp/controller/item/Bow.h>
#include <minecpp/entity/PlayerComponents.hpp>

namespace minecpp::controller::item {

using minecpp::entity::factory::Arrow;

void Bow::on_item_use(game::IWorld &world, game::PlayerId player_id, game::EntityId player_entity_id,
                      game::ItemId item_id)
{
   auto player_entity = world.entity_system().entity(player_entity_id);
   auto &rot          = player_entity.component<RotationComponent>();

   auto dir = math::Vector3::from_yaw_and_pitch(rot.yaw(), rot.pitch());
   dir.set_y(0.5);

   world.spawn<Arrow>(player_entity.component<LocationComponent>().position() + math::Vector3{0, 2.0, 0} - dir, dir);
}
}// namespace minecpp::controller::item