#pragma once
#include <boost/uuid/uuid.hpp>
#include <functional>
#include <mb/result.h>
#include <minecpp/game/entity/entity.h>
#include <minecpp/nbt/player/v1/player.nbt.h>
#include <minecpp/player/player.h>
#include <minecpp/player/provider.hpp>
#include <random>
#include <vector>

namespace minecpp::service::engine {

class EntityManager;

using encoded_uuid = std::pair<mb::u64, mb::u64>;

class PlayerManager : public player::Provider
{
   using PlayerIndex = std::vector<player::Player>::size_type;

   std::vector<player::Player> m_players;
   std::map<encoded_uuid, PlayerIndex> m_id_map;
   std::string m_players_path;
   EntityManager &m_entities;
   std::default_random_engine m_rand_engine;

 public:
   PlayerManager(std::string_view players_path, EntityManager &entities);

   mb::result<mb::empty> join_player(minecpp::game::World &w, const std::string &name, player::Id id);
   mb::result<nbt::player::v1::Player> load_player_data(minecpp::game::World &w, player::Id id);

   mb::result<minecpp::util::Vec3> get_spawn_position(minecpp::game::World &w);
   mb::result<minecpp::player::Player &> get_player(player::Id id);
   mb::result<minecpp::game::entity::Entity &> get_entity(player::Id id);
   void for_each_player(const std::function<void(minecpp::player::Player &)> &callback);
   void remove_player(player::Id id);
   void remap_ids();
   std::size_t player_count();

   [[nodiscard]] std::vector<player::Status> player_status_list() const;
};

}// namespace minecpp::service::engine
