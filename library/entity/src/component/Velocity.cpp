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
   m_entity_id = entity.id();
   if (entity.has_component<Ticker>()) {
      entt::sink sink{entity.component<Ticker>().on_tick};
      sink.connect<&Velocity::tick>(this);
   }
}

void Velocity::tick(game::IWorld &world, game::Entity &entity, double delta_time)
{
   if (entity.has_component<Player>())
      return;

   auto &location = entity.component<Location>();
   auto blocked   = world.is_movement_blocked_at(location.position());
   if (blocked) {
      this->set_velocity(world.dispatcher(), location.position(), {0, 0.1, 0});
      location.set_is_on_ground(world.dispatcher(), entity, false);
   }

   if (location.is_on_ground())
      return;

   auto new_position = location.position() + m_velocity * delta_time;
   if (not blocked and world.is_movement_blocked_at(new_position)) {
      world.dispatcher().send_chat(
              chat::MessageType::PlayerMessage,
              format::Builder().text(fmt::format("entity {} hit ground", entity.id())).to_string());
      this->set_velocity(world.dispatcher(), location.position(), {0, 0, 0});
      location.set_is_on_ground(world.dispatcher(), entity, true);
      return;
   }

   location.set_position(world, entity, new_position, false);

   if (m_velocity.y() > -0.9) {
      math::Vector3 new_velocity{m_velocity};
      new_velocity.set_y(m_velocity.y() - 0.03999999910593033 * delta_time);
      this->set_velocity(world.dispatcher(), location.position(), new_velocity);
   }
}

void Velocity::serialize_to_proto(proto::entity::v1::Entity *entity) const
{
   *entity->mutable_velocity() = (m_velocity * 8000.0).cast<short>().to_proto();
}

void Velocity::set_velocity(game::IDispatcher &dispatcher, const math::Vector3 &position,
                            const math::Vector3 &velocity)
{
   assert(position.is_correct());
   assert(velocity.is_correct());

   m_velocity = velocity;
   dispatcher.set_entity_velocity(m_entity_id, position, (velocity * 8000.0).cast<short>());
}

const math::Vector3 &Velocity::velocity() const
{
   return m_velocity;
}

}// namespace minecpp::entity::component
