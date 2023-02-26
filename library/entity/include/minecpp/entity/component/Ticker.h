#pragma once
#include <entt/entt.hpp>
#include <minecpp/game/IWorld.hpp>

namespace minecpp::entity::component {

class Ticker
{
 public:
   entt::sigh<void(game::IWorld &, game::Entity &, double)> on_tick;

   void tick(game::IWorld &world, game::Entity &entity, double delta_time);
};

}// namespace minecpp::entity::component