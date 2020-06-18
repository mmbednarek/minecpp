#include "players.h"
#include <utility>
#include <boost/uuid/uuid_io.hpp>
#include <fstream>
#include <mineutils/compression.h>
#include <mineutils/format.h>
#include <mineutils/uuid.h>
#include <nbt/reader.h>

namespace Engine {

PlayerManager::PlayerManager(std::string_view players_path,
                             EntityManager &entities)
    : players_path(players_path), entities(entities) {}

void PlayerManager::join_player(std::string name, uuid id) {
   auto player_data = load_player_data(id);

   auto entity_id = entities.spawn(
       std::forward<Game::Entity::Entity>(player_data.to_entity()));
   auto player = player_data.to_player(name);
   player.set_entity_id(entity_id);
   char uuid[17];
   Utils::encode_uuid(uuid, id);
   uuid_to_id[uuid] = players.size();
   players.emplace_back(player);
}

Game::PlayerData PlayerManager::load_player_data(uuid id) {
   // TODO: cache player data
   std::ifstream f_player_data;
   f_player_data.open(
       Utils::format("{}/{}.dat", players_path, boost::uuids::to_string(id)));
   if (!f_player_data.is_open()) {
      return Game::PlayerData(id);
   }

   Utils::GZipInputStream stream(f_player_data);
   NBT::Reader r(stream);
   r.check_signature();

   return Game::PlayerData(r);
}

Game::Player &PlayerManager::get_player(uuid id) {
   char uuid[17];
   Utils::encode_uuid(uuid, id);
   auto player_iter = uuid_to_id.find(uuid);
   if (player_iter == uuid_to_id.end()) {
      throw std::runtime_error("no such player");
   }
   return players[player_iter->second];
}

Game::Entity::Entity &PlayerManager::get_entity(uuid id) {
   return entities.get_entity(get_player(id).get_entity_id());
}

void PlayerManager::for_each_player(std::function<void(Game::Player &)> callback) {
   std::for_each(players.begin(), players.end(), std::move(callback));
}

} // namespace Engine
