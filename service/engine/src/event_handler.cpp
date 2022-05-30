#include "event_handler.h"
#include "dispatcher.h"
#include "entities.h"
#include "players.h"
#include <minecpp/chat/chat.h>
#include <minecpp/format/format.h>
#include <minecpp/game/world.h>
#include <minecpp/repository/block.h>
#include <minecpp/repository/item.h>
#include <minecpp/repository/state.h>

namespace minecpp::service::engine {

EventHandler::EventHandler(Dispatcher &dispatcher, PlayerManager &player_manager,
                           EntityManager &entity_manager, game::World &world) :
    m_dispatcher(dispatcher),
    m_player_manager(player_manager),
    m_entity_manager(entity_manager),
    m_world(world)
{
}

void EventHandler::handle_accept_player(const serverbound_v1::AcceptPlayer &event, player::Id player_id)
{
   spdlog::info("player accept request from {}", event.name());
   auto join_result = m_player_manager.join_player(m_world, event.name(), player_id);
   if (!join_result.ok()) {
      m_dispatcher.deny_player(player_id, join_result.msg());
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

      if (event.message()[0] == '/') {
         if (event.message().starts_with("/sb ")) {
            format::Builder msg;
            // set block
            auto block_state = std::stoi(event.message().substr(4, event.message().size()));
            if (block_state >= 0 &&
                static_cast<mb::u64>(block_state) <= repository::StateManager::the().state_count()) {
               msg.bold(format::Color::Green, "INFO").text(" changed selected color to ");

               m_selected_block = static_cast<game::BlockState>(block_state);
               const auto [block_id, state] =
                       repository::StateManager::the().parse_block_id(m_selected_block);
               auto &block = MB_ESCAPE(repository::Block::the().get_by_id(block_id));
               msg.text(format::Color::Yellow, block.tag());

               if (!block.is_single_state()) {
                  msg.text(" (");
                  std::stringstream ss;
                  bool first = true;
                  for (const auto &[state, value] : block.state_range(state)) {
                     if (first) {
                        first = false;
                     } else {
                        msg.text(", ");
                     }
                     msg.text(format::Color::Yellow, state.name())
                             .text("=")
                             .text(format::Color::White, state.value_from_index(value));
                  }
                  msg.text(")");
               }
            } else {
               msg.bold(format::Color::Yellow, "WARN")
                       .text(fmt::format(" invalid state id "))
                       .bold(format::Color::White, fmt::format("{}", block_state));
            }
            m_dispatcher.send_chat(chat::MessageType::SystemMessage, msg.build());
         } else if (event.message().starts_with("/give ")) {
            auto item_tag = event.message().substr(6, event.message().size());
            auto res      = repository::Item::the().find_id_by_tag(item_tag);
            if (!res.ok()) {
               format::Builder builder;
               builder.bold(format::Color::Red, "ERR ").text(fmt::format("invalid item tag {}", item_tag));
               m_dispatcher.send_chat(chat::MessageType::SystemMessage, builder.build());
               return;
            }

            auto item_id = res.unwrap();
            auto &player = MB_ESCAPE(m_player_manager.get_player(player_id));

            if (!player.inventory().add_item(item_id, 64)) {
               format::Builder builder;
               builder.bold(format::Color::Red, "ERR ").text("player inventory is full");
               m_dispatcher.send_chat(chat::MessageType::SystemMessage, builder.build());
               return;
            }

            format::Builder builder;
            builder.bold(format::Color::Green, "INFO ")
                    .text(fmt::format("giving {} to the player {}.", item_id, player.name()));
            m_dispatcher.send_chat(chat::MessageType::SystemMessage, builder.build());

            send_inventory_data(player);
         }
         return;
      }

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

   /*
   switch (status) {
   case game::PlayerDiggingState::Digging:
   case game::PlayerDiggingState::CanceledDigging: {
      auto block_position = game::BlockPosition::from_proto(event.block_position());
      auto block_state_res = m_world.get_block(block_position);
      if (!block_state_res.ok()) {
         spdlog::info("error fetching block state: {}", block_state_res.msg());
         return;
      }
      auto block_state = block_state_res.unwrap();
      m_dispatcher.acknowledge_player_digging(player_id, block_position, block_state, status, true);
   } break;
   case game::PlayerDiggingState::FinishedDigging: {
      auto block_position = game::BlockPosition::from_proto(event.block_position());
      m_dispatcher.acknowledge_player_digging(player_id, block_position, 0, status, true);
      m_dispatcher.update_block(block_position, 0);
      m_world.set_block(block_position, 0);
   } break;
   default: break;
   }
    */

   switch (status) {
   case game::PlayerDiggingState::Digging:
   case game::PlayerDiggingState::CanceledDigging:
   case game::PlayerDiggingState::FinishedDigging: {
      auto block_position = game::BlockPosition::from_proto(event.block_position());
      m_dispatcher.acknowledge_player_digging(player_id, block_position, 0, status, true);
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
      spdlog::error("error loading chunks: {}", res.msg());
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

   auto &player    = MB_ESCAPE(m_player_manager.get_player(player_id));
   auto item_slot  = player.inventory().active_item();
   auto &item      = MB_ESCAPE(repository::Item::the().get_by_id(item_slot.item_id));
   auto id         = MB_ESCAPE(repository::Block::the().find_id_by_tag(item.corresponding_block_tag()));
   auto base_state = repository::StateManager::the().block_base_state(id);

   m_world.set_block(neighbour_position, static_cast<unsigned int>(base_state));
   m_dispatcher.update_block(neighbour_position, static_cast<unsigned int>(base_state));
}

void EventHandler::send_inventory_data(const player::Player &player)
{
   for (player::SlotId id = 9; id < 5 * 9; ++id) {
      auto slot = player.inventory().item_at(id);
      //      if (slot.count == 0)
      //         continue;

      m_dispatcher.set_inventory_slot(player.id(), slot.item_id, id, slot.count);
   }
}

void EventHandler::handle_change_inventory_item(const serverbound_v1::ChangeInventoryItem &event,
                                                player::Id player_id)
{
   auto &player = MB_ESCAPE(m_player_manager.get_player(player_id));
   player.inventory().set_slot(static_cast<player::SlotId>(event.slot_id()),
                               player::ItemSlot{
                                       .item_id = static_cast<game::item::ItemId>(event.item_id().id()),
                                       .count   = static_cast<size_t>(event.item_count()),
                               });

   spdlog::info("setting slot {} to {} {}", event.slot_id(), event.item_id().id(), event.item_count());

   m_dispatcher.set_inventory_slot(player_id, static_cast<game::item::ItemId>(event.item_id().id()),
                                   static_cast<player::SlotId>(event.slot_id()),
                                   static_cast<size_t>(event.item_count()));
}

void EventHandler::handle_change_held_item(const serverbound_v1::ChangeHeldItem &event, player::Id player_id)
{
   auto &player = MB_ESCAPE(m_player_manager.get_player(player_id));
   player.inventory().set_hot_bar_slot(static_cast<size_t>(event.slot()));
}

}// namespace minecpp::service::engine
