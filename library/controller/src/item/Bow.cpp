#include <minecpp/controller/item/Bow.h>
#include <minecpp/entity/Aliases.hpp>
#include <minecpp/entity/component/Location.h>
#include <minecpp/entity/factory/Arrow.h>

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

void Bow::on_item_use(game::IWorld &world, game::PlayerId player_id, game::EntityId player_entity_id,
                      game::ItemId item_id)
{
   auto player_entity = world.entity_system().entity(player_entity_id);
   auto &rot          = player_entity.component<RotationComponent>();

   auto dir = math::Vector3::from_yaw_and_pitch(rot.yaw(), rot.pitch());

   auto initial_position =
           player_entity.component<LocationComponent>().position() + math::Vector3{0, 1.3, 0} + dir;

   world.spawn<Arrow>(initial_position, dir * 1.5, normalize_rot(-rot.yaw()), normalize_rot(-rot.pitch()));
}

}// namespace minecpp::controller::item