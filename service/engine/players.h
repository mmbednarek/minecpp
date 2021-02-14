#pragma once
#include "entities.h"
#include <boost/uuid/uuid.hpp>
#include <functional>
#include <mb/result.h>
#include <minecpp/game/player.h>
#include <minecpp/game/player_data.h>
#include <random>
#include <vector>

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

   mb::result<mb::empty> join_player(minecpp::game::World &w, std::string name, uuid id);
   mb::result<minecpp::game::PlayerData> load_player_data(minecpp::game::World &w, uuid id);

   mb::result<minecpp::util::Vec3> get_spawn_position(minecpp::game::World &w);
   mb::result<minecpp::game::Player &> get_player(uuid id);
   mb::result<minecpp::game::entity::Entity &> get_entity(uuid id);
   void for_each_player(const std::function<void(minecpp::game::Player &)> &callback);
   void remove_player(uuid id);
   void remap_ids();
   std::size_t player_count();
};

}// namespace Engine
