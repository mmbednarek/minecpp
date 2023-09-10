#pragma once

#include "minecpp/game/Types.hpp"

#include <string_view>

namespace minecpp::service::engine {
class PlayerManager;
class World;
class Dispatcher;
}// namespace minecpp::service::engine

namespace minecpp::service::engine::service {

class PlayerSession
{
 public:
   PlayerSession(PlayerManager &player_manager, World &world, Dispatcher &dispatcher);

   void handle_accept_player(game::PlayerId player_id, std::string_view name);
   void handle_remove_player(game::PlayerId player_id);
   void handle_update_ping(game::PlayerId player_id, int ping);
   void handle_pre_initial_chunks(game::PlayerId player_id);
   void handle_post_initial_chunks(game::PlayerId player_id);
   void handle_request_respawn(game::PlayerId player_id);

 private:
   PlayerManager &m_player_manager;
   World &m_world;
   Dispatcher &m_dispatcher;
};

}// namespace minecpp::service::engine::service
