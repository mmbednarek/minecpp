#include <minecpp/entity/component/Location.h>
#include <minecpp/entity/component/Player.h>
#include <minecpp/entity/component/Ticker.h>
#include <minecpp/entity/component/Velocity.h>
#include <spdlog/spdlog.h>

namespace minecpp::entity::component {

Velocity::Velocity(const math::Vector3 &velocity) :
    m_velocity(velocity)
{
}

void Velocity::on_attached(game::Entity &entity)
{
   assert(entity.has_component<Ticker>());
   m_entity_id = entity.id();

   auto &ticker = entity.component<Ticker>();
   ticker.on_tick.connect_to<&Velocity::tick>(m_tick_sink, this);
}

void Velocity::tick(game::IWorld &world, game::Entity &entity, double delta_time)
{
   if (entity.has_component<Player>())
      return;

   auto &location = entity.component<Location>();
   auto blocked   = world.is_movement_blocked_at(location.position());
   if (blocked) {
      this->set_velocity(world, entity, {0, 0.1, 0});
      location.set_is_on_ground(world, entity, false);
   }

   if (location.is_on_ground())
      return;

   auto new_position = location.position() + m_velocity * delta_time;
   if (not blocked and world.is_movement_blocked_at(new_position)) {
      this->set_velocity(world, entity, {0, 0, 0});
      location.set_is_on_ground(world, entity, true);
      return;
   }

   location.set_position(world, entity, new_position, false);

   if (m_velocity.y() > -0.9) {
      math::Vector3 new_velocity{m_velocity};
      new_velocity.set_y(m_velocity.y() - 0.03999999910593033 * delta_time);
      this->set_velocity(world, entity, new_velocity);
   }
}

void Velocity::serialize_to_proto(proto::entity::Entity *entity) const
{
   *entity->mutable_velocity() = (m_velocity * 8000.0).cast<short>().to_proto();
}

void Velocity::set_velocity(game::IWorld &world, game::Entity &entity, const math::Vector3 &velocity)
{
   assert(entity.has_component<Location>());
   assert(velocity.is_correct());

   m_velocity = velocity;
   on_velocity_change.publish(world, entity, velocity);
   world.dispatcher().set_entity_velocity(m_entity_id, entity.component<Location>().position(),
                                          (velocity * 8000.0).cast<short>());
}

const math::Vector3 &Velocity::velocity() const
{
   return m_velocity;
}

}// namespace minecpp::entity::component
