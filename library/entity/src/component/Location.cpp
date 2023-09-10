#include <minecpp/entity/component/Location.h>
#include <minecpp/entity/component/Player.h>
#include <minecpp/entity/component/Streamer.h>
#include <minecpp/math/Math.h>
#include <minecpp/math/Rotation.h>
#include <spdlog/spdlog.h>

namespace minecpp::entity::component {

Location::Location(const math::Vector3 &position, const math::Vector3 &extent) :
    m_position(position),
    m_extent(extent),
    m_tracked_position(TrackedPosition::from_vector3(position))
{
}

void Location::serialize_to_net(game::NetworkEntity *net_entity) const
{
   assert(net_entity);
   net_entity->entity_data.position = m_position;
}

void Location::serialize_to_net_player(game::NetworkPlayer *net_player) const
{
   assert(net_player);
   net_player->player_data.position = m_position;
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

   const auto old_logical_position = this->logical_position();
   const auto distance             = (position - old_logical_position).length();
   if (distance < 0.1) {
      // just apply position
      this->set_is_on_ground(world, entity, is_on_ground);
      m_position = position;
      return;
   }

   if (position.y() < -16.0) {
      world.apply_damage_or_kill_entity(entity.id(), game::Damage{.amount = 100.0f,
                                                                  .source = game::DamageSource::VoidDamage,
                                                                  .source_entity{},
                                                                  .target_entity = entity.id(),
                                                                  .vector{}});
      return;
   }

   auto movement = this->set_logical_position(world, entity.id(), position);

   m_is_on_ground = is_on_ground;
   m_position     = position;

   this->on_position_change.publish(world, entity, old_logical_position, position);

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
      m_entities_intersecting_with.insert(entity_id);
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

void Location::set_is_on_ground(game::IWorld &world, game::Entity &entity, const bool is_on_ground)
{
   if (m_is_on_ground == is_on_ground)
      return;

   m_is_on_ground = is_on_ground;

   math::Rotation rotation{0, 0};
   if (entity.has_component<Rotation>()) {
      rotation = entity.component<Rotation>().rotation();
   }

   world.dispatcher().teleport_entity(entity.id(), m_position, rotation, is_on_ground);

   if (is_on_ground) {
      on_hit_ground.publish(world, entity, m_position);
   }
}

math::Vector3l Location::set_logical_position(game::IWorld &world, game::EntityId entity_id,
                                              const math::Vector3 &position)
{
   std::lock_guard lk{m_mutex};
   auto old_logical_position = this->logical_position();

   auto movement = (position * 4096.0).cast<int64_t>() - m_tracked_position.position;
   m_tracked_position.position += movement;

   auto new_logical_position = this->logical_position();
   world.entity_system().move_spatial_entity(entity_id, m_extent, old_logical_position, new_logical_position);

   return movement;
}

void Location::teleport_player(game::IWorld &world, game::Entity &entity, const math::Vector3 &position)
{
   assert(entity.has_component<Player>());
   assert(entity.has_component<Rotation>());
   assert(entity.has_component<Streamer>());

   auto player_id = entity.component<Player>().id();

   this->set_position(world, entity, position, false);
   world.dispatcher().synchronise_player_position_and_rotation(player_id, position,
                                                               entity.component<Rotation>().rotation());
   entity.component<Streamer>().send_all_visible_chunks(world, player_id, position);
}

Rotation::Rotation(float yaw, float pitch) :
    m_rotation{yaw, pitch}
{
}

Rotation::Rotation(const math::Rotation &rotation) :
    m_rotation(rotation)
{
}

void Rotation::serialize_to_net(game::NetworkEntity *net_entity) const
{
   assert(net_entity);
   net_entity->entity_data.yaw = m_rotation.yaw_degrees();
   net_entity->entity_data.pitch = m_rotation.pitch_degrees();
}

void Rotation::serialize_to_net_player(game::NetworkPlayer *net_player) const
{
   assert(net_player);
   net_player->player_data.yaw = m_rotation.yaw_degrees();
   net_player->player_data.pitch = m_rotation.pitch_degrees();
}

math::Degrees Rotation::yaw_degrees() const
{
   return math::radians_to_degrees(m_rotation.yaw);
}

math::Degrees Rotation::pitch_degrees() const
{
   return math::radians_to_degrees(m_rotation.pitch);
}

void Rotation::set_yaw_degrees(math::Degrees yaw)
{
   this->set_yaw(math::degrees_to_radians(yaw));
}

void Rotation::set_pitch_degrees(math::Degrees pitch)
{
   this->set_pitch(math::degrees_to_radians(pitch));
}

math::Rotation Rotation::rotation() const
{
   return m_rotation;
}

math::Radians Rotation::yaw() const
{
   return m_rotation.yaw;
}

math::Radians Rotation::pitch() const
{
   return m_rotation.pitch;
}

void Rotation::set_yaw(math::Radians yaw)
{
   m_rotation.yaw = math::fmod(yaw, 2 * math::g_pi);
}

void Rotation::set_pitch(math::Radians pitch)
{
   m_rotation.pitch = math::fmod(pitch, 2 * math::g_pi);
}

void Rotation::set_rotation(game::IDispatcher &dispatcher, const math::Vector3 &position,
                            const math::Rotation &rotation)
{
   m_rotation = rotation;
   dispatcher.entity_look(m_entity_id, position, rotation);
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
