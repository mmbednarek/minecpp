#include "Players.h"
#include "Entities.h"
#include <boost/uuid/uuid_io.hpp>
#include <fmt/core.h>
#include <minecpp/game/World.h>
#include <minecpp/nbt/Reader.h>
#include <minecpp/util/Compression.h>
#include <minecpp/util/Uuid.h>
#include <utility>

namespace minecpp::service::engine {

PlayerManager::PlayerManager(EntityManager &entities, game::BlockPosition spawn_position) :
    m_entities(entities),
    m_spawn_position(std::move(spawn_position))
{
}

mb::result<mb::empty> PlayerManager::join_player(game::World &w, const std::string &name, game::PlayerId id)
{
   auto player_data = MB_TRY(load_player_data(w, id));
   auto entity_id   = m_entities.spawn(Entity::from_player_nbt(player_data));
   auto player      = game::player::Player::from_nbt(player_data, name, w.notifier());
   player.set_entity_id(entity_id);
   m_player_entity_map[entity_id] = id;

   m_id_map[minecpp::util::write_uuid(id)] = m_players.size();
   m_players.emplace_back(std::move(player));
   return mb::ok;
}

mb::result<minecpp::nbt::player::v1::Player> PlayerManager::load_player_data(game::World &w,
                                                                             game::PlayerId id)
{
   minecpp::nbt::player::v1::Player data;

   math::Vector3 pos{static_cast<double>(m_spawn_position.x), static_cast<double>(m_spawn_position.y),
                     static_cast<double>(m_spawn_position.z)};

   data.uuid = game::player::write_id_to_nbt(id);
   data.pos.resize(3);
   data.pos[0]              = pos.x();
   data.pos[1]              = pos.y();
   data.pos[2]              = pos.z();
   data.abilities.mayfly    = true;
   data.abilities.flying    = true;
   data.abilities.fly_speed = 0.08f;

   return data;
}

mb::result<game::player::Player &> PlayerManager::get_player(game::PlayerId id)
{
   auto it_player = m_id_map.find(minecpp::util::write_uuid(id));
   if (it_player == m_id_map.end()) {
      return mb::error("no such player");
   }
   return m_players.at(it_player->second);
}

mb::result<minecpp::game::entity::Entity &> PlayerManager::get_entity(game::PlayerId id)
{
   return m_entities.get_entity(MB_TRY(get_player(id)).entity_id());
}

void PlayerManager::for_each_player(const std::function<void(game::player::Player &)> &callback)
{
   std::for_each(m_players.begin(), m_players.end(), callback);
}

void PlayerManager::remove_player(game::PlayerId id)
{
   using DifferenceType = decltype(m_players)::iterator::difference_type;
   auto index           = m_id_map.at(minecpp::util::write_uuid(id));
   m_players.erase(m_players.begin() + static_cast<DifferenceType>(index));
   remap_ids();
}

void PlayerManager::remap_ids()
{
   m_id_map.clear();
   PlayerIndex index{};
   for (auto const &p : m_players) {
      m_id_map[minecpp::util::write_uuid(p.id())] = index++;
   }
}

std::size_t PlayerManager::player_count()
{
   return m_players.size();
}

std::vector<game::player::Status> PlayerManager::player_status_list() const
{
   std::vector<game::player::Status> status_list(m_players.size());
   std::transform(m_players.begin(), m_players.end(), status_list.begin(),
                  [](const game::player::Player &player) {
                     return game::player::Status{
                             .id   = player.id(),
                             .name = player.name(),
                             .ping = player.ping(),
                             .mode = player.game_mode(),
                     };
                  });
   return status_list;
}

std::optional<game::PlayerId> PlayerManager::get_player_id_by_entity_id(game::EntityId id)
{
   if (not m_player_entity_map.contains(id))
      return std::nullopt;
   return m_player_entity_map.at(id);
}

}// namespace minecpp::service::engine
