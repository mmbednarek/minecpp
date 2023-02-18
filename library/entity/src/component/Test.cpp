#include <minecpp/entity/component/Location.h>
#include <minecpp/entity/component/Test.h>
#include <spdlog/spdlog.h>

namespace minecpp::entity::component {

void Test::on_attached(game::Entity &entity) {
   entity.component<Location>().on_position_change.connect<&Test::on_position_change>(this);
}

void Test::on_position_change(game::EntityId entity_id, const math::Vector3 &old_position,
                              const math::Vector3 &new_position)
{
   ++m_position_change_count;
   spdlog::debug("Entity {} changing position from ({}) to ({}). This entity has changed position {} times.", entity_id, old_position, new_position, m_position_change_count);
}

}// namespace minecpp::entity::component
