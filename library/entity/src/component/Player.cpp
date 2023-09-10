#include <minecpp/entity/component/Player.h>
#include <minecpp/game/IWorld.hpp>

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

void Player::serialize_to_net_player(game::NetworkPlayer *net_player) const
{
   net_player->player_data.player_id = m_id;
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
         dispatcher.spawn_entity_for_player(m_id, other_entity.id());

         if (other_entity.has_component<Player>()) {
            auto &player_com = other_entity.component<Player>();
            if (player_com.id() != m_id) {
               other_entity.component<Player>().add_visible_player_entity(dispatcher, m_entity_id);
            }
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

void Player::init_visible_entities(game::IDispatcher &dispatcher, game::IEntitySystem &entity_system,
                                   const math::Vector3 &position)
{
   std::lock_guard lk{m_visible_entities_mutex};

   m_visible_entities = entity_system.list_entities_in_view_distance(position);
   std::sort(m_visible_entities.begin(), m_visible_entities.end());
   dispatcher.send_entities(m_id, m_visible_entities);

   for (auto entity_id : m_visible_entities) {
      if (entity_id == m_entity_id)
         continue;

      auto entity = entity_system.entity(entity_id);
      if (not entity.has_component<Player>())
         continue;

      entity.component<Player>().add_visible_player_entity(dispatcher, m_entity_id);
   }
}

void Player::on_killed(game::IWorld *world, game::Entity * /*entity*/)
{
   assert(world);

   std::lock_guard lk{m_visible_entities_mutex};

   for (auto entity_id : m_visible_entities) {
      if (entity_id == m_entity_id)
         continue;

      world->dispatcher().remove_entity_for_player(m_id, entity_id);

      const auto entity = world->entity_system().entity(entity_id);
      if (not entity.has_component<Player>())
         continue;

      entity.component<Player>().remove_visible_entity(world->dispatcher(), m_entity_id);
   }

   m_visible_entities.clear();
}

void Player::on_attached_to_world(game::IWorld *world, game::Entity * /*entity*/,
                                  const math::Vector3 &position, const math::Vector3 & /*extent*/)
{
   this->init_visible_entities(world->dispatcher(), world->entity_system(), position);
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

void Player::add_visible_player_entity(game::IDispatcher &dispatcher, game::EntityId entity_id)
{
   dispatcher.spawn_entity_for_player(m_id, entity_id);

   std::lock_guard lk{m_visible_entities_mutex};

   for (auto visible_entity_id : m_visible_entities) {
      if (visible_entity_id > entity_id)
         break;

      if (visible_entity_id == entity_id)
         return;// already added
   }

   m_visible_entities.push_back(entity_id);
   std::sort(m_visible_entities.begin(), m_visible_entities.end());
}

const std::vector<game::EntityId> &Player::visible_entities() const
{
   return m_visible_entities;
}

void Player::begin_use_item()
{
   m_started_using_item = std::chrono::steady_clock::now();
}

std::chrono::steady_clock::duration Player::end_use_item()
{
   using namespace std::chrono_literals;
   if (not m_started_using_item.has_value())
      return 0s;

   auto result = std::chrono::steady_clock::now() - *m_started_using_item;
   m_started_using_item.reset();
   return result;
}

}// namespace minecpp::entity::component