#pragma once
#include <boost/uuid/uuid.hpp>
#include <functional>
#include <mb/result.h>
#include <minecpp/game/entity/Entity.h>
#include <minecpp/nbt/player/v1/Player.nbt.h>
#include <minecpp/game/player/Player.h>
#include <minecpp/game/player/Provider.hpp>
#include <random>
#include <vector>

namespace minecpp::service::engine {

class EntityManager;

using encoded_uuid = std::pair<mb::u64, mb::u64>;

class PlayerManager : public game::player::Provider
{
   using PlayerIndex = std::vector<game::player::Player>::size_type;

   std::vector<game::player::Player> m_players;
   std::map<encoded_uuid, PlayerIndex> m_id_map;
   std::string m_players_path;
   EntityManager &m_entities;
   std::default_random_engine m_rand_engine;

 public:
   PlayerManager(std::string_view players_path, EntityManager &entities);

   mb::result<mb::empty> join_player(minecpp::game::World &w, const std::string &name, game::PlayerId id);
   mb::result<nbt::player::v1::Player> load_player_data(minecpp::game::World &w, game::PlayerId id);

   mb::result<minecpp::util::Vec3> get_spawn_position(minecpp::game::World &w);
   mb::result<minecpp::game::player::Player &> get_player(game::PlayerId id) override;
   mb::result<minecpp::game::entity::Entity &> get_entity(game::PlayerId id);
   void for_each_player(const std::function<void(minecpp::game::player::Player &)> &callback);
   void remove_player(game::PlayerId id);
   void remap_ids();
   std::size_t player_count();

   [[nodiscard]] std::vector<game::player::Status> player_status_list() const;
};

}// namespace minecpp::service::engine
