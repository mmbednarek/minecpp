#include "PlayerInterface.h"
#include "../Dispatcher.h"
#include "../PlayerManager.h"
#include "../World.h"

#include "minecpp/command/core/Core.h"
#include "minecpp/entity/Aliases.hpp"
#include "minecpp/entity/component/Inventory.h"
#include "minecpp/entity/component/Location.h"

#include <spdlog/spdlog.h>

namespace minecpp::service::engine::service {

PlayerInterface::PlayerInterface(PlayerManager &player_manager, World &world, Dispatcher &dispatcher) :
    m_player_manager{player_manager},
    m_world{world},
    m_dispatcher{dispatcher},
    m_command_std_stream(m_dispatcher),
    m_command_context(m_command_manager, command::g_null_stream, m_command_std_stream, &m_world)
{
   command::core::register_commands(m_command_manager);
}

void PlayerInterface::handle_change_inventory_item(game::PlayerId player_id, game::SlotId slot_id,
                                                   const game::ItemSlot &item_slot)
{
   auto entity = this->m_world.player_entity(player_id);
   if (entity.has_failed()) {
      spdlog::warn("player-interface: player entity is invalid: {}", entity.err()->msg());
      return;
   }

   entity->component<InventoryComponent>().set_slot(m_dispatcher, slot_id, item_slot);
}

void PlayerInterface::handle_change_held_item(game::PlayerId player_id, int active_slot_id)
{
   auto entity = this->m_world.player_entity(player_id);
   if (entity.has_failed()) {
      spdlog::warn("player-interface: player entity is invalid: {}", entity.err()->msg());
      return;
   }

   auto &inventory = entity->component<InventoryComponent>();
   inventory.set_active_item(m_dispatcher, active_slot_id);
}

void PlayerInterface::handle_drop_carried_item(game::PlayerId player_id, bool is_whole_stack)
{
   auto entity = this->m_world.player_entity(player_id);
   if (not entity->has_component<InventoryComponent>())
      return;

   entity->component<InventoryComponent>().drop_carried_item(m_world, is_whole_stack);
}

void PlayerInterface::handle_set_carried_item(game::PlayerId player_id, const game::ItemSlot &item_slot)
{
   auto entity = this->m_world.player_entity(player_id);
   if (entity.has_failed()) {
      spdlog::warn("player entity is invalid: {}", entity.err()->msg());
      return;
   }

   if (not entity->has_component<InventoryComponent>())
      return;

   entity->component<InventoryComponent>().set_carried_item(item_slot);
}

void PlayerInterface::handle_chat_message(game::PlayerId player_id, std::string_view message)
{
   try {
      if (message.empty())
         return;

      auto player = m_player_manager.get_player(player_id);
      if (player.has_failed()) {
         spdlog::warn("player-interface: no player with id: {}", util::uuid_to_string(player_id));
         return;
      }

      spdlog::info("player-interface: player message: <{}> {}", player->name(), message);
      m_dispatcher.send_chat(chat::MessageType::PlayerMessage,
                             chat::format_chat_message(player->name(), message));
   } catch (std::runtime_error &err) {
      spdlog::error("handle chat message: {}", err.what());
   }
}

void PlayerInterface::handle_issue_command(game::PlayerId player_id, std::string_view command)
{
   auto player = m_player_manager.get_player(player_id);
   if (player.has_failed()) {
      spdlog::warn("player is invalid: {}", player.err()->msg());
      return;
   }

   auto entity = this->m_world.player_entity(player_id);
   if (entity.has_failed()) {
      spdlog::warn("player entity is invalid: {}", entity.err()->msg());
      return;
   }

   m_command_context.set_variable("player_id", std::make_shared<command::UUIDObject>(player_id));
   m_command_context.set_variable("player_name", std::make_shared<command::StringObject>(player->name()));
   m_command_context.set_variable("entity_id", std::make_shared<command::IntObject>(entity->id()));

   auto player_pos =
           game::BlockPosition::from_vector3(entity->component<entity::component::Location>().position());
   m_command_context.set_variable("here", std::make_shared<command::BlockPositionObject>(player_pos));

   auto res = m_command_manager.evaluate(m_command_context, command);
   if (res.has_value()) {
      format::Builder builder;
      builder.bold(format::Color::Red, "COMMAND FAILED ").text(res->message);
      m_dispatcher.send_direct_chat(player_id, chat::MessageType::PlayerMessage, builder.to_string());
   }
}

}// namespace minecpp::service::engine::service
