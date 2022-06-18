#include "Players.h"
#include "Entities.h"
#include <boost/uuid/uuid_io.hpp>
#include <fmt/core.h>
#include <fstream>
#include <minecpp/game/World.h>
#include <minecpp/nbt/Reader.h>
#include <minecpp/util/Compression.h>
#include <minecpp/util/Format.h>
#include <minecpp/util/Uuid.h>
#include <utility>

namespace minecpp::service::engine {

PlayerManager::PlayerManager(std::string_view players_path, EntityManager &entities) :
    m_players_path(players_path),
    m_entities(entities)
{
}

mb::result<mb::empty> PlayerManager::join_player(game::World &w, const std::string &name,
                                                 game::PlayerId id)
{
   auto player_data = MB_TRY(load_player_data(w, id));
   auto entity_id   = m_entities.spawn(Entity::from_player_nbt(player_data));
   auto player      = game::player::Player::from_nbt(player_data, name, w.notifier());
   player.set_entity_id(entity_id);

   m_id_map[minecpp::util::write_uuid(id)] = m_players.size();
   m_players.emplace_back(std::move(player));
   return mb::ok;
}

mb::result<minecpp::nbt::player::v1::Player> PlayerManager::load_player_data(game::World &w,
                                                                             game::PlayerId id)
{
   // TODO: cache player data
   std::ifstream f_player_data;
   f_player_data.open(fmt::format("{}/{}.dat", m_players_path, boost::uuids::to_string(id)));
   if (!f_player_data.is_open()) {
      minecpp::nbt::player::v1::Player data;
      auto pos  = MB_TRY(get_spawn_position(w));
      data.uuid = game::player::write_id_to_nbt(id);
      data.pos.resize(3);
      data.pos[0]              = pos.x;
      data.pos[1]              = pos.y;
      data.pos[2]              = pos.z;
      data.abilities.mayfly    = true;
      data.abilities.flying    = true;
      data.abilities.fly_speed = 0.08f;
      return data;
   }

   minecpp::util::GZipInputStream stream(f_player_data);
   return minecpp::nbt::player::v1::Player::deserialize(stream);
}

mb::result<minecpp::util::Vec3> PlayerManager::get_spawn_position(minecpp::game::World &w)
{
   //   std::uniform_int_distribution<int> dist(-200, 200);
   //   auto x = dist(rand_engine);
   //   auto z = dist(rand_engine);
   auto x = 0;
   auto z = 0;
   auto y = MB_TRY(w.height_at(x, z)) + 2;
   return util::Vec3(x, y, z);
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
   std::transform(m_players.begin(), m_players.end(), status_list.begin(), [](const game::player::Player &player) {
      return game::player::Status{
              .name = player.name(),
              .ping = player.ping(),
              .mode = player.game_mode(),
      };
   });
   return status_list;
}

}// namespace minecpp::service::engine
