#pragma once
#include <minecpp/entity/component/Abilities.h>
#include <minecpp/entity/component/Health.h>
#include <minecpp/entity/component/Inventory.h>
#include <minecpp/entity/component/Location.h>
#include <minecpp/entity/component/Player.h>
#include <minecpp/entity/component/StreamingComponent.h>
#include <minecpp/entity/component/Test.h>
#include <minecpp/entity/factory/Player.h>

namespace minecpp::entity::factory {

Player::Player(const math::Vector3 &position, const game::PlayerId &player_id, std::string name) :
    m_position(position),
    m_player_id(player_id),
    m_name(std::move(name))
{
}

game::Entity Player::create_entity(EntitySystem &entity_system)
{
   auto player_entity = entity_system.create_spatial_entity(m_position, {0.6, 1.8, 0.6});

   player_entity.add_component<component::Player>(m_player_id, m_name);
   player_entity.add_component<component::Rotation>(0.0f, 0.0f);
   player_entity.add_component<component::Health>(20.0f);
   player_entity.add_component<component::Food>(20, 5.0f);
   player_entity.add_component<component::Abilities>(Abilities{});
   player_entity.add_component<component::StreamingComponent>(
           static_cast<int>(entity_system.view_distance()));
   player_entity.add_component<component::Inventory>();

   return player_entity;
}

}// namespace minecpp::entity::factory