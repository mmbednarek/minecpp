#pragma once

#include <minecpp/entity/EntitySystem.h>
#include <minecpp/game/Team.h>

namespace minecpp::entity::factory {

class Arrow : public IEntityFactory
{
 public:
   Arrow(const math::Vector3 &initial_velocity, const math::Rotation &rotation, game::EntityId owner_id,
         float damage);
   game::Entity create_entity(const math::Vector3 &position, game::IEntitySystem &entity_system) override;

 private:
   math::Vector3 m_initial_velocity;
   math::Rotation m_initial_rotation;
   game::EntityId m_owner_id;
   float m_damage{0.5f};
};

}// namespace minecpp::entity::factory