#include "PlayerMovement.h"
#include "../PlayerManager.h"
#include "../World.h"

#include "minecpp/entity/Aliases.hpp"
#include "minecpp/entity/component/Location.h"

#include <spdlog/spdlog.h>

namespace minecpp::service::engine::service {

PlayerMovement::PlayerMovement(PlayerManager &player_manager, World &world, Dispatcher &dispatcher) :
    m_player_manager(player_manager),
    m_world(world),
    m_dispatcher(dispatcher)
{
}

void PlayerMovement::handle_set_player_position(game::PlayerId player_id, const math::Vector3 &position,
                                                bool is_on_ground)
{
   auto player = m_player_manager.get_player(player_id);
   if (player.has_failed()) {
      spdlog::warn("couldn't get player: {}", player.err()->msg());
      return;
   }

   // to set position player needs to load initial chunks first
   if (not player->has_loaded_initial_chunks())
      return;

   auto entity = this->m_world.player_entity(player_id);
   if (entity.has_failed()) {
      spdlog::warn("player entity is invalid: {}", entity.err()->msg());
      return;
   }

   if (not entity->has_component<LocationComponent>())
      return;

   auto player_position = position;
   auto &location       = entity->component<LocationComponent>();
   location.set_position(m_world, *entity, player_position, is_on_ground);
}

void PlayerMovement::handle_set_player_rotation(game::PlayerId player_id, const math::Rotation &rotation)
{
   auto player = m_player_manager.get_player(player_id);
   if (player.has_failed()) {
      spdlog::warn("couldn't get player: {}", player.err()->msg());
      return;
   }

   // to set position player needs to load initial chunks first
   if (not player->has_loaded_initial_chunks())
      return;

   auto entity = this->m_world.player_entity(player_id);
   if (entity.has_failed()) {
      spdlog::warn("player entity is invalid: {}", entity.err()->msg());
      return;
   }

   auto &location           = entity->component<LocationComponent>();
   auto &rotation_component = entity->component<RotationComponent>();
   rotation_component.set_rotation(m_dispatcher, location.position(), rotation);
}

void PlayerMovement::handle_set_player_is_on_ground(game::PlayerId player_id, bool is_on_ground)
{
   auto entity = this->m_world.player_entity(player_id);
   if (entity.has_failed()) {
      spdlog::warn("player-movement: player entity is invalid: {}", entity.err()->msg());
      return;
   }

   if (not entity->has_component<LocationComponent>())
      return;

   entity->component<LocationComponent>().set_is_on_ground(m_world, *entity, is_on_ground);
}

}// namespace minecpp::service::engine::service
