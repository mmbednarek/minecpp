#pragma once
#include <boost/uuid/uuid.hpp>
#include <functional>
#include <mb/result.h>
#include <minecpp/game/Entity.h>
#include <minecpp/game/player/Player.h>
#include <minecpp/game/player/Provider.hpp>
#include <minecpp/game/Team.h>
#include <minecpp/nbt/player/v1/Player.nbt.h>
#include <random>
#include <vector>

namespace minecpp::entity {
class EntitySystem;
class Entity;
}// namespace minecpp::entity

namespace minecpp::service::engine {

class EntityManager;

using encoded_uuid = std::pair<mb::u64, mb::u64>;

class PlayerManager : public game::player::Provider
{
   using PlayerIndex = std::vector<game::player::Player>::size_type;

 public:
   PlayerManager(entity::EntitySystem &entity_system, game::BlockPosition spawn_position);

   mb::result<mb::empty> join_player(minecpp::game::IWorld &w, const std::string &name, game::PlayerId id);
   mb::result<game::Entity> respawn_player(game::IWorld &world, game::PlayerId player_id);
   mb::result<nbt::player::v1::Player> load_player_data(minecpp::game::IWorld &w, game::PlayerId id) const;
   mb::emptyres mark_player_as_dead(game::PlayerId id);

   mb::result<minecpp::game::player::Player &> get_player(game::PlayerId id) override;
   std::optional<game::PlayerId> get_player_id_by_entity_id(game::EntityId id);
   void for_each_player(const std::function<void(minecpp::game::player::Player &)> &callback);
   void remove_player(game::PlayerId id);
   void remap_ids();
   std::size_t player_count();

   [[nodiscard]] std::vector<game::player::Status> player_status_list() const;

 private:
   entity::EntitySystem &m_entity_system;

   std::vector<game::player::Player> m_players;
   std::map<encoded_uuid, PlayerIndex> m_id_map;
   std::map<game::EntityId, game::PlayerId> m_player_entity_map;
   std::default_random_engine m_rand_engine;
   game::BlockPosition m_spawn_position;
};

}// namespace minecpp::service::engine
