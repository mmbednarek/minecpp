#include <minecpp/entity/component/Abilities.h>
#include <minecpp/entity/component/DealthScreen.h>
#include <minecpp/entity/component/Health.h>
#include <minecpp/entity/component/Inventory.h>
#include <minecpp/entity/component/Location.h>
#include <minecpp/entity/component/Player.h>
#include <minecpp/entity/component/Streamer.h>
#include <minecpp/entity/component/Team.h>
#include <minecpp/entity/component/Test.h>
#include <minecpp/entity/component/Ticker.h>
#include <minecpp/entity/component/Velocity.h>
#include <minecpp/entity/factory/Player.h>

namespace minecpp::entity::factory {

Player::Player(const game::PlayerId &player_id, std::string name) :
    m_player_id(player_id),
    m_name(std::move(name))
{
}

game::Entity Player::create_entity(const math::Vector3 &position, game::IEntitySystem &entity_system)
{
   auto player_entity = entity_system.create_spatial_entity(position, {0.6, 1.8, 0.6});

   player_entity.add_component<component::Player>(m_player_id, m_name);
   player_entity.add_component<component::Ticker>();
   player_entity.add_component<component::Rotation>(0.0f, 0.0f);
   player_entity.add_component<component::Health>(20.0f);
   player_entity.add_component<component::Food>(20, 5.0f);
   player_entity.add_component<component::Abilities>();
   player_entity.add_component<component::Streamer>(static_cast<int>(entity_system.view_distance()));
   player_entity.add_component<component::Inventory>();
   player_entity.add_component<component::Velocity>(math::Vector3{0, 0, 0});
   player_entity.add_component<component::DeathScreen>();

   return player_entity;
}

}// namespace minecpp::entity::factory