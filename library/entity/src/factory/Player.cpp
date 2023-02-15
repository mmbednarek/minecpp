#pragma once
#include <minecpp/entity/component/Health.h>
#include <minecpp/entity/factory/Player.h>

namespace minecpp::entity::factory {

game::EntityId Player::create_entity(EntitySystem &entity_system)
{
   auto player_entity = entity_system.create_spatial_entity(m_position, {0.6, 1.8, 0.6});

   player_entity.add_component<component::Health>(20.0f);
   player_entity.add_component<component::Food>(20, 5.0f);

   return player_entity.id();
}

}// namespace minecpp::entity::factory