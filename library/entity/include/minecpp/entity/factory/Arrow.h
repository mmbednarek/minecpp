#pragma once

#include "minecpp/entity/EntitySystem.h"

namespace minecpp::entity::factory {

class Arrow : public IEntityFactory
{
 public:
   Arrow(const math::Vector3 &initial_velocity, float initial_yaw, float initial_pitch);
   game::Entity create_entity(const math::Vector3 &position, game::IEntitySystem &entity_system) override;

 private:
   math::Vector3 m_initial_velocity;
   math::Radians m_initial_yaw;
   math::Radians m_initial_pitch;
};

}// namespace minecpp::entity::factory