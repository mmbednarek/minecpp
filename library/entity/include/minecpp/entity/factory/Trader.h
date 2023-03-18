#pragma once

#include <minecpp/entity/EntitySystem.h>

namespace minecpp::entity::factory {

class Trader : public IEntityFactory
{
 public:
   Trader(float initial_yaw, float initial_pitch);

   game::Entity create_entity(const math::Vector3 &position, game::IEntitySystem &entity_system) override;

 private:
   math::Radians m_initial_yaw;
   math::Radians m_initial_pitch;
};

}// namespace minecpp::entity::factory
