#include <minecpp/entity/component/Location.h>
#include <minecpp/entity/component/Player.h>
#include <minecpp/entity/component/Team.h>
#include <minecpp/entity/component/Totem.h>

namespace minecpp::entity::component {

Totem::Totem(game::Team team) :
    m_team(team)
{
}

void Totem::on_attached(game::Entity &entity)
{
   assert(entity.has_component<Location>());

   m_entity_id = entity.id();

   auto &location = entity.component<Location>();
   m_intersect_sink.emplace(location.on_begin_intersect.connect<&Totem::on_begin_intersect>(this));
}

void Totem::serialize_to_proto(proto::entity::v1::Entity *entity) const
{
   entity->set_entity_type(m_entity_type_id);
   auto *meta = entity->add_metadata();
   meta->set_index(17);
   meta->set_byte(static_cast<uint32_t>(m_team.sheep_color()));
}

void Totem::on_begin_intersect(game::IWorld &world, game::Entity & /*entity*/, game::Entity &other_entity)
{
   using format::Color;

   if (m_is_attached)
      return;

   if (not other_entity.has_component<Player>())
      return;

   assert(other_entity.has_component<Team>());
   assert(other_entity.has_component<Location>());
   assert(other_entity.has_component<Health>());

   auto is_bringing_back = other_entity.component<Team>().team() == m_team;

   if (not m_is_moved and is_bringing_back)
      return;

   auto &location = other_entity.component<Location>();
   location.on_position_change.connect_to<&Totem::on_player_move>(m_position_change_sink, this);

   auto &health = other_entity.component<Health>();
   health.on_dead.connect_to<&Totem::on_player_dead>(m_dead_sink, this);

   m_is_attached = true;
   m_is_moved    = true;

   world.dispatcher().send_chat(chat::MessageType::PlayerMessage,
                                format::Builder()
                                        .bold(other_entity.component<Team>().team().color(),
                                              other_entity.component<Player>().name())
                                        .text(" has captured team's ")
                                        .bold(m_team.color(), m_team.to_string())
                                        .text(" totem")
                                        .to_string());
}

void Totem::on_player_move(game::IWorld &world, game::Entity &entity, const math::Vector3 & /*old_position*/,
                           const math::Vector3 &new_position)
{
   auto totem_entity = world.entity_system().entity(m_entity_id);
   assert(totem_entity.has_component<Location>());

   assert(entity.has_component<Rotation>());
   assert(entity.has_component<Team>());

   auto is_bringing_back = entity.component<Team>().team() == m_team;

   auto base = base_from_position(new_position);
   if (not base.has_value() or ((*base == m_team) != is_bringing_back)) {
      auto &player_rotation = entity.component<Rotation>();

      auto &rotation = totem_entity.component<Rotation>();
      rotation.set_rotation(world.dispatcher(), new_position, player_rotation.rotation());

      auto &location = totem_entity.component<Location>();
      location.set_position(world, totem_entity, new_position + math::Vector3{0, 1.9, 0}, true);

      return;
   }

   this->detach(world, totem_entity);

   if (*base == m_team) {
      world.dispatcher().send_chat(chat::MessageType::PlayerMessage,
                                   format::Builder()
                                           .bold(m_team.color(), m_team.to_string())
                                           .text("'s team totem has return to its base")
                                           .to_string());
   } else {
      world.dispatcher().send_chat(chat::MessageType::PlayerMessage,
                                   format::Builder()
                                           .bold(base->color(), base->to_string())
                                           .text(" has seized ")
                                           .bold(m_team.color(), m_team.to_string())
                                           .text("'s totem")
                                           .to_string());
   }
}

void Totem::on_player_dead(game::IWorld &world, game::Entity &entity, const game::Damage & /*damage*/)
{
   using format::Color;

   auto totem_entity = world.entity_system().entity(m_entity_id);
   this->detach(world, totem_entity);

   assert(entity.has_component<Player>());
   assert(entity.has_component<Team>());

   auto player_team = entity.component<Team>().team();

   world.dispatcher().send_chat(chat::MessageType::PlayerMessage,
                                format::Builder()
                                        .bold(player_team.color(), entity.component<Player>().name())
                                        .text(" has lost control over ")
                                        .bold(m_team.color(), m_team.to_string())
                                        .text("'s team totem")
                                        .to_string());
}

game::Team Totem::team() const
{
   return m_team;
}

void Totem::detach(game::IWorld &world, game::Entity &entity)
{
   assert(entity.has_component<Location>());
   entity.component<Location>().set_is_on_ground(world, entity, false);

   m_position_change_sink.reset();
   m_dead_sink.reset();

   m_is_attached = false;
}

std::optional<game::Team> Totem::base_from_position(const math::Vector3 &position)
{
   if (position.z() > -318)
      return game::Team::Blue;

   if (position.z() < -598)
      return game::Team::Black;

   return std::nullopt;
}

}// namespace minecpp::entity::component
