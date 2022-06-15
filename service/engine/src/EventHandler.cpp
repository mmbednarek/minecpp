#include "EventHandler.h"
#include "Dispatcher.h"
#include "Entities.h"
#include "Players.h"
#include <minecpp/chat/Chat.h>
#include <minecpp/command/Command.h>
#include <minecpp/command/core/Echo.h>
#include <minecpp/command/core/Format.h>
#include <minecpp/command/core/Give.h>
#include <minecpp/format/Format.h>
#include <minecpp/game/World.h>
#include <minecpp/repository/Block.h>
#include <minecpp/repository/Item.h>
#include <minecpp/repository/State.h>

namespace minecpp::service::engine {

EventHandler::EventHandler(Dispatcher &dispatcher, PlayerManager &player_manager,
                           EntityManager &entity_manager, game::World &world) :
    m_dispatcher(dispatcher),
    m_player_manager(player_manager),
    m_entity_manager(entity_manager),
    m_world(world),
    m_command_std_stream(m_dispatcher),
    m_command_context(m_command_manager, command::g_null_stream, m_command_std_stream)
{
   m_command_manager.register_command<command::core::Echo>("echo");
   m_command_manager.register_command<command::core::Give>("give", m_player_manager);

   m_command_manager.register_command<command::core::Format>("black", format::Color::Black, false);
   m_command_manager.register_command<command::core::Format>("black-bold", format::Color::Black, true);
   m_command_manager.register_command<command::core::Format>("dark-blue", format::Color::DarkBlue, false);
   m_command_manager.register_command<command::core::Format>("dark-blue-bold", format::Color::DarkBlue, true);
   m_command_manager.register_command<command::core::Format>("dark-green", format::Color::DarkGreen, false);
   m_command_manager.register_command<command::core::Format>("dark-green-bold", format::Color::DarkGreen,
                                                             true);
   m_command_manager.register_command<command::core::Format>("dark-aqua", format::Color::DarkAqua, false);
   m_command_manager.register_command<command::core::Format>("dark-aqua-bold", format::Color::DarkAqua, true);
   m_command_manager.register_command<command::core::Format>("dark-red", format::Color::DarkRed, false);
   m_command_manager.register_command<command::core::Format>("dark-red-bold", format::Color::DarkRed, true);
   m_command_manager.register_command<command::core::Format>("dark-purple", format::Color::DarkPurple, false);
   m_command_manager.register_command<command::core::Format>("dark-purple-bold", format::Color::DarkPurple,
                                                             true);
   m_command_manager.register_command<command::core::Format>("gold", format::Color::Gold, false);
   m_command_manager.register_command<command::core::Format>("gold-bold", format::Color::Gold, true);
   m_command_manager.register_command<command::core::Format>("gray", format::Color::Gray, false);
   m_command_manager.register_command<command::core::Format>("gray-bold", format::Color::Gray, true);
   m_command_manager.register_command<command::core::Format>("darkgray", format::Color::DarkGray, false);
   m_command_manager.register_command<command::core::Format>("darkgray-bold", format::Color::DarkGray, true);
   m_command_manager.register_command<command::core::Format>("blue", format::Color::Blue, false);
   m_command_manager.register_command<command::core::Format>("blue-bold", format::Color::Blue, true);
   m_command_manager.register_command<command::core::Format>("green", format::Color::Green, false);
   m_command_manager.register_command<command::core::Format>("green-bold", format::Color::Green, true);
   m_command_manager.register_command<command::core::Format>("aqua", format::Color::Aqua, false);
   m_command_manager.register_command<command::core::Format>("aqua-bold", format::Color::Aqua, true);
   m_command_manager.register_command<command::core::Format>("red", format::Color::Red, false);
   m_command_manager.register_command<command::core::Format>("red-bold", format::Color::Red, true);
   m_command_manager.register_command<command::core::Format>("light-purple", format::Color::LightPurple,
                                                             false);
   m_command_manager.register_command<command::core::Format>("light-purple-bold", format::Color::LightPurple,
                                                             true);
   m_command_manager.register_command<command::core::Format>("yellow", format::Color::Yellow, false);
   m_command_manager.register_command<command::core::Format>("yellow-bold", format::Color::Yellow, true);
   m_command_manager.register_command<command::core::Format>("white", format::Color::White, false);
   m_command_manager.register_command<command::core::Format>("white-bold", format::Color::White, true);
}

void EventHandler::handle_accept_player(const serverbound_v1::AcceptPlayer &event, player::Id player_id)
{
   spdlog::info("player accept request from {}", event.name());
   auto join_result = m_player_manager.join_player(m_world, event.name(), player_id);
   if (!join_result.ok()) {
      m_dispatcher.deny_player(player_id, join_result.err()->msg());
      return;
   }

   auto &player = MB_ESCAPE(m_player_manager.get_player(player_id));// We can assume no problems here
   auto &entity = MB_ESCAPE(m_player_manager.get_entity(player_id));

   if (!player.inventory().add_item(1, 64)) {
      spdlog::info("player inventory is full");
   }
   if (!player.inventory().add_item(2, 32)) {
      spdlog::info("player inventory is full");
   }

   m_dispatcher.accept_player(player, entity);
   m_dispatcher.add_player(player.id(), player.name(), static_cast<mb::u32>(player.ping()));
   m_dispatcher.spawn_player(player.id(), player.entity_id(), entity.get_pos(),
                             entity::Rotation(entity.get_yaw(), entity.get_pitch()));
   m_dispatcher.send_chat(chat::MessageType::SystemMessage, chat::format_join_message(player.name()));
}

void EventHandler::handle_set_player_position(const serverbound_v1::SetPlayerPosition &event,
                                              player::Id player_id)
{
   auto &entity         = MB_ESCAPE(m_player_manager.get_entity(player_id));
   auto player_position = entity::read_entity_position(event.position());
   entity.set_pos(m_dispatcher, player_position);
   MB_ESCAPE(m_player_manager.get_player(player_id)).on_movement(m_world, player_position);
}

void EventHandler::handle_set_player_rotation(const serverbound_v1::SetPlayerRotation &event,
                                              player::Id player_id)
{
   auto &entity = MB_ESCAPE(m_player_manager.get_entity(player_id));
   entity.set_rot(event.rotation().yaw(), event.rotation().pitch());
   m_dispatcher.entity_look(player_id, entity.get_id(),
                            entity::Rotation(entity.get_yaw(), entity.get_pitch()));
}

void EventHandler::handle_chat_message(const serverbound_v1::ChatMessage &event, player::Id player_id)
{
   try {
      if (event.message().empty())
         return;

      auto &player = MB_ESCAPE(m_player_manager.get_player(player_id));

      spdlog::info("CHAT [{}] {}", player.name(), event.message());
      m_dispatcher.send_chat(chat::MessageType::PlayerMessage,
                             chat::format_chat_message(player.name(), event.message()));
   } catch (std::runtime_error &err) {
      spdlog::error("handle chat message: {}", err.what());
   }
}

void EventHandler::handle_remove_player(const serverbound_v1::RemovePlayer &event, player::Id player_id)
{
   auto &player = MB_ESCAPE(m_player_manager.get_player(player_id));
   m_dispatcher.send_chat(chat::MessageType::SystemMessage, chat::format_left_message(player.name()));
   m_dispatcher.remove_player(player_id, player.entity_id());
   m_player_manager.remove_player(player_id);
}

void EventHandler::handle_player_digging(const serverbound_v1::PlayerDigging &event, player::Id player_id)
{
   auto status = static_cast<game::PlayerDiggingState>(event.state());
   switch (status) {
   case game::PlayerDiggingState::Digging:
   case game::PlayerDiggingState::CanceledDigging:
   case game::PlayerDiggingState::FinishedDigging: {
      auto block_position = game::BlockPosition::from_proto(event.block_position());
      m_dispatcher.acknowledge_block_change(player_id, event.sequence_id());
      m_dispatcher.update_block(block_position, 0);
      m_world.set_block(block_position, 0);
   } break;
   default: break;
   }
}

void EventHandler::handle_update_ping(const serverbound_v1::UpdatePing &event, player::Id player_id)
{
   auto &player = MB_ESCAPE(m_player_manager.get_player(player_id));
   player.set_ping(event.ping());
}

void EventHandler::handle_animate_hand(const serverbound_v1::AnimateHand &event, player::Id player_id)
{
   auto &player = MB_ESCAPE(m_player_manager.get_player(player_id));
   m_dispatcher.animate_hand(player_id, player.entity_id(), event.hand());
}

void EventHandler::handle_load_initial_chunks(const serverbound_v1::LoadInitialChunks &event,
                                              player::Id player_id)
{
   auto &player = MB_ESCAPE(m_player_manager.get_player(player_id));
   auto res     = player.load_chunks(m_world);
   if (!res.ok()) {
      spdlog::error("error loading chunks: {}", res.err()->msg());
   }

   auto &entity = MB_ESCAPE(m_entity_manager.get_entity(player.entity_id()));

   send_inventory_data(player);

   m_dispatcher.player_list(player.id(), m_player_manager.player_status_list());
   m_dispatcher.entity_list(player.id(), m_entity_manager.entities());
}

void EventHandler::handle_block_placement(const serverbound_v1::BlockPlacement &event, player::Id player_id)
{
   auto face               = game::face_from_proto(event.face());
   auto block_position     = game::BlockPosition::from_proto(event.position());
   auto neighbour_position = block_position.neighbour_at(face);

   auto &player   = MB_ESCAPE(m_player_manager.get_player(player_id));
   auto item_slot = player.inventory().active_item();

   if (item_slot.count == 0)
      return;

   auto &item = MB_ESCAPE(repository::Item::the().get_by_id(static_cast<std::size_t>(item_slot.item_id)));
   if (not item.is_block())
      return;

   if (not player.inventory().take_from_active_slot(1)) {
      spdlog::error("cannot take item from player inventory");
      return;
   }

   auto source_block_state = m_world.get_block(neighbour_position);
   if (source_block_state.has_failed()) {
      spdlog::error("could not obtain source block");
      return;
   }

   const auto air_id = static_cast<int>(repository::Block::the().find_id_by_tag("minecraft:air").unwrap(0));
   const auto water_id =
           static_cast<int>(repository::Block::the().find_id_by_tag("minecraft:water").unwrap(0));

   auto [source_block_id, _] = repository::StateManager::the().parse_block_id(*source_block_state);

   if (source_block_id != air_id && source_block_id != water_id) {
      return;
   }

   auto id    = MB_ESCAPE(repository::Block::the().find_id_by_tag(item.corresponding_block_tag()));
   auto block = repository::Block::the().get_by_id(id);
   auto state = repository::StateManager::the().block_base_state(static_cast<int>(id));

   if (block->find_state("waterlogged") != std::nullopt) {
      if (source_block_id == water_id) {
         state = repository::encode_block_by_tag(block->tag(), std::make_pair("waterlogged", "true"));
      } else {
         state = repository::encode_block_by_tag(block->tag(), std::make_pair("waterlogged", "false"));
      }
   }

   auto res = m_world.set_block(neighbour_position, state);
   if (not res.ok()) {
      spdlog::error("could not set block: {}", res.err()->msg());
   }

   m_dispatcher.acknowledge_block_change(player_id, event.sequence_id());
   m_dispatcher.update_block(neighbour_position, state);
}

void EventHandler::send_inventory_data(const player::Player &player)
{
   for (game::SlotId id = 9; id < 5 * 9; ++id) {
      auto slot = player.inventory().item_at(id);
      m_dispatcher.set_inventory_slot(player.id(), slot.item_id, id, slot.count);
   }
}

void EventHandler::handle_change_inventory_item(const serverbound_v1::ChangeInventoryItem &event,
                                                player::Id player_id)
{
   auto &player = MB_ESCAPE(m_player_manager.get_player(player_id));
   player.inventory().set_slot(static_cast<game::SlotId>(event.slot_id()),
                               player::ItemSlot{
                                       .item_id = static_cast<game::item::ItemId>(event.item_id().id()),
                                       .count   = static_cast<size_t>(event.item_count()),
                               });

   spdlog::info("setting slot {} to {} {}", event.slot_id(), event.item_id().id(), event.item_count());

   m_dispatcher.set_inventory_slot(player_id, static_cast<game::item::ItemId>(event.item_id().id()),
                                   static_cast<game::SlotId>(event.slot_id()),
                                   static_cast<size_t>(event.item_count()));
}

void EventHandler::handle_change_held_item(const serverbound_v1::ChangeHeldItem &event, player::Id player_id)
{
   auto &player = MB_ESCAPE(m_player_manager.get_player(player_id));
   player.inventory().set_hot_bar_slot(static_cast<size_t>(event.slot()));
}

void EventHandler::handle_issue_command(const serverbound_v1::IssueCommand &event, player::Id player_id)
{
   auto &player = MB_ESCAPE(m_player_manager.get_player(player_id));

   m_command_context.set_variable("player_id", std::make_shared<command::UUIDObject>(player_id));
   m_command_context.set_variable("player_name", std::make_shared<command::StringObject>(player.name()));

   auto res = m_command_manager.evaluate(m_command_context, event.command());
   if (res.has_value()) {
      format::Builder builder;
      builder.bold(format::Color::Red, "COMMAND FAILED ").text(res->message);
      m_dispatcher.send_chat(chat::MessageType::SystemMessage, builder.to_string());
   }
}

}// namespace minecpp::service::engine
