#pragma once
#include <entt/entt.hpp>
#include <minecpp/game/IWorld.h>

namespace minecpp::entity::component {

class TickComponent
{
 public:
   entt::sigh<void(game::IWorld &, game::Entity &, double)> on_tick;

   void tick(game::IWorld &world, game::Entity &entity, double delta_time);
};

}