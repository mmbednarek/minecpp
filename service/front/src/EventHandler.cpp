#include "EventHandler.h"

#include "minecpp/game/Abilities.h"
#include "minecpp/game/player/Player.h"
#include "minecpp/network/message/Clientbound.h"
#include "minecpp/proto/event/serverbound/Serverbound.pb.h"
#include "minecpp/repository/Repository.h"
#include "minecpp/service/engine/Api.h"
#include "minecpp/util/Uuid.h"

#include <boost/uuid/uuid_io.hpp>
#include <spdlog/spdlog.h>

namespace minecpp::service::front {

EventHandler::EventHandler(Server &server, nbt::repository::Registry &registry) :
    m_server(server),
    m_registry(registry)
{
}

void EventHandler::handle_add_player(const clientbound_v1::AddPlayer &msg,
                                     const event::RecipientList &recipient_list)
{
   auto add_player = minecpp::network::message::AddPlayer{
           .id   = game::player::read_id_from_proto(msg.player_id()),
           .name = msg.name(),
           .properties{},
           .game_mode = static_cast<mb::u8>(msg.game_mode()),
           .ping      = static_cast<mb::u32>(msg.ping()),
   };
   send_message(add_player, recipient_list);
}

void EventHandler::handle_spawn_player(const clientbound_v1::SpawnPlayer &spawn,
                                       const event::RecipientList &recipient_list)
{
   auto player_id = game::player::read_id_from_proto(spawn.player_id());

   auto spawn_player = minecpp::network::message::SpawnPlayer{
           .entity_id = spawn.entity().entity_id(),
           .id        = player_id,
           .x         = spawn.entity().position().x(),
           .y         = spawn.entity().position().y(),
           .z         = spawn.entity().position().z(),
           .yaw       = spawn.entity().rotation().yaw(),
           .pitch     = spawn.entity().rotation().pitch(),
   };

   send_message(spawn_player, recipient_list);

   for (const auto &equipment : spawn.entity().equipment()) {
      if (equipment.item().count() == 0)
         continue;

      send_message(
              network::message::SetEquipment{
                      .entity_id = spawn.entity().entity_id(),
                      .slot      = static_cast<uint8_t>(equipment.slot()),
                      .present   = true,
                      .item_id   = equipment.item().item_id().id(),
                      .count     = static_cast<int>(equipment.item().count()),
              },
              recipient_list);
   }
}

void EventHandler::handle_entity_move(const clientbound_v1::EntityMove &pos,
                                      const event::RecipientList &recipient_list)
{
   minecpp::network::message::EntityMove entity_move{
           .entity_id = pos.entity_id(),
           .x         = static_cast<short>(pos.movement().x()),
           .y         = static_cast<short>(pos.movement().y()),
           .z         = static_cast<short>(pos.movement().z()),
           .yaw       = pos.rotation().yaw(),
           .pitch     = pos.rotation().pitch(),
           .on_ground = pos.is_on_ground(),
   };

   send_message(entity_move, recipient_list);
}

void EventHandler::handle_entity_look(const clientbound_v1::EntityLook &pos,
                                      const event::RecipientList &recipient_list)
{
   minecpp::network::message::EntityLook entity_look{
           .entity_id = static_cast<int>(pos.entity_id()),
           .yaw       = pos.rotation().yaw(),
           .pitch     = pos.rotation().pitch(),
           .on_ground = true,
   };
   send_message(entity_look, recipient_list);

   minecpp::network::message::EntityHeadLook entity_head_look{
           .entity_id = static_cast<int>(pos.entity_id()),
           .yaw       = pos.rotation().yaw(),
   };
   send_message(entity_head_look, recipient_list);
}

void EventHandler::handle_chat(const clientbound_v1::Chat &chat_msg,
                               const event::RecipientList &recipient_list)
{
   minecpp::network::message::SystemChat chat{
           .message = chat_msg.message(),
           .type    = static_cast<chat::MessageType>(chat_msg.type()),
   };
   send_message(chat, recipient_list);
}

void EventHandler::handle_remove_player(const clientbound_v1::RemovePlayer &msg,
                                        const event::RecipientList &recipient_list)
{
   spdlog::info("removing player");
   network::message::RemovePlayer remove_player{
           .id = game::player::read_id_from_proto(msg.player_id()),
   };
   network::message::DestroyEntity destroy_entity{
           .entity_id = static_cast<uint32_t>(msg.entity_id()),
   };
   send_message(remove_player, recipient_list);
   send_message(destroy_entity, recipient_list);
}

void EventHandler::handle_update_block(const clientbound_v1::UpdateBlock &msg,
                                       const event::RecipientList &recipient_list)
{
   minecpp::network::message::BlockChange change{
           .block_position = static_cast<mb::u64>(msg.block_position()),
           .block_id       = msg.state(),
   };
   send_message(change, recipient_list);
}

void EventHandler::handle_animate_entity(const clientbound_v1::AnimateEntity &msg,
                                         const event::RecipientList &recipient_list)
{
   minecpp::network::message::AnimateEntity animate{
           .entity_id = static_cast<int>(msg.entity_id()),
           .type      = static_cast<uint8_t>(msg.animation()),
   };

   send_message(animate, recipient_list);
}

void EventHandler::handle_acknowledge_block_change(const clientbound_v1::AcknowledgeBlockChange &msg,
                                                   const event::RecipientList &recipient_list)
{
   minecpp::network::message::AcknowledgeBlockChanges acknowledge{
           .sequence_id = msg.sequence_id(),
   };
   send_message(acknowledge, recipient_list);
}

void EventHandler::handle_load_terrain(const clientbound_v1::LoadTerrain &msg,
                                       const event::RecipientList &recipient_list)
{
   for (auto &player_id : recipient_list.list) {
      if (!m_server.has_connection(player_id)) {
         spdlog::error("connection {} not found", boost::uuids::to_string(player_id));
         return;
      }

      auto conn = m_server.connection_by_player_id(player_id);
      if (!conn) {
         spdlog::error("connection {} is null", boost::uuids::to_string(player_id));
         return;
      }

      spdlog::info("loading {} chunks, central position {} {}", msg.coords().size(), msg.central_chunk().x(),
                   msg.central_chunk().z());

      send(conn, minecpp::network::message::UpdateChunkPosition{
                         .x = msg.central_chunk().x(),
                         .z = msg.central_chunk().z(),
                 });
   }
}

void EventHandler::handle_transfer_player(const clientbound_v1::TransferPlayer & /*msg*/,
                                          const event::RecipientList & /*recipient_list*/)
{
   // TODO: Implement this
}

void EventHandler::handle_unload_chunk(const clientbound_v1::UnloadChunk &msg,
                                       const event::RecipientList &recipient_list)
{
   minecpp::network::message::UnloadChunk unload_chunk{
           .chunk_x = msg.chunk_position().x(),
           .chunk_z = msg.chunk_position().z(),
   };
   send_message(unload_chunk, recipient_list);
}

void EventHandler::handle_accept_player(const clientbound_v1::AcceptPlayer &msg,
                                        const event::RecipientList &recipient_list)
{
   using namespace minecpp::network::message;

   for (auto player_id : recipient_list.list) {
      spdlog::info("got player accepted");

      if (!m_server.has_connection(player_id)) {
         spdlog::error("connection {} not found", game::player::format_player_id(player_id));
         return;
      }

      auto conn = m_server.connection_by_player_id(player_id);
      if (conn == nullptr) {
         spdlog::error("connection {} is null", game::player::format_player_id(player_id));
         return;
      }

      std::stringstream dimension_codec;
      m_registry.serialize(dimension_codec, "");

      send(conn, JoinGame{
                         .player_id = static_cast<mb::u32>(msg.player().entity_id()),
                         .game_mode = static_cast<mb::u8>(msg.gameplay().mode()),
                         .available_dimensions{"overworld", "the_nether", "the_end", "overworld_caves"},
                         .dimension_codec    = dimension_codec.str(),
                         .dimension_name     = "minecraft:overworld",
                         .world_name         = "overworld",
                         .seed               = msg.gameplay().seed(),
                         .max_players        = static_cast<mb::u8>(msg.gameplay().max_players()),
                         .view_distance      = static_cast<mb::u32>(msg.gameplay().view_distance()),
                         .reduced_debug_info = msg.gameplay().reduced_debug_info(),
                         .immediate_respawn  = msg.gameplay().do_immediate_respawn(),
      });

      send(conn, ServerBrand{"minecpp"});

      send(conn, Difficulty{
                         .difficulty = static_cast<mb::u8>(msg.gameplay().difficulty()),
                         .locked     = false,
                 });

      auto abilities = minecpp::game::Abilities::from_proto(msg.abilities());

      send(conn, PlayerAbilities{
                         .flags         = static_cast<mb::u8>(abilities.flags()),
                         .fly_speed     = abilities.fly_speed,
                         .field_of_view = abilities.walk_speed,
                 });

      // TODO: Send recipes and tags

      send(conn, EntityStatus{
                         .entity_id = static_cast<mb::u8>(msg.player().entity_id()),
                         .opcode    = 0x18,
                 });

      // TODO: Send command list

      send(conn,
           RecipeBook{
                   .state                       = Init,
                   .gui_open                    = msg.player().recipe_book().gui_open(),
                   .filtering_craftable         = msg.player().recipe_book().filtering_craftable(),
                   .furnace_gui_open            = msg.player().recipe_book().furnace_gui_open(),
                   .furnace_filtering_craftable = msg.player().recipe_book().furnace_filtering_craftable(),
           });

      if (m_client == nullptr) {
         spdlog::error("Player stream is null!");
         return;
      }

      spdlog::info("Issuing loading initial chunks");
      m_client->send(proto::event::serverbound::PreInitialChunks{}, player_id);
   }
}

void EventHandler::handle_deny_player(const clientbound_v1::DenyPlayer &msg,
                                      const event::RecipientList &recipient_list)
{
   for (auto player_id : recipient_list.list) {
      if (!m_server.has_connection(player_id)) {
         spdlog::error("connection {} not found", game::player::format_player_id(player_id));
         return;
      }

      auto conn = m_server.connection_by_player_id(player_id);
      if (!conn) {
         spdlog::error("connection {} is null", game::player::format_player_id(player_id));
         return;
      }

      spdlog::error("could not join player {}.", msg.denial_reason());
      send_and_disconnect(conn, minecpp::network::message::Disconnect{
                                        .reason = format::Builder()
                                                          .bold(format::Color::Red, "DISCONNECTED ")
                                                          .text(msg.denial_reason())
                                                          .to_string(),
                                });
   }
}

void EventHandler::handle_player_list(const clientbound_v1::PlayerList &msg,
                                      const event::RecipientList &recipient_list)
{
   for (auto player_id : recipient_list.list) {
      if (!m_server.has_connection(player_id)) {
         spdlog::error("connection {} not found", game::player::format_player_id(player_id));
         return;
      }

      auto conn = m_server.connection_by_player_id(player_id);
      if (!conn) {
         spdlog::error("connection {} is null", game::player::format_player_id(player_id));
         return;
      }

      for (auto const &player_status : msg.list()) {
         send(conn, network::message::AddPlayer{
                            .id   = game::player::read_id_from_proto(player_status.id()),
                            .name = player_status.name(),
                            .properties{},
                            .game_mode = static_cast<mb::u8>(player_status.game_mode()),
                            .ping      = static_cast<mb::u32>(player_status.ping()),
                    });
      }
   }
}

void EventHandler::handle_entity_list(const clientbound_v1::EntityList &msg,
                                      const event::RecipientList &recipient_list)
{
   for (auto const &entity : msg.entities()) {
      auto id = util::read_uuid(entity.uuid().lower(), entity.uuid().upper());
      spdlog::info("sending entity data {}", to_string(id));

      this->send_entity(recipient_list, entity);
   }

   for (auto const &entity : msg.player_entities()) {
      auto id = util::read_uuid(entity.uuid().lower(), entity.uuid().upper());
      spdlog::info("sending player data {}", to_string(id));

      for (auto player_id : recipient_list.list) {
         if (player_id == id)
            continue;

         auto conn = m_server.connection_by_player_id(player_id);
         if (not conn) {
            spdlog::error("connection {} is null", game::player::format_player_id(player_id));
            continue;
         }
         send(conn, network::message::SpawnPlayer{
                            .entity_id = entity.entity_id(),
                            .id        = id,
                            .x         = entity.position().x(),
                            .y         = entity.position().y(),
                            .z         = entity.position().z(),
                            .yaw       = entity.rotation().yaw(),
                            .pitch     = entity.rotation().pitch(),
                    });

         for (const auto &equipment : entity.equipment()) {
            if (equipment.item().count() == 0)
               continue;

            send(conn, network::message::SetEquipment{
                               .entity_id = entity.entity_id(),
                               .slot      = static_cast<uint8_t>(equipment.slot()),
                               .present   = true,
                               .item_id   = equipment.item().item_id().id(),
                               .count     = static_cast<int>(equipment.item().count()),
                       });
         }
      }
   }
}

void EventHandler::handle_set_inventory_slot(const clientbound_v1::SetInventorySlot &msg,
                                             const event::RecipientList &recipient_list)
{
   assert(recipient_list.list.size() == 1);

   const auto player_id = recipient_list.list.front();

   auto conn = m_server.connection_by_player_id(player_id);
   if (!conn) {
      spdlog::error("connection {} is null", game::player::format_player_id(player_id));
      return;
   }

   send(conn, network::message::SetSlot{
                      .window_id = 0,
                      .state_id  = 0,
                      .slot      = static_cast<short>(msg.slot().slot_id()),
                      .item_id   = static_cast<int>(msg.slot().item_id().id()),
                      .count     = static_cast<uint8_t>(msg.slot().count()),
              });
}

void EventHandler::handle_update_block_light(const clientbound_v1::UpdateBlockLight &msg,
                                             const event::RecipientList &recipient_list)
{
   for (auto &chunk : msg.block_light()) {
      network::message::UpdateBlockLight update_block_light{};
      update_block_light.chunk_position = game::ChunkPosition::from_proto(chunk.position());
      for (auto &section : chunk.sections()) {
         std::vector<char> data;
         data.resize(section.block_light().size());
         std::copy(section.block_light().begin(), section.block_light().end(), data.begin());
         update_block_light.block_light[section.y()] = std::move(data);
      }

      for (auto player_id : recipient_list.list) {
         auto conn = m_server.connection_by_player_id(player_id);
         if (not conn) {
            spdlog::error("connection {} is null", game::player::format_player_id(player_id));
            return;
         }

         send(conn, update_block_light);
      }
   }
}

void EventHandler::handle_chunk_data(const clientbound_v1::ChunkData &msg,
                                     const event::RecipientList &recipient_list)
{
   network::message::ChunkData chunk_data{
           .chunk = msg.chunk(),
   };
   for (auto player_id : recipient_list.list) {
      auto conn = m_server.connection_by_player_id(player_id);
      if (not conn) {
         spdlog::error("connection {} is null", game::player::format_player_id(player_id));
         return;
      }

      send(conn, chunk_data);

      if (msg.is_initial_chunk() && conn->initial_chunk_count >= 0) {
         ++conn->initial_chunk_count;

         if (conn->initial_chunk_count > 32) {
            assert(m_client);
            m_client->send(proto::event::serverbound::PostInitialChunks{}, player_id);
            conn->initial_chunk_count = -1;
         }
      }
   }
}

void EventHandler::handle_set_center_chunk(const clientbound_v1::SetCenterChunk &msg,
                                           const event::RecipientList &recipient_list)
{
   network::message::UpdateChunkPosition chunk_position{
           .x = msg.position().x(),
           .z = msg.position().z(),
   };

   for (auto player_id : recipient_list.list) {
      auto conn = m_server.connection_by_player_id(player_id);
      if (not conn) {
         spdlog::error("connection {} is null", game::player::format_player_id(player_id));
         return;
      }

      send(conn, chunk_position);
   }
}

void EventHandler::handle_player_position_rotation(const clientbound_v1::PlayerPositionRotation &msg,
                                                   const event::RecipientList &recipient_list)
{
   network::message::PlayerPositionLook player_pos_look{
           .x                = msg.position().x(),
           .y                = msg.position().y(),
           .z                = msg.position().z(),
           .yaw              = msg.rotation().yaw(),
           .pitch            = msg.rotation().pitch(),
           .flags            = 0,
           .tp_id            = 0,
           .dismount_vehicle = false,
   };

   for (auto player_id : recipient_list.list) {
      auto conn = m_server.connection_by_player_id(player_id);
      if (not conn) {
         spdlog::error("connection {} is null", game::player::format_player_id(player_id));
         return;
      }

      send(conn, player_pos_look);
   }
}

void EventHandler::handle_set_spawn_position(const clientbound_v1::SetSpawnPosition &msg,
                                             const event::RecipientList &recipient_list)
{
   network::message::SetDefaultSpawnPosition set_spawn{
           .position = msg.position(),
           .angle    = msg.angle(),
   };

   for (auto player_id : recipient_list.list) {
      auto conn = m_server.connection_by_player_id(player_id);
      if (not conn) {
         spdlog::error("connection {} is null", game::player::format_player_id(player_id));
         return;
      }

      send(conn, set_spawn);
   }
}

void EventHandler::handle_set_entity_equipment(const clientbound_v1::SetEntityEquipment &msg,
                                               const event::RecipientList &recipient_list)
{
   network::message::SetEquipment set_equipment{
           .entity_id = msg.entity_id(),
           .slot      = static_cast<std::uint8_t>(msg.equipment_slot()),
           .present   = msg.has_item() && msg.item().count() > 0,
           .item_id   = msg.item().item_id().id(),
           .count     = static_cast<int>(msg.item().count()),
   };

   send_message(set_equipment, recipient_list);
}

void EventHandler::handle_set_health(const clientbound_v1::SetHealth &msg,
                                     const event::RecipientList &recipient_list)
{
   network::message::SetHealth set_health{
           .health          = msg.health(),
           .food            = msg.food(),
           .food_saturation = msg.food_saturation(),
   };
   send_message(set_health, recipient_list);
}

void EventHandler::handle_spawn_entity(const clientbound_v1::SpawnEntity &msg,
                                       const event::RecipientList &recipient_list)
{
   send_entity(recipient_list, msg.entity());
}

void EventHandler::send_entity(const event::RecipientList &recipient_list,
                               const proto::entity::Entity &entity)
{
   network::message::SpawnEntity spawn_entity{
           .entity_id   = entity.entity_id(),
           .unique_id   = util::read_uuid(entity.uuid().lower(), entity.uuid().upper()),
           .entity_type = static_cast<int>(entity.entity_type()),
           .x           = entity.position().x(),
           .y           = entity.position().y(),
           .z           = entity.position().z(),
           .yaw         = entity.rotation().yaw(),
           .pitch       = entity.rotation().pitch(),
           .head_yaw    = entity.head_yaw(),
           .data        = static_cast<int>(entity.data()),
           .vel_x       = static_cast<uint16_t>(entity.velocity().x()),
           .vel_y       = static_cast<uint16_t>(entity.velocity().y()),
           .vel_z       = static_cast<uint16_t>(entity.velocity().z()),
   };
   send_message(spawn_entity, recipient_list);

   for (const auto &meta : entity.metadata()) {
      switch (meta.value_case()) {
      case proto::entity::Metadata::kSlot: {
         network::message::EntityMetadataSlot slot{
                 .entity_id = entity.entity_id(),
                 .index     = static_cast<uint8_t>(meta.index()),
                 .item_id   = meta.slot().item_id().id(),
                 .count     = static_cast<int>(meta.slot().count()),
         };
         send_message(slot, recipient_list);
         break;
      }
      case proto::entity::Metadata::kByte: {
         network::message::EntityMetadataByte byte_meta{
                 .entity_id = entity.entity_id(),
                 .index     = static_cast<uint8_t>(meta.index()),
                 .value     = static_cast<uint8_t>(meta.byte()),
         };
         send_message(byte_meta, recipient_list);
         break;
      }
      default: break;
      }
   }
}

void EventHandler::handle_collect_item(const clientbound_v1::CollectItem &msg,
                                       const event::RecipientList &recipient_list)
{
   network::message::PickupItem pickup_item{
           .collected_entity_id = msg.collected_entity_id(),
           .collector_entity_id = msg.collector_entity_id(),
           .count               = msg.count(),
   };
   send_message(pickup_item, recipient_list);
}

void EventHandler::handle_remove_entity(const clientbound_v1::RemoveEntity &msg,
                                        const event::RecipientList &recipient_list)
{
   network::message::DestroyEntity destroy_entity{
           .entity_id = static_cast<uint32_t>(msg.entity_id()),
   };
   send_message(destroy_entity, recipient_list);
}

void EventHandler::handle_set_entity_velocity(const clientbound_v1::SetEntityVelocity &msg,
                                              const event::RecipientList &recipient_list)
{
   network::message::SetEntityVelocity update_velocity{
           .entity_id = static_cast<uint32_t>(msg.entity_id()),
           .velocity  = math::Vector3i::from_proto(msg.velocity()).cast<short>(),
   };
   send_message(update_velocity, recipient_list);
}

void EventHandler::handle_display_death_screen(const clientbound_v1::DisplayDeathScreen &msg,
                                               const event::RecipientList &recipient_list)
{
   network::message::DisplayDeathScreen display_death_screen{
           .victim_entity_id = msg.victim_entity_id(),
           .killer_entity_id = msg.killer_entity_id(),
           .message          = msg.death_message(),
   };
   send_message(display_death_screen, recipient_list);
}

void EventHandler::handle_respawn(const clientbound_v1::Respawn &msg,
                                  const event::RecipientList &recipient_list)
{
   network::message::Respawn respawn{
           .dimension_codec = msg.dimension_type(),
           .dimension_name  = msg.dimension_name(),

           .seed           = static_cast<uint64_t>(msg.hashed_seed()),
           .game_mode      = static_cast<uint8_t>(msg.game_mode()),
           .prev_game_mode = static_cast<uint8_t>(msg.game_mode()),

           .is_debug             = msg.is_debug(),
           .is_flat              = msg.is_flat(),
           .should_copy_metadata = msg.copy_metadata(),

           .has_death_location = msg.has_death_location(),
           .death_dimension    = msg.death_dimension(),
           .death_position     = math::Vector3::from_proto(msg.death_position()),
   };
   send_message(respawn, recipient_list);
}

void EventHandler::handle_teleport_entity(const clientbound_v1::TeleportEntity &msg,
                                          const event::RecipientList &recipient_list)
{
   network::message::TeleportEntity teleport_entity{.entity_id    = msg.entity_id(),
                                                    .position     = math::Vector3::from_proto(msg.position()),
                                                    .yaw          = msg.rotation().yaw(),
                                                    .pitch        = msg.rotation().pitch(),
                                                    .is_on_ground = msg.is_on_ground()};
   send_message(teleport_entity, recipient_list);
}

void EventHandler::handle_set_abilities(const clientbound_v1::SetAbilities &msg,
                                        const event::RecipientList &recipient_list)
{
   using minecpp::network::message::PlayerAbilityFlag;

   std::uint8_t flags{};
   flags |= msg.abilities().invulnerable() ? PlayerAbilityFlag::Invulnerable : PlayerAbilityFlag::None;
   flags |= msg.abilities().flying() ? PlayerAbilityFlag::IsFlying : PlayerAbilityFlag::None;
   flags |= msg.abilities().may_fly() ? PlayerAbilityFlag::AllowFlying : PlayerAbilityFlag::None;
   flags |= msg.abilities().may_build() ? PlayerAbilityFlag::CreativeMode : PlayerAbilityFlag::None;

   minecpp::network::message::PlayerAbilities player_abilities{
           .flags         = flags,
           .fly_speed     = msg.abilities().fly_speed(),
           .field_of_view = msg.abilities().walk_speed(),
   };

   send_message(player_abilities, recipient_list);
}

void EventHandler::set_client(engine::Client *client)
{
   m_client = client;
}

void EventHandler::visit_event(const proto::event::clientbound::Event &event)
{
   event::visit_clientbound(event, *this);
}

}// namespace minecpp::service::front
