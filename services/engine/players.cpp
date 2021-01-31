#include "players.h"
#include <boost/uuid/uuid_io.hpp>
#include <fmt/core.h>
#include <fstream>
#include <minecpp/nbt/reader.h>
#include <minecpp/util/compression.h>
#include <minecpp/util/format.h>
#include <minecpp/util/uuid.h>
#include <utility>

namespace Engine {

PlayerManager::PlayerManager(std::string_view players_path, EntityManager &entities)
    : players_path(players_path), entities(entities) {}

mb::result<mb::empty> PlayerManager::join_player(minecpp::game::World &w, std::string name, uuid id) {
   auto player_data = MB_TRY(load_player_data(w, id));
   auto entity_id = entities.spawn(player_data.to_entity());
   auto player = player_data.to_player(name);
   player.set_entity_id(entity_id);

   uuid_to_id[minecpp::util::uuid_to_string(id)] = players.size();
   players.emplace_back(std::move(player));
   return mb::ok;
}

mb::result<minecpp::game::PlayerData> PlayerManager::load_player_data(minecpp::game::World &w, uuid id) {
   // TODO: cache player data
   std::ifstream f_player_data;
   f_player_data.open(fmt::format("{}/{}.dat", players_path, boost::uuids::to_string(id)));
   if (!f_player_data.is_open()) {
      auto data = minecpp::game::PlayerData(id);
      data.pos = MB_TRY(get_spawn_position(w));
      return data;
   }

   minecpp::util::GZipInputStream stream(f_player_data);
   minecpp::nbt::Reader r(stream);
   r.check_signature();

   return minecpp::game::PlayerData(r);
}

mb::result<minecpp::util::Vec3> PlayerManager::get_spawn_position(minecpp::game::World &w) {
   std::uniform_int_distribution<int> dist(-200, 200);
   auto x = dist(rand_engine);
   auto z = dist(rand_engine);
   auto y = MB_TRY(w.height_at(x, z)) + 2;
   return minecpp::util::Vec3(x, y, z);
}

mb::result<minecpp::game::Player &> PlayerManager::get_player(uuid id) {
   auto it_player = uuid_to_id.find(minecpp::util::uuid_to_string(id));
   if (it_player == uuid_to_id.end()) {
      return mb::error("no such player");
   }
   return players.at(it_player->second);
}

mb::result<minecpp::game::entity::Entity &> PlayerManager::get_entity(uuid id) {
   return entities.get_entity(MB_TRY(get_player(id)).get_entity_id());
}

void PlayerManager::for_each_player(const std::function<void(minecpp::game::Player &)> &callback) {
   std::for_each(players.begin(), players.end(), callback);
}

void PlayerManager::remove_player(uuid id) {
   auto index = uuid_to_id.at(minecpp::util::uuid_to_string(id));
   players.erase(players.begin() + index);
   remap_ids();
}

void PlayerManager::remap_ids() {
   uuid_to_id = std::map<std::string, mb::u32>();
   uint32_t index = 0;
   for (auto const &p : players) {
      char uuid[17];
      minecpp::util::encode_uuid(uuid, p.get_id());
      uuid_to_id[uuid] = index++;
   }
}

std::size_t PlayerManager::player_count() { return players.size(); }

}// namespace Engine
