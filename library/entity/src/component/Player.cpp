#include <minecpp/entity/component/Player.h>

#include <utility>

namespace minecpp::entity::component {

Player::Player(const game::PlayerId &id, std::string name) :
    m_id(id),
    m_name(std::move(name))
{
}

void Player::on_attached(game::Entity &entity)
{
   m_entity_id = entity.id();
}

void Player::serialize_player_to_proto(proto::entity::v1::PlayerEntity *entity) const
{
   auto [lower, upper] = util::write_uuid(m_id);
   entity->mutable_uuid()->set_lower(lower);
   entity->mutable_uuid()->set_upper(upper);
}

game::PlayerId Player::id() const
{
   return m_id;
}

const std::string &Player::name() const
{
   return m_name;
}

void Player::refresh_visible_entities(game::IDispatcher &dispatcher, game::IEntitySystem &entity_system,
                                      const math::Vector3 &position)
{
   auto new_visible_entities = entity_system.list_entities_in_view_distance(position);
   std::sort(new_visible_entities.begin(), new_visible_entities.end());

   std::lock_guard lk{m_visible_entities_mutex};

   auto new_it = new_visible_entities.begin();
   auto old_it = m_visible_entities.begin();

   while (new_it != new_visible_entities.end() or old_it != m_visible_entities.end()) {
      if (new_it == new_visible_entities.end() or
          (old_it != m_visible_entities.end() and *old_it < *new_it)) {
         dispatcher.remove_entity_for_player(m_id, *old_it);

         auto other_entity = entity_system.entity(*old_it);
         if (other_entity.has_component<Player>()) {
            other_entity.component<Player>().remove_visible_entity(dispatcher, m_entity_id);
         }

         ++old_it;
         continue;
      }

      if (old_it == m_visible_entities.end() or *new_it < *old_it) {
         auto other_entity = entity_system.entity(*new_it);
         if (other_entity.has_component<Player>()) {
            if (other_entity.component<Player>().id() == m_id) {
               ++new_it;
               continue;
            }

            dispatcher.spawn_player_for_player(m_id, other_entity.component<Player>().id(),
                                               other_entity.id());
            other_entity.component<Player>().add_visible_player_entity(dispatcher, m_id, m_entity_id);
         } else {
            dispatcher.spawn_entity_for_player(m_id, other_entity.id());
         }

         ++new_it;
         continue;
      }

      if (old_it != m_visible_entities.end())
         ++old_it;

      if (new_it != new_visible_entities.end())
         ++new_it;
   }

   m_visible_entities = std::move(new_visible_entities);
}

void Player::remove_visible_entity(game::IDispatcher &dispatcher, game::EntityId entity_id)
{
   dispatcher.remove_entity_for_player(m_id, entity_id);

   std::lock_guard lk{m_visible_entities_mutex};
   auto it = std::find(m_visible_entities.begin(), m_visible_entities.end(), entity_id);
   if (it != m_visible_entities.end()) {
      m_visible_entities.erase(it);
   }
}

void Player::add_visible_player_entity(game::IDispatcher &dispatcher, game::PlayerId player_id,
                                       game::EntityId entity_id)
{
   dispatcher.spawn_player_for_player(m_id, player_id, entity_id);

   std::lock_guard lk{m_visible_entities_mutex};
   m_visible_entities.push_back(entity_id);
   std::sort(m_visible_entities.begin(), m_visible_entities.end());
}

void Player::init_visible_entities(game::IDispatcher &dispatcher, game::IEntitySystem &entity_system,
                                   const math::Vector3 &position)
{
   std::lock_guard lk{m_visible_entities_mutex};
   m_visible_entities = entity_system.list_entities_in_view_distance(position);
   std::sort(m_visible_entities.begin(), m_visible_entities.end());
   dispatcher.entity_list(m_id, m_visible_entities);

   for (auto entity_id : m_visible_entities) {
      if (entity_id == m_entity_id)
         continue;

      auto entity = entity_system.entity(entity_id);
      if (not entity.has_component<Player>())
         continue;

      entity.component<Player>().add_visible_player_entity(dispatcher, m_id, m_entity_id);
   }
}

}// namespace minecpp::entity::component