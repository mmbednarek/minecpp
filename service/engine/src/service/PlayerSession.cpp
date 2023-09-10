#include "PlayerSession.h"
#include "../Dispatcher.h"
#include "../PlayerManager.h"
#include "../World.h"

#include "minecpp/entity/Aliases.hpp"
#include "minecpp/entity/component/Abilities.h"
#include "minecpp/entity/component/Inventory.h"
#include "minecpp/entity/component/Location.h"
#include "minecpp/entity/component/Player.h"
#include "minecpp/entity/component/Streamer.h"

#include <spdlog/spdlog.h>

namespace minecpp::service::engine::service {

PlayerSession::PlayerSession(PlayerManager &player_manager, World &world, Dispatcher &dispatcher) :
    m_player_manager(player_manager),
    m_world(world),
    m_dispatcher(dispatcher)
{
}

void PlayerSession::handle_accept_player(game::PlayerId player_id, std::string_view name)
{
   auto join_result = m_player_manager.join_player(m_world, std::string{name}, player_id);
   if (!join_result.ok()) {
      m_dispatcher.deny_player(player_id, join_result.err()->msg());
      return;
   }

   spdlog::info("player-session: player {} has joined", name);

   auto entity = this->m_world.player_entity(player_id);
   if (entity.has_failed()) {
      spdlog::warn("player-session: player entity is invalid: {}", entity.err()->msg());
      return;
   }

   auto &inventory = entity->component<InventoryComponent>();
   if (inventory.add_item_by_tag(m_dispatcher, "minecraft:bow", 1).has_failed()) {
      spdlog::warn("player-session: could not add item: {}", entity.err()->msg());
   }
   if (inventory.add_item_by_tag(m_dispatcher, "minecraft:iron_sword", 1).has_failed()) {
      spdlog::warn("player-session: could not add item: {}", entity.err()->msg());
   }
   if (inventory.add_item_by_tag(m_dispatcher, "minecraft:apple", 8).has_failed()) {
      spdlog::warn("player-session: could not add item: {}", entity.err()->msg());
   }
   if (inventory.add_item_by_tag(m_dispatcher, "minecraft:arrow", 64).has_failed()) {
      spdlog::warn("player-session: could not add item: {}", entity.err()->msg());
   }
   if (inventory.add_item_by_tag(m_dispatcher, "minecraft:dirt", 64).has_failed()) {
      spdlog::warn("player-session: could not add item: {}", entity.err()->msg());
   }

   if (not entity->has_component<entity::component::Abilities>()) {
      m_dispatcher.deny_player(player_id, "Player's entity doesn't have abilities component");
   }

   auto player = m_player_manager.get_player(player_id);
   if (player.has_failed()) {
      spdlog::warn("player-session: player ID is invalid: {}", player.err()->msg());
      return;
   }

   m_dispatcher.accept_player(*player);
   m_dispatcher.add_player(player_id, player->name(), static_cast<mb::u32>(player->ping()));

   m_dispatcher.send_chat(chat::MessageType::SystemMessage, chat::format_join_message(player->name()));

   m_dispatcher.send_direct_chat(player_id, chat::MessageType::PlayerMessage,
                                 format::Builder()
                                         .bold(format::Color::Green, "Welcome ")
                                         .bold(format::Color::Green, player->name())
                                         .bold(format::Color::Green, "!")
                                         .to_string());
   m_dispatcher.send_direct_chat(
           player_id, chat::MessageType::PlayerMessage,
           format::Builder()
                   .text(format::Color::Gray, "------------------------------------------------")
                   .to_string());
   m_dispatcher.send_direct_chat(
           player_id, chat::MessageType::PlayerMessage,
           format::Builder().text("This server implementation is under development").to_string());
   m_dispatcher.send_direct_chat(player_id, chat::MessageType::PlayerMessage,
                                 format::Builder()
                                         .text("GitHub repository: ")
                                         .text(format::Color::Gold, "mmbednarek/minecpp")
                                         .to_string());
   m_dispatcher.send_direct_chat(player_id, chat::MessageType::PlayerMessage,
                                 format::Builder().text("").to_string());
   m_dispatcher.send_direct_chat(player_id, chat::MessageType::PlayerMessage,
                                 format::Builder()
                                         .text("When something breaks type ")
                                         .text(format::Color::Yellow, "/sync ")
                                         .to_string());
   m_dispatcher.send_direct_chat(
           player_id, chat::MessageType::PlayerMessage,
           format::Builder()
                   .text(format::Color::Gray, "------------------------------------------------")
                   .to_string());
   m_dispatcher.synchronise_player_position_and_rotation(player_id,
                                                         entity->component<LocationComponent>().position(),
                                                         entity->component<RotationComponent>().rotation());

   this->handle_pre_initial_chunks(player_id);
}

void PlayerSession::handle_remove_player(game::PlayerId player_id)
{
   auto player = m_player_manager.get_player(player_id);
   if (player.has_failed()) {
      spdlog::warn("player-session: requested removal of player with UUID {}, no such player exists",
                   util::uuid_to_string(player_id));
      return;
   }

   spdlog::info("player-session: player {} has left", player->name());

   auto entity_id = player->entity_id();

   m_dispatcher.send_chat(chat::MessageType::SystemMessage, chat::format_left_message(player->name()));
   m_dispatcher.remove_player(player_id, entity_id);

   m_world.entity_system().destroy_entity(entity_id);
   m_player_manager.remove_player(player_id);
}

void PlayerSession::handle_update_ping(game::PlayerId player_id, int ping)
{
   auto player = m_player_manager.get_player(player_id);
   if (player.has_failed()) {
      spdlog::error("no player with id {}", util::uuid_to_string(player_id));
      return;
   }
   player->set_ping(ping);
}

void PlayerSession::handle_pre_initial_chunks(game::PlayerId player_id)
{
   spdlog::info("pre initial chunks!");
   auto entity = this->m_world.player_entity(player_id);
   if (entity.has_failed()) {
      spdlog::warn("player entity is invalid: {}", entity.err()->msg());
      return;
   }
   assert(entity->has_component<LocationComponent>());
   assert(entity->has_component<StreamerComponent>());
   assert(entity->has_component<InventoryComponent>());

   m_dispatcher.player_list(player_id, m_player_manager.player_status_list());

   auto result = entity->component<StreamerComponent>().send_all_visible_chunks(
           m_world, player_id, entity->component<LocationComponent>().position());
   if (result.has_failed()) {
      spdlog::error("error loading chunks: {}", result.err()->msg());
      return;
   }

   this->handle_post_initial_chunks(player_id);
}

void PlayerSession::handle_post_initial_chunks(game::PlayerId player_id)
{
   spdlog::info("post initial chunks!");
   auto player = m_player_manager.get_player(player_id);
   if (player.has_failed()) {
      spdlog::warn("couldn't get player: {}", player.err()->msg());
      return;
   }

   player->set_has_loaded_initial_chunks(true);

   auto entity = this->m_world.player_entity(player_id);
   if (entity.has_failed()) {
      spdlog::warn("player entity is invalid: {}", entity.err()->msg());
      return;
   }
   assert(entity->has_component<PlayerComponent>());
   assert(entity->has_component<LocationComponent>());
   assert(entity->has_component<RotationComponent>());

   entity->component<PlayerComponent>().init_visible_entities(
           m_dispatcher, m_world.entity_system(), entity->component<LocationComponent>().position());

   entity->component<InventoryComponent>().synchronize_inventory(m_dispatcher);

   m_dispatcher.update_chunk_position(
           player_id, ChunkPosition::from_position(entity->component<LocationComponent>().position()));

   m_dispatcher.synchronise_player_position_and_rotation(player_id,
                                                         entity->component<LocationComponent>().position(),
                                                         entity->component<RotationComponent>().rotation());
   m_dispatcher.teleport_entity(entity->id(), entity->component<LocationComponent>().position(),
                                entity->component<RotationComponent>().rotation(),
                                entity->component<LocationComponent>().is_on_ground());

   m_dispatcher.set_spawn_position(player_id, game::BlockPosition(),
                                   entity->component<entity::component::Rotation>().pitch_degrees());
}

void PlayerSession::handle_request_respawn(game::PlayerId player_id)
{
   auto entity = m_player_manager.respawn_player(m_world, player_id);
   if (entity.has_failed())
      return;

   m_dispatcher.respawn_player(player_id);
   m_dispatcher.set_health_and_food(player_id, 20.0f, 20, 5.0f);

   m_dispatcher.synchronise_player_position_and_rotation(player_id,
                                                         entity->component<LocationComponent>().position(),
                                                         entity->component<RotationComponent>().rotation());

   auto result = entity->component<StreamerComponent>().send_all_visible_chunks(
           m_world, player_id, entity->component<LocationComponent>().position());
   if (result.has_failed()) {
      spdlog::error("error loading chunks: {}", result.err()->msg());
      return;
   }

   entity->component<InventoryComponent>().synchronize_inventory(m_dispatcher);

   m_dispatcher.synchronise_player_position_and_rotation(player_id,
                                                         entity->component<LocationComponent>().position(),
                                                         entity->component<RotationComponent>().rotation());

   m_dispatcher.spawn_entity(entity->id());
}

}// namespace minecpp::service::engine::service
