#include <minecpp/entity/component/Location.h>
#include <minecpp/entity/component/Player.h>
#include <minecpp/math/Rotation.h>
#include <spdlog/spdlog.h>

namespace minecpp::entity::component {

Location::Location(const math::Vector3 &position, const math::Vector3 &extent) :
    m_position(position),
    m_extent(extent),
    m_tracked_position(TrackedPosition::from_vector3(position))
{
}

void Location::serialize_to_proto(proto::entity::v1::Entity *entity) const
{
   *entity->mutable_position() = this->m_position.to_proto();
}

void Location::serialize_player_to_proto(proto::entity::v1::PlayerEntity *entity) const
{
   *entity->mutable_position() = this->m_position.to_proto();
}

math::Vector3 Location::position() const
{
   return m_position;
}

math::Vector3 Location::extent() const
{
   return m_extent;
}

void Location::set_position(game::IWorld &world, game::Entity &entity, const math::Vector3 &position,
                            bool is_on_ground)
{
   if (m_is_detached)
      return;// cannot set the position while the entity is detached

   const auto prev_logical_position = this->logical_position();
   const auto distance              = (position - prev_logical_position).length();
   if (distance < 0.1) {
      // just apply position
      m_position = position;
      return;
   }

   this->on_position_change.publish(world, entity, prev_logical_position, position);

   m_is_on_ground = is_on_ground;
   m_position     = position;

   auto movement = (m_position * 4096.0).cast<int64_t>() - m_tracked_position.position;
   if (movement == math::Vector3l{0, 0, 0})
      return;

   m_tracked_position.position += movement;
   world.entity_system().move_spatial_entity(entity.id(), m_extent, prev_logical_position,
                                             this->logical_position());

   math::Rotation rotation{};
   if (entity.has_component<Rotation>()) {
      rotation = entity.component<Rotation>().rotation();
   }

   if (m_refresh_count <= 0 || distance >= 16.0) {
      m_refresh_count = 100;
      world.dispatcher().teleport_entity(entity.id(), position, rotation, m_is_on_ground);
   } else {
      world.dispatcher().entity_move(entity.id(), position, movement.cast<short>(), rotation, m_is_on_ground);
      --m_refresh_count;
   }

   auto min = m_position - m_extent * 0.5;
   auto max = m_position + m_extent * 0.5;
   min.set_y(m_position.y());
   max.set_y(m_position.y() + m_extent.y());
   auto intersecting_entities = world.entity_system().list_entities_intersecting_with(min, max);
   for (auto entity_id : intersecting_entities) {
      if (entity_id == entity.id())
         continue;

      if (m_entities_intersecting_with.contains(entity_id))
         continue;

      auto other = world.entity_system().entity(entity_id);
      this->on_begin_intersect.publish(world, entity, other);
      if (other.has_component<Location>()) {
         other.component<Location>().on_begin_intersect.publish(world, other, entity);
      }
   }

   // FIXME: It is stupid to create the same RB tree on each tick
   m_entities_intersecting_with.clear();
   for (auto entity_id : intersecting_entities) {
      if (entity_id == entity.id())
         continue;
      this->m_entities_intersecting_with.insert(entity_id);
   }
}

math::Vector3 Location::logical_position() const
{
   return m_tracked_position.position.cast<double>() / 4096.0;
}

void Location::on_killed(game::IWorld * /*world*/, game::Entity *entity)
{
   spdlog::info("called on kill! eid:{}", entity->id());
   m_is_detached = true;
}

void Location::reset_position_and_extent(const math::Vector3 &position, const math::Vector3 &extent)
{
   m_tracked_position = TrackedPosition::from_vector3(position);
   m_position         = position;
   m_extent           = extent;
   m_is_detached      = false;
}

bool Location::is_on_ground() const
{
   return m_is_on_ground;
}

void Location::set_is_on_ground(game::IDispatcher &dispatcher, game::Entity &entity, const bool is_on_ground)
{
   if (m_is_on_ground == is_on_ground)
      return;

   m_is_on_ground = is_on_ground;

   math::Rotation rotation{0, 0};
   if (entity.has_component<Rotation>()) {
      rotation = entity.component<Rotation>().rotation();
   }

   dispatcher.teleport_entity(entity.id(), m_position, rotation, is_on_ground);
}

Rotation::Rotation(float yaw, float pitch) :
    m_yaw(yaw),
    m_pitch(pitch)
{
}

void Rotation::serialize_to_proto(proto::entity::v1::Entity *entity) const
{
   entity->mutable_rotation()->set_yaw(math::radians_to_degrees(this->m_yaw));
   entity->mutable_rotation()->set_pitch(math::radians_to_degrees(this->m_pitch));
}

void Rotation::serialize_player_to_proto(proto::entity::v1::PlayerEntity *entity) const
{
   entity->mutable_rotation()->set_yaw(math::radians_to_degrees(this->m_yaw));
   entity->mutable_rotation()->set_pitch(math::radians_to_degrees(this->m_pitch));
}

math::Degrees Rotation::yaw_degrees() const
{
   return math::radians_to_degrees(m_yaw);
}

math::Degrees Rotation::pitch_degrees() const
{
   return math::radians_to_degrees(m_pitch);
}

void Rotation::set_yaw_degrees(math::Degrees yaw)
{
   m_yaw = math::degrees_to_radians(yaw);
}

void Rotation::set_pitch_degrees(math::Degrees pitch)
{
   m_pitch = math::degrees_to_radians(pitch);
}

math::Rotation Rotation::rotation() const
{
   return {m_yaw, m_pitch};
}

math::Radians Rotation::yaw() const
{
   return m_yaw;
}

math::Radians Rotation::pitch() const
{
   return m_pitch;
}

void Rotation::set_yaw(math::Radians yaw)
{
   m_yaw = yaw;
}

void Rotation::set_pitch(math::Radians pitch)
{
   m_pitch = pitch;
}

void Rotation::set_rotation(game::IDispatcher &dispatcher, const math::Vector3 &position, math::Radians yaw,
                            math::Radians pitch)
{
   m_yaw   = yaw;
   m_pitch = pitch;
   dispatcher.entity_look(m_entity_id, position, {this->yaw_degrees(), this->pitch_degrees()});
}

void Rotation::on_attached(game::Entity &entity)
{
   m_entity_id = entity.id();
}

TrackedPosition TrackedPosition::from_vector3(const math::Vector3 &position)
{
   return {(position * 4096.0).cast<std::int64_t>()};
}

math::Vector3 TrackedPosition::to_vector3() const
{
   return this->position.cast<double>() / 4096.0;
}

void TrackedPosition::apply_movement(const game::Movement &movement)
{
   this->position += movement.movement.cast<std::int64_t>();
}

}// namespace minecpp::entity::component
