#pragma once
#include "../EntitySystem.h"
#include <minecpp/game/Team.h>
#include <minecpp/math/Vector3.h>

namespace minecpp::entity::factory {

class Player : public IEntityFactory
{
 public:
   Player(const game::PlayerId &player_id, std::string name);

   game::Entity create_entity(const math::Vector3 &position, game::IEntitySystem &entity_system) override;

 private:
   game::PlayerId m_player_id;
   std::string m_name;
};

}// namespace minecpp::entity::factory