#include "EventHandler.h"
#include "Dispatcher.h"
#include "minecpp/entity/component/Velocity.h"
#include "Players.h"
#include <minecpp/chat/Chat.h>
#include <minecpp/command/Command.h>
#include <minecpp/command/core/Echo.h>
#include <minecpp/command/core/Format.h>
#include <minecpp/command/core/Give.h>
#include <minecpp/command/core/ReloadChunk.h>
#include <minecpp/command/core/Sync.h>
#include <minecpp/controller/block/Door.h>
#include <minecpp/controller/block/Fence.h>
#include <minecpp/controller/block/Stairs.h>
#include <minecpp/controller/block/Torch.h>
#include <minecpp/controller/block/Wood.h>
#include <minecpp/entity/component/Abilities.h>
#include <minecpp/entity/component/Health.h>
#include <minecpp/entity/component/Inventory.h>
#include <minecpp/entity/component/Location.h>
#include <minecpp/entity/component/StreamingComponent.h>
#include <minecpp/entity/EntitySystem.h>
#include <minecpp/entity/factory/Item.h>
#include <minecpp/format/Format.h>
#include <minecpp/game/IWorld.h>
#include <minecpp/repository/Block.h>
#include <minecpp/repository/Item.h>
#include <minecpp/repository/State.h>
#include <minecpp/world/BlockState.h>
#include <spdlog/spdlog.h>

namespace minecpp::service::engine {

EventHandler::EventHandler(Dispatcher &dispatcher, PlayerManager &player_manager,
                           entity::EntitySystem &entity_system, game::IWorld &world,
                           controller::BlockManager &block_manager) :
    m_dispatcher(dispatcher),
    m_player_manager(player_manager),
    m_entity_system(entity_system),
    m_world(world),
    m_command_std_stream(m_dispatcher),
    m_command_context(m_command_manager, command::g_null_stream, m_command_std_stream, &m_world),
    m_block_manager(block_manager)
{
   m_command_manager.register_command<command::core::Echo>();
   m_command_manager.register_command<command::core::Give>();
   m_command_manager.register_command<command::core::ReloadChunk>();
   m_command_manager.register_command<command::core::Sync>();

   m_command_manager.register_command_as<command::core::Format>("black", format::Color::Black, false);
   m_command_manager.register_command_as<command::core::Format>("black-bold", format::Color::Black, true);
   m_command_manager.register_command_as<command::core::Format>("dark-blue", format::Color::DarkBlue, false);
   m_command_manager.register_command_as<command::core::Format>("dark-blue-bold", format::Color::DarkBlue,
                                                                true);
   m_command_manager.register_command_as<command::core::Format>("dark-green", format::Color::DarkGreen,
                                                                false);
   m_command_manager.register_command_as<command::core::Format>("dark-green-bold", format::Color::DarkGreen,
                                                                true);
   m_command_manager.register_command_as<command::core::Format>("dark-aqua", format::Color::DarkAqua, false);
   m_command_manager.register_command_as<command::core::Format>("dark-aqua-bold", format::Color::DarkAqua,
                                                                true);
   m_command_manager.register_command_as<command::core::Format>("dark-red", format::Color::DarkRed, false);
   m_command_manager.register_command_as<command::core::Format>("dark-red-bold", format::Color::DarkRed,
                                                                true);
   m_command_manager.register_command_as<command::core::Format>("dark-purple", format::Color::DarkPurple,
                                                                false);
   m_command_manager.register_command_as<command::core::Format>("dark-purple-bold", format::Color::DarkPurple,
                                                                true);
   m_command_manager.register_command_as<command::core::Format>("gold", format::Color::Gold, false);
   m_command_manager.register_command_as<command::core::Format>("gold-bold", format::Color::Gold, true);
   m_command_manager.register_command_as<command::core::Format>("gray", format::Color::Gray, false);
   m_command_manager.register_command_as<command::core::Format>("gray-bold", format::Color::Gray, true);
   m_command_manager.register_command_as<command::core::Format>("darkgray", format::Color::DarkGray, false);
   m_command_manager.register_command_as<command::core::Format>("darkgray-bold", format::Color::DarkGray,
                                                                true);
   m_command_manager.register_command_as<command::core::Format>("blue", format::Color::Blue, false);
   m_command_manager.register_command_as<command::core::Format>("blue-bold", format::Color::Blue, true);
   m_command_manager.register_command_as<command::core::Format>("green", format::Color::Green, false);
   m_command_manager.register_command_as<command::core::Format>("green-bold", format::Color::Green, true);
   m_command_manager.register_command_as<command::core::Format>("aqua", format::Color::Aqua, false);
   m_command_manager.register_command_as<command::core::Format>("aqua-bold", format::Color::Aqua, true);
   m_command_manager.register_command_as<command::core::Format>("red", format::Color::Red, false);
   m_command_manager.register_command_as<command::core::Format>("red-bold", format::Color::Red, true);
   m_command_manager.register_command_as<command::core::Format>("light-purple", format::Color::LightPurple,
                                                                false);
   m_command_manager.register_command_as<command::core::Format>("light-purple-bold",
                                                                format::Color::LightPurple, true);
   m_command_manager.register_command_as<command::core::Format>("yellow", format::Color::Yellow, false);
   m_command_manager.register_command_as<command::core::Format>("yellow-bold", format::Color::Yellow, true);
   m_command_manager.register_command_as<command::core::Format>("white", format::Color::White, false);
   m_command_manager.register_command_as<command::core::Format>("white-bold", format::Color::White, true);

   for (auto wood_type : game::g_wood_types) {
      if (auto wood_id = repository::Block::the().find_id_by_tag(
                  fmt::format("minecraft:{}_wood", game::to_string(wood_type)));
          wood_id.ok()) {
         m_block_manager.register_controller<controller::block::Wood>(*wood_id);
      } else {
         spdlog::error("no such block id minecraft:{}_wood", game::to_string(wood_type));
      }

      if (auto log_id = repository::Block::the().find_id_by_tag(
                  fmt::format("minecraft:{}_log", game::to_string(wood_type)));
          log_id.ok()) {
         m_block_manager.register_controller<controller::block::Wood>(*log_id);
      } else {
         spdlog::error("no such block id minecraft:{}_log", game::to_string(wood_type));
      }

      if (auto door_id = repository::Block::the().find_id_by_tag(
                  fmt::format("minecraft:{}_door", game::to_string(wood_type)));
          door_id.ok()) {
         m_block_manager.register_controller<controller::block::Door>(*door_id);
      } else {
         spdlog::error("no such block id minecraft:{}_door", game::to_string(wood_type));
      }

      if (auto fence_id = repository::Block::the().find_id_by_tag(
                  fmt::format("minecraft:{}_fence", game::to_string(wood_type)));
          fence_id.ok()) {
         m_block_manager.register_controller<controller::block::Fence>(*fence_id);
      } else {
         spdlog::error("no such block id minecraft:{}_fence", game::to_string(wood_type));
      }

      if (auto stairs_id = repository::Block::the().find_id_by_tag(
                  fmt::format("minecraft:{}_stairs", game::to_string(wood_type)));
          stairs_id.ok()) {
         m_block_manager.register_controller<controller::block::Stairs>(*stairs_id);
      } else {
         spdlog::error("no such block id minecraft:{}_stairs", game::to_string(wood_type));
      }
   }

   if (auto stairs_id = repository::Block::the().find_id_by_tag("minecraft:stone_stairs"); stairs_id.ok()) {
      m_block_manager.register_controller<controller::block::Stairs>(*stairs_id);
   }
   if (auto stairs_id = repository::Block::the().find_id_by_tag("minecraft:cobblestone_stairs");
       stairs_id.ok()) {
      m_block_manager.register_controller<controller::block::Stairs>(*stairs_id);
   }
   if (auto stairs_id = repository::Block::the().find_id_by_tag("minecraft:stone_brick_stairs");
       stairs_id.ok()) {
      m_block_manager.register_controller<controller::block::Stairs>(*stairs_id);
   }

   if (auto torch_id = repository::Block::the().find_id_by_tag("minecraft:torch"); torch_id.ok()) {
      m_block_manager.register_controller<controller::block::Torch>(*torch_id);
   }
   if (auto torch_id = repository::Block::the().find_id_by_tag("minecraft:wall_torch"); torch_id.ok()) {
      m_block_manager.register_controller<controller::block::Torch>(*torch_id);
   }
}

void EventHandler::handle_accept_player(const serverbound_v1::AcceptPlayer &event, game::PlayerId player_id)
{
   //  Is chunk where player stands even loaded?

   spdlog::info("player accept request from {}", event.name());
   auto join_result = m_player_manager.join_player(m_world, event.name(), player_id);
   if (!join_result.ok()) {
      m_dispatcher.deny_player(player_id, join_result.err()->msg());
      return;
   }

   auto &player = MB_ESCAPE(m_player_manager.get_player(player_id));// We can assume no problems here
   auto entity  = m_entity_system.entity(player.entity_id());

   auto &inventory = entity.component<entity::component::Inventory>();
   if (not inventory.add_item(m_dispatcher, 1, 64)) {
      spdlog::info("player inventory is full");
   }
   if (not inventory.add_item(m_dispatcher, 2, 32)) {
      spdlog::info("player inventory is full");
   }

   if (not entity.has_component<entity::component::Abilities>()) {
      m_dispatcher.deny_player(player_id, "Player's entity doesn't have abilities component");
   }

   m_dispatcher.accept_player(player);
   m_dispatcher.add_player(player.id(), player.name(), static_cast<mb::u32>(player.ping()));
   m_dispatcher.spawn_player(player.id(), player.entity_id(),
                             entity.component<entity::component::Location>().position());
   m_dispatcher.send_chat(chat::MessageType::SystemMessage, chat::format_join_message(player.name()));

   m_dispatcher.send_direct_chat(player.id(), chat::MessageType::PlayerMessage,
                                 format::Builder()
                                         .bold(format::Color::Green, "Welcome ")
                                         .bold(format::Color::Green, player.name())
                                         .bold(format::Color::Green, "!")
                                         .to_string());
   m_dispatcher.send_direct_chat(
           player.id(), chat::MessageType::PlayerMessage,
           format::Builder()
                   .text(format::Color::Gray, "------------------------------------------------")
                   .to_string());
   m_dispatcher.send_direct_chat(
           player.id(), chat::MessageType::PlayerMessage,
           format::Builder().text("This server implementation is under development").to_string());
   m_dispatcher.send_direct_chat(player.id(), chat::MessageType::PlayerMessage,
                                 format::Builder()
                                         .text("To obtain a block please type ")
                                         .text(format::Color::Yellow, "/give ")
                                         .text(format::Color::Gold, "<block name>")
                                         .to_string());
   m_dispatcher.send_direct_chat(
           player.id(), chat::MessageType::PlayerMessage,
           format::Builder()
                   .text(format::Color::Gray, "------------------------------------------------")
                   .to_string());
   m_dispatcher.synchronise_player_position_and_rotation(
           player_id, entity.component<entity::component::Location>().position(),
           entity.component<entity::component::Rotation>().yaw(),
           entity.component<entity::component::Rotation>().pitch());
}

void EventHandler::handle_set_player_position(const serverbound_v1::SetPlayerPosition &event,
                                              game::PlayerId player_id)
{
   auto player = m_player_manager.get_player(player_id);
   if (player.has_failed())
      return;

   auto entity          = m_entity_system.entity(player->entity_id());
   auto player_position = math::Vector3::from_proto(event.position());
   entity.component<entity::component::Location>().set_position(m_world, entity, player_position);
}

void EventHandler::handle_set_player_rotation(const serverbound_v1::SetPlayerRotation &event,
                                              game::PlayerId player_id)
{
   auto player = m_player_manager.get_player(player_id);
   if (player.has_failed())
      return;

   auto entity              = m_entity_system.entity(player->entity_id());
   auto &rotation_component = entity.component<entity::component::Rotation>();

   rotation_component.set_yaw(event.rotation().yaw());
   rotation_component.set_pitch(event.rotation().pitch());
   m_dispatcher.player_look(player_id, entity.id(),
                            entity.component<entity::component::Location>().position(),
                            rotation_component.rotation());
}

void EventHandler::handle_chat_message(const serverbound_v1::ChatMessage &event, game::PlayerId player_id)
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

void EventHandler::handle_remove_player(const serverbound_v1::RemovePlayer &event, game::PlayerId player_id)
{
   auto &player = MB_ESCAPE(m_player_manager.get_player(player_id));
   spdlog::info("removing player {}", player.name());

   m_dispatcher.send_chat(chat::MessageType::SystemMessage, chat::format_left_message(player.name()));
   m_dispatcher.remove_player(player_id, player.entity_id());

   m_entity_system.destroy_entity(player.entity_id());
   m_player_manager.remove_player(player_id);
}

void EventHandler::handle_player_digging(const serverbound_v1::PlayerDigging &event, game::PlayerId player_id)
{
   m_dispatcher.acknowledge_block_change(player_id, event.sequence_id());

   auto status = static_cast<game::PlayerDiggingState>(event.state());
   switch (status) {
   case game::PlayerDiggingState::Digging:
   case game::PlayerDiggingState::CanceledDigging:
   case game::PlayerDiggingState::FinishedDigging: {
      auto block_position = game::BlockPosition::from_proto(event.block_position());
      auto block_state_id = m_world.get_block(block_position);

      m_world.set_block(block_position, 0);

      if (block_state_id.ok() && *block_state_id != 0) {
         world::BlockState block_state{*block_state_id};
         auto item_id = repository::Item::the().find_id_by_tag(block_state.block_tag());
         if (item_id.ok()) {
            auto position = block_position.to_vec3() + math::Vector3{0.5, 0.75, 0.5};
            auto msg      = fmt::format("spawning item {} at {}", *item_id, position);
            m_dispatcher.send_direct_chat(player_id, chat::MessageType::PlayerMessage,
                                          format::Builder().text(msg).to_string());
            m_world.spawn<entity::factory::Item>(position, game::ItemSlot{*item_id, 1});
         }
      }
   } break;
   default: break;
   }
}

void EventHandler::handle_update_ping(const serverbound_v1::UpdatePing &event, game::PlayerId player_id)
{
   auto &player = MB_ESCAPE(m_player_manager.get_player(player_id));
   player.set_ping(event.ping());
}

void EventHandler::handle_animate_hand(const serverbound_v1::AnimateHand &event, game::PlayerId player_id)
{
   auto &player = MB_ESCAPE(m_player_manager.get_player(player_id));
   auto entity  = m_entity_system.entity(player.entity_id());
   if (entity.has_component<entity::component::Location>())
      return;

   m_dispatcher.animate_player_entity(
           player_id, player.entity_id(), entity.component<entity::component::Location>().position(),
           event.hand() == 0 ? game::EntityAnimation::SwingMainArm : game::EntityAnimation::SwingOffHand);
}

void EventHandler::handle_load_initial_chunks(const serverbound_v1::LoadInitialChunks &event,
                                              game::PlayerId player_id)
{
   spdlog::info("loading initial chunks!");
   auto player = m_player_manager.get_player(player_id);
   if (player.has_failed()) {
      spdlog::error("could not obtain player info: {}", player.err()->msg());
      return;
   }

   auto entity = m_entity_system.entity(player->entity_id());

   auto result = entity.component<entity::component::StreamingComponent>().send_all_visible_chunks(m_world,
                                                                                                   player_id);
   if (result.has_failed()) {
      spdlog::error("error loading chunks: {}", result.err()->msg());
      return;
   }

   entity.component<entity::component::Inventory>().synchronize_inventory(m_dispatcher);

   m_dispatcher.player_list(player_id, m_player_manager.player_status_list());
   m_dispatcher.entity_list(player_id, entity.component<entity::component::Location>().position(), 16.0);

   m_dispatcher.synchronise_player_position_and_rotation(
           player_id, entity.component<entity::component::Location>().position(),
           entity.component<entity::component::Rotation>().yaw(),
           entity.component<entity::component::Rotation>().pitch());

   m_dispatcher.set_spawn_position(player_id, game::BlockPosition(),
                                   entity.component<entity::component::Rotation>().pitch());
}

void EventHandler::handle_block_placement(const serverbound_v1::BlockPlacement &event,
                                          game::PlayerId player_id)
{
   auto face           = game::Face::from_proto(event.face());
   auto block_position = game::BlockPosition::from_proto(event.position());

   auto state_id = m_world.get_block(block_position);
   if (state_id.has_failed())
      return;

   if (m_block_manager.on_player_action(
               m_world, player_id, *state_id, block_position, face,
               {event.crosshair().x(), event.crosshair().y(), event.crosshair().z()})) {
      m_dispatcher.acknowledge_block_change(player_id, event.sequence_id());
      return;
   }

   auto player = m_world.players().get_player(player_id);
   if (player.has_failed()) {
      return;
   }

   auto entity     = m_entity_system.entity(player->entity_id());
   auto &inventory = entity.component<entity::component::Inventory>();

   auto item_slot = inventory.active_item();
   if (item_slot.count == 0)
      return;

   auto item = repository::Item::the().get_by_id(item_slot.item_id);
   if (item.has_failed())
      return;

   if (not item->is_block())
      return;

   auto block_id = repository::Block::the().find_id_by_tag(item->corresponding_block_tag());
   if (block_id.has_failed())
      return;

   if (not inventory.take_from_active_slot(m_dispatcher, 1))
      return;

   if (m_block_manager.on_player_place_block(m_world, player_id, static_cast<int>(*block_id), block_position,
                                             face)) {
      m_dispatcher.acknowledge_block_change(player_id, event.sequence_id());
   }
}

void EventHandler::handle_change_inventory_item(const serverbound_v1::ChangeInventoryItem &event,
                                                game::PlayerId player_id)
{
   auto &player = MB_ESCAPE(m_player_manager.get_player(player_id));
   auto entity  = m_entity_system.entity(player.entity_id());

   spdlog::info("setting slot {} to {} {}", event.slot_id(), event.item_id().id(), event.item_count());

   entity.component<entity::component::Inventory>().set_slot(
           m_dispatcher, static_cast<game::SlotId>(event.slot_id()),
           game::ItemSlot{
                   .item_id = static_cast<game::ItemId>(event.item_id().id()),
                   .count   = event.item_count(),
           });
}

void EventHandler::handle_change_held_item(const serverbound_v1::ChangeHeldItem &event,
                                           game::PlayerId player_id)
{
   auto &player    = MB_ESCAPE(m_player_manager.get_player(player_id));
   auto entity     = m_entity_system.entity(player.entity_id());
   auto &inventory = entity.component<entity::component::Inventory>();

   inventory.set_active_item(m_dispatcher, event.slot());
}

void EventHandler::handle_issue_command(const serverbound_v1::IssueCommand &event, game::PlayerId player_id)
{
   auto &player = MB_ESCAPE(m_player_manager.get_player(player_id));
   auto entity  = m_entity_system.entity(player.entity_id());

   m_command_context.set_variable("player_id", std::make_shared<command::UUIDObject>(player_id));
   m_command_context.set_variable("player_name", std::make_shared<command::StringObject>(player.name()));
   m_command_context.set_variable("entity_id", std::make_shared<command::IntObject>(player.entity_id()));

   auto player_pos =
           game::BlockPosition::from_vec3(entity.component<entity::component::Location>().position());
   m_command_context.set_variable("here", std::make_shared<command::BlockPositionObject>(player_pos));

   auto res = m_command_manager.evaluate(m_command_context, event.command());
   if (res.has_value()) {
      format::Builder builder;
      builder.bold(format::Color::Red, "COMMAND FAILED ").text(res->message);
      m_dispatcher.send_direct_chat(player_id, chat::MessageType::PlayerMessage, builder.to_string());
   }
}

void EventHandler::handle_interact(const serverbound_v1::Interact &event, game::PlayerId player_id)
{
   spdlog::info("player {} is attacking entity {}", boost::uuids::to_string(player_id), event.entity_id());

   auto &player = MB_ESCAPE(m_player_manager.get_player(player_id));
   auto entity  = m_entity_system.entity(event.entity_id());
   if (not entity.has_component<entity::component::Health>())
      return;
   if (not entity.has_component<entity::component::Location>())
      return;
   if (not entity.has_component<entity::component::Velocity>())
      return;

   entity.component<entity::component::Health>().health -= 1.0f;

   auto attacking_entity = m_entity_system.entity(player.entity_id());
   if (not attacking_entity.has_component<entity::component::Location>())
      return;

   auto diff = (entity.component<entity::component::Location>().position() - attacking_entity.component<entity::component::Location>().position()).normalize();
   diff.set_y(0.2);
   entity.component<entity::component::Velocity>().set_velocity(m_dispatcher, entity.component<entity::component::Location>().position(), diff);

   auto target_player_id = m_player_manager.get_player_id_by_entity_id(event.entity_id());
   if (target_player_id.has_value()) {

      spdlog::info("setting players health to {}", entity.component<entity::component::Health>().health);
      m_dispatcher.set_health_and_food(*target_player_id,
                                       entity.component<entity::component::Health>().health, 20, 5.0f);
   }

   m_dispatcher.animate_entity(event.entity_id(), entity.component<entity::component::Location>().position(),
                               game::EntityAnimation::TakeDamage);
}

}// namespace minecpp::service::engine
