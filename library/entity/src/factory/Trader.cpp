#include <minecpp/entity/component/Location.h>
#include <minecpp/entity/component/Ticker.h>
#include <minecpp/entity/component/Totem.h>
#include <minecpp/entity/component/Trader.h>
#include <minecpp/entity/component/UniqueId.h>
#include <minecpp/entity/component/Velocity.h>
#include <minecpp/entity/factory/Trader.h>

namespace minecpp::entity::factory {

Trader::Trader(float initial_yaw, float initial_pitch) :
    m_initial_yaw{initial_yaw},
    m_initial_pitch{initial_pitch}
{
}

game::Entity Trader::create_entity(const math::Vector3 &position, game::IEntitySystem &entity_system)
{
   auto trader_entity = entity_system.create_spatial_entity(position, {0.6, 1.9, 0.6});

   trader_entity.add_component<component::UniqueId>();
   trader_entity.add_component<component::Rotation>(m_initial_yaw, m_initial_pitch);
   trader_entity.add_component<component::Ticker>();
   trader_entity.add_component<component::Velocity>(math::Vector3{0, 0, 0});
   trader_entity.add_component<component::Trader>();

   return trader_entity;
}

}// namespace minecpp::entity::factory
