#pragma once
#include "entities.h"
#include <boost/uuid/uuid.hpp>
#include <minecpp/game/player.h>
#include <minecpp/game/player_data.h>
#include <vector>
#include <functional>
#include <random>

namespace Engine {

using boost::uuids::uuid;

class PlayerManager {
   std::vector<minecpp::game::Player> players;
   std::map<std::string, uint32_t> uuid_to_id;
   std::string_view players_path;
   EntityManager &entities;
   std::default_random_engine rand_engine;

 public:
   PlayerManager(std::string_view players_path, EntityManager &entities);

   void join_player(minecpp::game::World &w, std::string name, uuid id);
   minecpp::game::PlayerData load_player_data(minecpp::game::World &w, uuid id);

   minecpp::util::Vec3 get_spawn_position(minecpp::game::World &w);
   minecpp::game::Player &get_player(uuid id);
   minecpp::game::entity::Entity &get_entity(uuid id);
   void for_each_player(std::function<void(minecpp::game::Player &)> callback);
   void remove_player(uuid id);
   void remap_ids();
   std::size_t player_count();
};

} // namespace Engine
