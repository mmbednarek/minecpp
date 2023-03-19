#pragma once

#include <minecpp/entity/EntitySystem.h>
#include <minecpp/game/Team.h>

namespace minecpp::entity::factory {

class Totem : public IEntityFactory
{
 public:
   Totem(game::Team team, float initial_yaw, float initial_pitch);

   game::Entity create_entity(const math::Vector3 &position, game::IEntitySystem &entity_system) override;

 private:
   game::Team m_team;
   math::Radians m_initial_yaw;
   math::Radians m_initial_pitch;
};


}// namespace minecpp::entity::factory