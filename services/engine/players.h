#pragma once
#include "entities.h"
#include <boost/uuid/uuid.hpp>
#include <game/player.h>
#include <game/player_data.h>
#include <vector>
#include <functional>

namespace Engine {

using boost::uuids::uuid;

class PlayerManager {
   std::vector<Game::Player> players;
   std::map<std::string, uint32_t> uuid_to_id;
   std::string_view players_path;
   EntityManager &entities;

 public:
   PlayerManager(std::string_view players_path, EntityManager &entities);

   void join_player(std::string name, uuid id);
   Game::PlayerData load_player_data(uuid id);

   Game::Player &get_player(uuid id);
   Game::Entity::Entity &get_entity(uuid id);
   void for_each_player(std::function<void(Game::Player &)> callback);
   void remove_player(uuid id);
   void remap_ids();
};

} // namespace Engine
