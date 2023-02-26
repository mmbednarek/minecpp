#include <minecpp/entity/component/Ticker.h>

namespace minecpp::entity::component {

void Ticker::tick(game::IWorld &world, game::Entity &entity, double delta_time)
{
   on_tick.publish(world, entity, delta_time);
}

}// namespace minecpp::entity::component
