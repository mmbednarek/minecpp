#include <minecpp/entity/component/Location.h>
#include <minecpp/entity/component/Test.h>
#include <minecpp/entity/component/Ticker.h>
#include <spdlog/spdlog.h>

namespace minecpp::entity::component {

void Test::on_attached(game::Entity &entity)
{
   assert(entity.has_component<Location>());
   assert(entity.has_component<Ticker>());

   auto &location = entity.component<Location>();
   location.on_position_change.connect_to<&Test::on_position_change>(m_position_change_sink, this);

   auto &ticker = entity.component<Ticker>();
   ticker.on_tick.connect_to<&Test::tick>(m_tick_sink, this);
}

void Test::tick(game::IWorld & /*world*/, game::Entity &entity, double delta_time)
{
   spdlog::debug("Ticking entity {}, TPS={}", entity.id(), 1000.0 / delta_time);
}

void Test::on_position_change(game::IWorld & /*world*/, game::Entity &entity,
                              const math::Vector3 &old_position, const math::Vector3 &new_position)
{
   ++m_position_change_count;
   spdlog::debug("Entity {} changing position from ({}) to ({}). This entity has changed position {} times.",
                 entity.id(), old_position, new_position, m_position_change_count);
}

}// namespace minecpp::entity::component
