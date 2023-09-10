#pragma once

#include <mb/int.h>
#include <minecpp/game/Entity.h>
#include <minecpp/game/IWorld.hpp>

namespace minecpp::entity::component {

class Trader
{
 public:
   void on_interact(game::IWorld &world, game::Entity &self, game::Entity &other);
};

}// namespace minecpp::entity::component