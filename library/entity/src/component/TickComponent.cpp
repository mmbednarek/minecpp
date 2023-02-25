#include <minecpp/entity/component/TickComponent.h>

namespace minecpp::entity::component {

void TickComponent::tick(game::IWorld &world, game::Entity &entity, double delta_time)
{
   on_tick.publish(world, entity, delta_time);
}

}// namespace minecpp::entity::component
