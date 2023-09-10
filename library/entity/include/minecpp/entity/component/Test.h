#pragma once
#include "Location.h"
#include "Ticker.h"
#include <minecpp/game/Entity.h>

namespace minecpp::entity::component {

class Test
{
 public:
   Test() = default;

   void tick(game::IWorld &world, game::Entity &entity, double delta_time);

   void on_attached(game::Entity &entity);
   void on_position_change(game::IWorld &world, game::Entity &entity, const math::Vector3 &old_position,
                           const math::Vector3 &new_position);

 private:
   int m_position_change_count{};
   Location::PositionChange::OptSink<Test> m_position_change_sink;
   Ticker::Tick::OptSink<Test> m_tick_sink;
};

}// namespace minecpp::entity::component
