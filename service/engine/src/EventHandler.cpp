#include "EventHandler.h"
#include "Dispatcher.h"
#include "Players.h"

#include <minecpp/chat/Chat.h>
#include <minecpp/command/Command.h>
#include <minecpp/command/core/Cord.h>
#include <minecpp/command/core/DecimateBlocks.h>
#include <minecpp/command/core/Echo.h>
#include <minecpp/command/core/Fly.h>
#include <minecpp/command/core/Format.h>
#include <minecpp/command/core/Give.h>
#include <minecpp/command/core/KillAll.h>
#include <minecpp/command/core/ListEntities.h>
#include <minecpp/command/core/ReloadChunk.h>
#include <minecpp/command/core/Spawn.h>
#include <minecpp/command/core/Sync.h>
#include <minecpp/command/core/Teleport.h>
#include <minecpp/controller/block/Door.h>
#include <minecpp/controller/block/Fence.h>
#include <minecpp/controller/block/Foliage.h>
#include <minecpp/controller/block/Grass.h>
#include <minecpp/controller/block/Slab.h>
#include <minecpp/controller/block/Stairs.h>
#include <minecpp/controller/block/Torch.h>
#include <minecpp/controller/block/TrapDoor.h>
#include <minecpp/controller/block/Wood.h>
#include <minecpp/controller/item/Bow.h>
#include <minecpp/controller/item/Food.h>
#include <minecpp/controller/item/Sword.h>
#include <minecpp/entity/Aliases.hpp>
#include <minecpp/entity/component/Abilities.h>
#include <minecpp/entity/component/Inventory.h>
#include <minecpp/entity/component/Location.h>
#include <minecpp/entity/component/Player.h>
#include <minecpp/entity/component/Streamer.h>
#include <minecpp/entity/component/Team.h>
#include <minecpp/entity/component/Trader.h>
#include <minecpp/entity/EntitySystem.h>
#include <minecpp/format/Format.h>
#include <minecpp/game/IWorld.hpp>
#include <minecpp/repository/Block.h>
#include <minecpp/repository/Item.h>
#include <minecpp/repository/State.h>

#include <spdlog/spdlog.h>

namespace minecpp::service::engine {

EventHandler::EventHandler(Dispatcher &dispatcher, PlayerManager &player_manager,
                           entity::EntitySystem &entity_system, game::IWorld &world,
                           controller::BlockManager &block_manager,
                           controller::RootItem &root_item_controller) :
    m_dispatcher(dispatcher),
    m_player_manager(player_manager),
    m_entity_system(entity_system),
    m_world(world),
    m_command_std_stream(m_dispatcher),
    m_command_context(m_command_manager, command::g_null_stream, m_command_std_stream, &m_world),
    m_block_manager(block_manager),
    m_root_item_controller(root_item_controller)
{
   m_command_manager.register_command<command::core::Echo>();
   m_command_manager.register_command<command::core::Give>();
   m_command_manager.register_command<command::core::ReloadChunk>();
   m_command_manager.register_command<command::core::Sync>();
   m_command_manager.register_command<command::core::ListEntities>();
   m_command_manager.register_command<command::core::Cord>();
   m_command_manager.register_command<command::core::Spawn>();
   m_command_manager.register_command<command::core::Fly>();
   m_command_manager.register_command<command::core::KillAll>();
   m_command_manager.register_command<command::core::Teleport>();
   m_command_manager.register_command<command::core::DecimateBlocks>();

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

   for (auto wood_type_value : game::WoodType::Values) {
      game::WoodType wood_type{wood_type_value};

      if (auto wood_id = repository::Block::the().find_id_by_tag(
                  fmt::format("minecraft:{}_wood", wood_type.to_string()));
          wood_id.ok()) {
         m_block_manager.register_controller<controller::block::Wood>(*wood_id);
      } else {
         spdlog::error("no such block id minecraft:{}_wood", wood_type.to_string());
      }

      if (auto log_id = repository::Block::the().find_id_by_tag(
                  fmt::format("minecraft:{}_log", wood_type.to_string()));
          log_id.ok()) {
         m_block_manager.register_controller<controller::block::Wood>(*log_id);
      } else {
         spdlog::error("no such block id minecraft:{}_log", wood_type.to_string());
      }

      if (auto log_id = repository::Block::the().find_id_by_tag(
                  fmt::format("minecraft:stripped_{}_log", wood_type.to_string()));
          log_id.ok()) {
         m_block_manager.register_controller<controller::block::Wood>(*log_id);
      } else {
         spdlog::error("no such block id minecraft:stripped_{}_log", wood_type.to_string());
      }

      if (auto door_id = repository::Block::the().find_id_by_tag(
                  fmt::format("minecraft:{}_door", wood_type.to_string()));
          door_id.ok()) {
         m_block_manager.register_controller<controller::block::Door>(*door_id);
      } else {
         spdlog::error("no such block id minecraft:{}_door", wood_type.to_string());
      }

      if (auto fence_id = repository::Block::the().find_id_by_tag(
                  fmt::format("minecraft:{}_fence", wood_type.to_string()));
          fence_id.ok()) {
         m_block_manager.register_controller<controller::block::Fence>(*fence_id);
      } else {
         spdlog::error("no such block id minecraft:{}_fence", wood_type.to_string());
      }

      if (auto stairs_id = repository::Block::the().find_id_by_tag(
                  fmt::format("minecraft:{}_stairs", wood_type.to_string()));
          stairs_id.ok()) {
         m_block_manager.register_controller<controller::block::Stairs>(*stairs_id);
      } else {
         spdlog::error("no such block id minecraft:{}_stairs", wood_type.to_string());
      }

      if (auto slab_id = repository::Block::the().find_id_by_tag(
                  fmt::format("minecraft:{}_slab", wood_type.to_string()));
          slab_id.ok()) {
         m_block_manager.register_controller<controller::block::Slab>(*slab_id);
      }

      if (auto trapdoor_id = repository::Block::the().find_id_by_tag(
                  fmt::format("minecraft:{}_trapdoor", wood_type.to_string()));
          trapdoor_id.ok()) {
         m_block_manager.register_controller<controller::block::TrapDoor>(*trapdoor_id);
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
   if (auto stairs_id = repository::Block::the().find_id_by_tag("minecraft:mossy_stone_brick_stairs");
       stairs_id.ok()) {
      m_block_manager.register_controller<controller::block::Stairs>(*stairs_id);
   }

   if (auto torch_id = repository::Block::the().find_id_by_tag("minecraft:torch"); torch_id.ok()) {
      m_block_manager.register_controller<controller::block::Torch>(*torch_id);
   }
   if (auto torch_id = repository::Block::the().find_id_by_tag("minecraft:wall_torch"); torch_id.ok()) {
      m_block_manager.register_controller<controller::block::Torch>(*torch_id);
   }
   if (auto block_id = repository::Block::the().find_id_by_tag("minecraft:tall_grass"); block_id.ok()) {
      m_block_manager.register_controller<controller::block::Foliage>(*block_id);
   }
   if (auto block_id = repository::Block::the().find_id_by_tag("minecraft:poppy"); block_id.ok()) {
      m_block_manager.register_controller<controller::block::Foliage>(*block_id);
   }
   if (auto block_id = repository::Block::the().find_id_by_tag("minecraft:dandelion"); block_id.ok()) {
      m_block_manager.register_controller<controller::block::Foliage>(*block_id);
   }
   if (auto block_id = repository::Block::the().find_id_by_tag("minecraft:blue_orchid"); block_id.ok()) {
      m_block_manager.register_controller<controller::block::Foliage>(*block_id);
   }
   if (auto block_id = repository::Block::the().find_id_by_tag("minecraft:snow"); block_id.ok()) {
      m_block_manager.register_controller<controller::block::Foliage>(*block_id);
   }
   if (auto block_id = repository::Block::the().find_id_by_tag("minecraft:stone_slab"); block_id.ok()) {
      m_block_manager.register_controller<controller::block::Slab>(*block_id);
   }
   if (auto block_id = repository::Block::the().find_id_by_tag("minecraft:cobblestone_slab"); block_id.ok()) {
      m_block_manager.register_controller<controller::block::Slab>(*block_id);
   }
   if (auto block_id = repository::Block::the().find_id_by_tag("minecraft:stone_brick_slab"); block_id.ok()) {
      m_block_manager.register_controller<controller::block::Slab>(*block_id);
   }
   if (auto block_id = repository::Block::the().find_id_by_tag("minecraft:mossy_stone_brick_slab");
       block_id.ok()) {
      m_block_manager.register_controller<controller::block::Slab>(*block_id);
   }
   if (auto block_id = repository::Block::the().find_id_by_tag("minecraft:grass_block"); block_id.ok()) {
      m_block_manager.register_controller<controller::block::Grass>(*block_id);
   }

   if (auto item_id = repository::Item::the().find_id_by_tag("minecraft:bow"); item_id.ok()) {
      m_root_item_controller.register_controller<controller::item::Bow>(*item_id);
   }
   if (auto item_id = repository::Item::the().find_id_by_tag("minecraft:apple"); item_id.ok()) {
      m_root_item_controller.register_controller<controller::item::Food>(*item_id);
   }
   if (auto item_id = repository::Item::the().find_id_by_tag("minecraft:iron_sword"); item_id.ok()) {
      m_root_item_controller.register_controller<controller::item::Sword>(*item_id);
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

   auto entity = this->player_entity(player_id);
   if (entity.has_failed()) {
      spdlog::warn("player entity is invalid: {}", entity.err()->msg());
      return;
   }

   auto &inventory = entity->component<entity::component::Inventory>();
   if (inventory.add_item_by_tag(m_dispatcher, "minecraft:bow", 1).has_failed()) {
      spdlog::warn("could not add item: {}", entity.err()->msg());
   }
   if (inventory.add_item_by_tag(m_dispatcher, "minecraft:iron_sword", 1).has_failed()) {
      spdlog::warn("could not add item: {}", entity.err()->msg());
   }
   if (inventory.add_item_by_tag(m_dispatcher, "minecraft:apple", 8).has_failed()) {
      spdlog::warn("could not add item: {}", entity.err()->msg());
   }
   if (inventory.add_item_by_tag(m_dispatcher, "minecraft:arrow", 64).has_failed()) {
      spdlog::warn("could not add item: {}", entity.err()->msg());
   }
   if (inventory.add_item_by_tag(m_dispatcher, "minecraft:dirt", 64).has_failed()) {
      spdlog::warn("could not add item: {}", entity.err()->msg());
   }

   if (not entity->has_component<entity::component::Abilities>()) {
      m_dispatcher.deny_player(player_id, "Player's entity doesn't have abilities component");
   }

   auto player = m_player_manager.get_player(player_id);
   if (player.has_failed()) {
      spdlog::warn("player is invalid: {}", player.err()->msg());
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
}

void EventHandler::handle_set_player_position(const serverbound_v1::SetPlayerPosition &event,
                                              game::PlayerId player_id)
{
   auto player = m_player_manager.get_player(player_id);
   if (player.has_failed()) {
      spdlog::warn("couldn't get player: {}", player.err()->msg());
      return;
   }

   // to set position player needs to load initial chunks first
   if (not player->has_loaded_initial_chunks())
      return;

   auto entity = this->player_entity(player_id);
   if (entity.has_failed()) {
      spdlog::warn("player entity is invalid: {}", entity.err()->msg());
      return;
   }

   if (not entity->has_component<LocationComponent>())
      return;

   auto player_position = math::Vector3::from_proto(event.position());
   auto &location       = entity->component<LocationComponent>();
   location.set_position(m_world, *entity, player_position, event.is_on_ground());
}

void EventHandler::handle_set_player_rotation(const serverbound_v1::SetPlayerRotation &event,
                                              game::PlayerId player_id)
{
   auto player = m_player_manager.get_player(player_id);
   if (player.has_failed()) {
      spdlog::warn("couldn't get player: {}", player.err()->msg());
      return;
   }

   // to set position player needs to load initial chunks first
   if (not player->has_loaded_initial_chunks())
      return;

   auto entity = this->player_entity(player_id);
   if (entity.has_failed()) {
      spdlog::warn("player entity is invalid: {}", entity.err()->msg());
      return;
   }

   auto &location = entity->component<LocationComponent>();
   location.set_is_on_ground(m_world, *entity, event.is_on_ground());

   auto &rotation_component = entity->component<RotationComponent>();
   rotation_component.set_rotation(m_dispatcher, location.position(),
                                   math::Rotation::from_proto(event.rotation()));
}

void EventHandler::handle_set_player_position_rotation(const serverbound_v1::SetPlayerPositionRotation &event,
                                                       game::PlayerId player_id)
{
   auto player = m_player_manager.get_player(player_id);
   if (player.has_failed()) {
      spdlog::warn("couldn't get player: {}", player.err()->msg());
      return;
   }

   // to set position player needs to load initial chunks first
   if (not player->has_loaded_initial_chunks())
      return;

   auto entity = this->player_entity(player_id);
   if (entity.has_failed()) {
      spdlog::warn("player entity is invalid: {}", entity.err()->msg());
      return;
   }

   if (not entity->has_component<LocationComponent>())
      return;

   auto player_position = math::Vector3::from_proto(event.position());
   auto &location       = entity->component<LocationComponent>();
   location.set_position(m_world, *entity, player_position, event.is_on_ground());

   auto &rotation_component = entity->component<RotationComponent>();
   rotation_component.set_rotation(m_dispatcher, location.position(),
                                   math::Rotation::from_proto(event.rotation()));
}

void EventHandler::handle_set_player_on_ground(const serverbound_v1::SetPlayerOnGround &event,
                                               game::PlayerId player_id)
{
   auto entity = this->player_entity(player_id);
   if (entity.has_failed()) {
      spdlog::warn("player entity is invalid: {}", entity.err()->msg());
      return;
   }

   if (not entity->has_component<LocationComponent>())
      return;

   entity->component<LocationComponent>().set_is_on_ground(m_world, *entity, event.is_on_ground());
}

void EventHandler::handle_chat_message(const serverbound_v1::ChatMessage &event, game::PlayerId player_id)
{
   try {
      if (event.message().empty())
         return;

      auto player = m_player_manager.get_player(player_id);
      if (player.has_failed()) {
         spdlog::warn("no player with id: {}", util::uuid_to_string(player_id));
         return;
      }

      spdlog::info("CHAT [{}] {}", player->name(), event.message());
      m_dispatcher.send_chat(chat::MessageType::PlayerMessage,
                             chat::format_chat_message(player->name(), event.message()));
   } catch (std::runtime_error &err) {
      spdlog::error("handle chat message: {}", err.what());
   }
}

void EventHandler::handle_remove_player(const serverbound_v1::RemovePlayer & /*event*/,
                                        game::PlayerId player_id)
{
   auto player = m_player_manager.get_player(player_id);
   if (player.has_failed()) {
      spdlog::warn("no such player {}", util::uuid_to_string(player_id));
      return;
   }

   spdlog::info("removing player {}", player->name());

   auto entity_id = player->entity_id();

   m_dispatcher.send_chat(chat::MessageType::SystemMessage, chat::format_left_message(player->name()));
   m_dispatcher.remove_player(player_id, entity_id);

   m_entity_system.destroy_entity(entity_id);
   m_player_manager.remove_player(player_id);
}

void EventHandler::handle_player_digging(const serverbound_v1::PlayerDigging &event, game::PlayerId player_id)
{
   m_dispatcher.acknowledge_block_change(player_id, event.sequence_id());

   auto entity = this->player_entity(player_id);
   if (entity.has_failed()) {
      spdlog::warn("player entity is invalid: {}", entity.err()->msg());
      return;
   }

   auto status = static_cast<game::PlayerDiggingState>(event.state());

   if (this->should_destroy_block(*entity, status)) {
      m_world.destroy_block(game::BlockPosition::from_proto(event.block_position()));
      return;
   }

   switch (status) {
   case game::PlayerDiggingState::DropAllItems:
   case game::PlayerDiggingState::DropItem: {
      if (not entity->has_component<InventoryComponent>())
         return;

      entity->component<InventoryComponent>().drop_active_item(
              m_world, status == game::PlayerDiggingState::DropAllItems);
   } break;
   case game::PlayerDiggingState::ReleaseUseItem: {
      if (not entity->has_component<InventoryComponent>()) {
         spdlog::error("player entity doesn't have inventory (entity_id:{})", entity->id());
         return;
      }

      auto slot_item = entity->component<InventoryComponent>().active_item();
      m_root_item_controller.on_released_item(m_world, slot_item.item_id, entity->id());
   } break;
   default: break;
   }
}

void EventHandler::handle_update_ping(const serverbound_v1::UpdatePing &event, game::PlayerId player_id)
{
   auto player = m_player_manager.get_player(player_id);
   if (player.has_failed()) {
      spdlog::error("no player with id {}", util::uuid_to_string(player_id));
      return;
   }
   player->set_ping(event.ping());
}

void EventHandler::handle_animate_hand(const serverbound_v1::AnimateHand &event, game::PlayerId player_id)
{
   auto entity = this->player_entity(player_id);
   if (entity.has_failed()) {
      spdlog::warn("player entity is invalid: {}", entity.err()->msg());
      return;
   }
   if (entity->has_component<entity::component::Location>())
      return;

   m_dispatcher.animate_player_entity(
           player_id, entity->id(), entity->component<entity::component::Location>().position(),
           event.hand() == 0 ? game::EntityAnimation::SwingMainArm : game::EntityAnimation::SwingOffHand);
}

void EventHandler::handle_pre_initial_chunks(const serverbound_v1::PreInitialChunks & /*event*/,
                                             game::PlayerId player_id)
{
   spdlog::info("pre initial chunks!");
   auto entity = this->player_entity(player_id);
   if (entity.has_failed()) {
      spdlog::warn("player entity is invalid: {}", entity.err()->msg());
      return;
   }
   assert(entity->has_component<LocationComponent>());
   assert(entity->has_component<StreamerComponent>());
   assert(entity->has_component<InventoryComponent>());

   auto result = entity->component<StreamerComponent>().send_all_visible_chunks(
           m_world, player_id, entity->component<LocationComponent>().position());
   if (result.has_failed()) {
      spdlog::error("error loading chunks: {}", result.err()->msg());
      return;
   }
}

void EventHandler::handle_post_initial_chunks(const serverbound_v1::PostInitialChunks &event,
                                              game::PlayerId player_id)
{
   spdlog::info("post initial chunks!");
   auto player = m_player_manager.get_player(player_id);
   if (player.has_failed()) {
      spdlog::warn("couldn't get player: {}", player.err()->msg());
      return;
   }

   player->set_has_loaded_initial_chunks(true);

   auto entity = this->player_entity(player_id);
   if (entity.has_failed()) {
      spdlog::warn("player entity is invalid: {}", entity.err()->msg());
      return;
   }
   assert(entity->has_component<PlayerComponent>());
   assert(entity->has_component<LocationComponent>());
   assert(entity->has_component<RotationComponent>());

   entity->component<PlayerComponent>().init_visible_entities(
           m_dispatcher, m_entity_system, entity->component<LocationComponent>().position());

   entity->component<InventoryComponent>().synchronize_inventory(m_dispatcher);

   m_dispatcher.player_list(player_id, m_player_manager.player_status_list());

   m_dispatcher.synchronise_player_position_and_rotation(player_id,
                                                         entity->component<LocationComponent>().position(),
                                                         entity->component<RotationComponent>().rotation());

   m_dispatcher.set_spawn_position(player_id, game::BlockPosition(),
                                   entity->component<entity::component::Rotation>().pitch_degrees());
}

void EventHandler::handle_block_placement(const serverbound_v1::BlockPlacement &event,
                                          game::PlayerId player_id)
{
   auto face           = game::Face::from_proto(event.face());
   auto block_position = game::BlockPosition::from_proto(event.position());

   auto state_id = m_world.block_at(block_position);
   if (state_id.has_failed())
      return;

   math::Vector3f crosshair_position{event.crosshair().x(), event.crosshair().y(), event.crosshair().z()};

   if (m_block_manager.on_player_action(m_world, player_id, *state_id, block_position, face,
                                        crosshair_position)) {
      m_dispatcher.acknowledge_block_change(player_id, event.sequence_id());
      return;
   }

   auto entity = this->player_entity(player_id);
   if (entity.has_failed()) {
      spdlog::warn("player entity is invalid: {}", entity.err()->msg());
      return;
   }

   auto &inventory = entity->component<entity::component::Inventory>();
   auto item_slot  = inventory.active_item();
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
                                             face, crosshair_position)) {
      m_dispatcher.acknowledge_block_change(player_id, event.sequence_id());
   }
}

void EventHandler::handle_change_inventory_item(const serverbound_v1::ChangeInventoryItem &event,
                                                game::PlayerId player_id)
{
   auto entity = this->player_entity(player_id);
   if (entity.has_failed()) {
      spdlog::warn("player entity is invalid: {}", entity.err()->msg());
      return;
   }

   entity->component<entity::component::Inventory>().set_slot(
           m_dispatcher, static_cast<game::SlotId>(event.slot_id()),
           game::ItemSlot{
                   .item_id = static_cast<game::ItemId>(event.item_id().id()),
                   .count   = event.item_count(),
           });
}

void EventHandler::handle_change_held_item(const serverbound_v1::ChangeHeldItem &event,
                                           game::PlayerId player_id)
{
   auto entity = this->player_entity(player_id);
   if (entity.has_failed()) {
      spdlog::warn("player entity is invalid: {}", entity.err()->msg());
      return;
   }

   auto &inventory = entity->component<InventoryComponent>();
   inventory.set_active_item(m_dispatcher, event.slot());
}

void EventHandler::handle_issue_command(const serverbound_v1::IssueCommand &event, game::PlayerId player_id)
{
   auto player = m_player_manager.get_player(player_id);
   if (player.has_failed()) {
      spdlog::warn("player is invalid: {}", player.err()->msg());
      return;
   }

   auto entity = this->player_entity(player_id);
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

   auto player_entity = this->player_entity(player_id);
   if (player_entity.has_failed()) {
      spdlog::warn("player entity is invalid: {}", player_entity.err()->msg());
      return;
   }
   if (not player_entity->has_component<LocationComponent>())
      return;

   auto interacted_entity = m_entity_system.entity(event.entity_id());
   if (not interacted_entity.is_valid()) {
      spdlog::warn("attacked entity is invalid: {}", player_entity.err()->msg());
      return;
   }

   auto interaction = game::InteractionType::from_proto(event.interaction_type());

   if (interaction == game::InteractionType::Standard) {
      if (interacted_entity.has_component<TraderComponent>()) {
         auto &trader = interacted_entity.component<TraderComponent>();
         trader.on_interact(m_world, interacted_entity, *player_entity);
         return;
      }
   }

   if (not player_entity->has_component<InventoryComponent>())
      return;

   auto slot_item = player_entity->component<InventoryComponent>().active_item();
   m_root_item_controller.on_interact(m_world, slot_item.item_id, interaction, player_entity->id(),
                                      interacted_entity.id(), math::Vector3f::from_proto(event.position()),
                                      event.hand_type() == proto::common::v1::HandType::OffHand);
}

void EventHandler::handle_use_item(const serverbound_v1::UseItem & /*use_item*/, game::PlayerId player_id)
{
   auto entity = this->player_entity(player_id);
   if (entity.has_failed()) {
      spdlog::warn("player entity is invalid: {}", entity.err()->msg());
      return;
   }

   if (not entity->has_component<InventoryComponent>()) {
      spdlog::error("player entity doesn't have inventory (entity_id:{})", entity->id());
      return;
   }

   auto slot_item = entity->component<InventoryComponent>().active_item();
   m_root_item_controller.on_item_use(m_world, player_id, entity->id(), slot_item.item_id);
}

void EventHandler::handle_drop_inventory_item(const serverbound_v1::DropInventoryItem &drop_inventory_item,
                                              game::PlayerId player_id)
{
   auto entity = this->player_entity(player_id);
   if (not entity->has_component<InventoryComponent>())
      return;

   entity->component<InventoryComponent>().drop_carried_item(m_world, drop_inventory_item.full_stack());
}

void EventHandler::handle_set_carried_item(const serverbound_v1::SetCarriedItem &set_carried_item_msg,
                                           game::PlayerId player_id)
{
   auto entity = this->player_entity(player_id);
   if (entity.has_failed()) {
      spdlog::warn("player entity is invalid: {}", entity.err()->msg());
      return;
   }

   if (not entity->has_component<InventoryComponent>())
      return;

   entity->component<InventoryComponent>().set_carried_item(
           {static_cast<game::ItemId>(set_carried_item_msg.carried_item_id().id()),
            set_carried_item_msg.carried_item_count()});
}

void EventHandler::handle_request_respawn(const serverbound_v1::RequestRespawn & /*request_respawn*/,
                                          game::PlayerId player_id)
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

   m_dispatcher.spawn_player(player_id, entity->id(), entity->component<LocationComponent>().position());

   if (entity->has_component<TeamComponent>()) {
      entity->component<TeamComponent>().send_team_equipment(m_dispatcher, player_id);
   }
}

mb::result<game::Entity> EventHandler::player_entity(game::PlayerId player_id)
{
   auto player = m_player_manager.get_player(player_id);
   if (player.has_failed())
      return std::move(player.err());

   auto entity = m_entity_system.entity(player->entity_id());
   if (not entity.is_valid())
      return mb::error("invalid entity");

   return entity;
}

bool EventHandler::should_destroy_block(game::Entity &entity, game::PlayerDiggingState state) const
{
   assert(entity.has_component<AbilitiesComponent>());

   if (entity.component<AbilitiesComponent>().abilities().may_build) {
      switch (state) {
      case game::PlayerDiggingState::FinishedDigging:
      case game::PlayerDiggingState::Digging:
         return true;
      default:
         return false;
      }
   }
   return state == game::PlayerDiggingState::FinishedDigging;
}

}// namespace minecpp::service::engine
