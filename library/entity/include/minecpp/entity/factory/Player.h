#pragma once
#include "../EntitySystem.h"
#include <minecpp/math/Vector3.h>

namespace minecpp::entity::factory {

class Player : public IEntityFactory
{
 public:
   Player(const math::Vector3 &position, const game::PlayerId &player_id, std::string name);

   game::Entity create_entity(EntitySystem &entity_system) override;

 private:
   math::Vector3 m_position;
   game::PlayerId m_player_id;
   std::string m_name;
};

}// namespace minecpp::entity::factory