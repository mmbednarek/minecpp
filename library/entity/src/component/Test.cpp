#include <minecpp/entity/component/Location.h>
#include <minecpp/entity/component/Test.h>
#include <minecpp/entity/component/TickComponent.h>
#include <spdlog/spdlog.h>

namespace minecpp::entity::component {

void Test::on_attached(game::Entity &entity)
{
   if (entity.has_component<Location>()) {
      entt::sink sink{entity.component<Location>().on_position_change};
      sink.connect<&Test::on_position_change>(this);
   }

   if (entity.has_component<TickComponent>()) {
      entt::sink sink{entity.component<TickComponent>().on_tick};
      sink.connect<&Test::tick>(this);
   }
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
