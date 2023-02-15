#pragma once
#include "../EntitySystem.h"
#include <minecpp/math/Vector3.h>

namespace minecpp::entity::factory {

class Player : public IEntityFactory
{
 public:
   game::EntityId create_entity(EntitySystem &entity_system) override;

 private:
   math::Vector3 m_position;
   game::PlayerId m_player_id;
};

}// namespace minecpp::entity::factory