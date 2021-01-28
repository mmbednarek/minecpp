#include "players.h"
#include <boost/uuid/uuid_io.hpp>
#include <fstream>
#include <minecpp/util/compression.h>
#include <minecpp/util/format.h>
#include <minecpp/util/uuid.h>
#include <minecpp/nbt/reader.h>
#include <utility>

namespace Engine {

PlayerManager::PlayerManager(std::string_view players_path, EntityManager &entities)
    : players_path(players_path), entities(entities) {}

void PlayerManager::join_player(minecpp::game::World &w, std::string name, uuid id) {
   auto player_data = load_player_data(w, id);

   auto entity_id = entities.spawn(std::forward<minecpp::game::entity::Entity>(player_data.to_entity()));
   auto player = player_data.to_player(name);
   player.set_entity_id(entity_id);
   char uuid[17];
   minecpp::util::encode_uuid(uuid, id);
   uuid_to_id[uuid] = players.size();
   players.emplace_back(player);
}

minecpp::game::PlayerData PlayerManager::load_player_data(minecpp::game::World &w, uuid id) {
   // TODO: cache player data
   std::ifstream f_player_data;
   f_player_data.open(minecpp::util::format("{}/{}.dat", players_path, boost::uuids::to_string(id)));
   if (!f_player_data.is_open()) {
      auto data = minecpp::game::PlayerData(id);
      data.pos = get_spawn_position(w);
      return data;
   }

   minecpp::util::GZipInputStream stream(f_player_data);
   minecpp::nbt::Reader r(stream);
   r.check_signature();

   return minecpp::game::PlayerData(r);
}

minecpp::util::Vec3 PlayerManager::get_spawn_position(minecpp::game::World &w) {
   std::uniform_int_distribution<int> dist(-200, 200);
   auto x = dist(rand_engine);
   auto z = dist(rand_engine);
   auto y = w.height_at(x, z).unwrap(0) + 2;
   return minecpp::util::Vec3(x, y, z);
}

minecpp::game::Player &PlayerManager::get_player(uuid id) {
   char uuid[17];
   minecpp::util::encode_uuid(uuid, id);
   auto player_iter = uuid_to_id.find(uuid);
   if (player_iter == uuid_to_id.end()) {
      throw std::runtime_error("no such player");
   }
   return players[player_iter->second];
}

minecpp::game::entity::Entity &PlayerManager::get_entity(uuid id) { return entities.get_entity(get_player(id).get_entity_id()); }

void PlayerManager::for_each_player(std::function<void(minecpp::game::Player &)> callback) {
   std::for_each(players.begin(), players.end(), std::move(callback));
}

void PlayerManager::remove_player(uuid id) {
   char uuid[17];
   minecpp::util::encode_uuid(uuid, id);
   try {
      auto index = uuid_to_id.at(uuid);
      players.erase(players.begin() + index);
      remap_ids();
   } catch (std::runtime_error &e) {
   }
}

void PlayerManager::remap_ids() {
   uuid_to_id = std::map<std::string, uint32_t>();
   uint32_t index = 0;
   for (auto const &p : players) {
      char uuid[17];
      minecpp::util::encode_uuid(uuid, p.get_id());
      uuid_to_id[uuid] = index++;
   }
}

std::size_t PlayerManager::player_count() { return players.size(); }

} // namespace Engine
