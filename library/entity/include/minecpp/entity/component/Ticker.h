#pragma once
#include <minecpp/game/Delegate.hpp>
#include <minecpp/game/Entt.hpp>
#include <minecpp/game/IWorld.hpp>

namespace minecpp::game {
class Entity;
}

namespace minecpp::entity::component {

class Ticker
{
 public:
   using Tick = game::Delegate<game::IWorld & /*world*/, game::Entity & /*entity*/, double /*delta_time*/>;
   Tick on_tick;

   void tick(game::IWorld &world, game::Entity &entity, double delta_time);
};

}// namespace minecpp::entity::component