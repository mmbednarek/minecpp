#pragma once
#include <minecpp/entity/component/Location.h>
#include <minecpp/entity/component/Ticker.h>
#include <minecpp/entity/component/Totem.h>
#include <minecpp/entity/component/UniqueId.h>
#include <minecpp/entity/component/Velocity.h>
#include <minecpp/entity/factory/Totem.h>

namespace minecpp::entity::factory {

Totem::Totem(game::Team team, float initial_yaw, float initial_pitch) :
    m_team{team},
    m_initial_yaw{initial_yaw},
    m_initial_pitch{initial_pitch}
{
}

game::Entity Totem::create_entity(const math::Vector3 &position, game::IEntitySystem &entity_system)
{
   auto totem_entity = entity_system.create_spatial_entity(position, {0.9, 1.3, 0.9});

   totem_entity.add_component<component::UniqueId>();
   totem_entity.add_component<component::Rotation>(m_initial_yaw, m_initial_pitch);
   totem_entity.add_component<component::Ticker>();
   totem_entity.add_component<component::Velocity>(math::Vector3{0, 0, 0});
   totem_entity.add_component<component::Totem>(m_team);

   return totem_entity;
}

}// namespace minecpp::entity::factory
