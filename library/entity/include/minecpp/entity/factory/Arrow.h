#pragma once

#include "minecpp/entity/EntitySystem.h"

namespace minecpp::entity::factory {

class Arrow : public IEntityFactory
{
 public:
   explicit Arrow(const math::Vector3 &initial_velocity);

   game::Entity create_entity(const math::Vector3 &position, game::IEntitySystem &entity_system) override;

 private:
   math::Vector3 m_initial_velocity;
};

}// namespace minecpp::entity::factory