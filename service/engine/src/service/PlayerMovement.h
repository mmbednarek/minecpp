#pragma once

#include "minecpp/game/Types.hpp"
#include "minecpp/math/Rotation.h"
#include "minecpp/math/Vector3.h"

namespace minecpp::service::engine {
class PlayerManager;
class World;
class Dispatcher;
}// namespace minecpp::service::engine

namespace minecpp::service::engine::service {

class PlayerMovement
{
 public:
   PlayerMovement(PlayerManager &player_manager, World &world, Dispatcher &dispatcher);

   void handle_set_player_position(game::PlayerId player_id, const math::Vector3 &position,
                                   bool is_on_ground);
   void handle_set_player_rotation(game::PlayerId player_id, const math::Rotation &rotation);
   void handle_set_player_is_on_ground(game::PlayerId player_id, bool is_on_ground);

 private:
   PlayerManager &m_player_manager;
   World &m_world;
   Dispatcher &m_dispatcher;
};

}// namespace minecpp::service::engine::service
