#include "EventHandler.h"

#include "minecpp/game/Abilities.h"
#include "minecpp/game/player/Player.h"
#include "minecpp/net/play/Clientbound.schema.h"
#include "minecpp/proto/event/serverbound/Serverbound.pb.h"
#include "minecpp/repository/Repository.h"
#include "minecpp/service/engine/Api.h"
#include "minecpp/util/Packed.h"
#include "minecpp/util/Uuid.h"
#include "minecpp/world/Section.h"

#include <boost/uuid/uuid_io.hpp>
#include <spdlog/spdlog.h>

namespace minecpp::service::front {

namespace {

constexpr std::uint8_t encode_angle(float angle)
{
   return static_cast<std::uint8_t>(angle / 360.0f * 256.0f);
}

std::optional<net::play::Slot> encode_slot(const proto::common::Slot &slot)
{
   if (slot.count() == 0)
      return std::nullopt;

   return net::play::Slot{.item_id    = static_cast<std::int32_t>(slot.item_id().id()),
                          .item_count = static_cast<std::int8_t>(slot.count()),
                          .data{}};
}

}// namespace

EventHandler::EventHandler(Server &server, nbt::repository::Registry &registry) :
    m_server(server),
    m_registry(registry)
{
}

void EventHandler::handle_add_player(const clientbound_v1::AddPlayer &msg,
                                     const event::RecipientList &recipient_list)
{
   auto add_player = net::play::cb::UpdatePlayerInfo{
           .action_bits = 0b11101,
           .actions{net::play::cb::PlayerInfoChange{
                   .player_id = game::player::read_id_from_proto(msg.player_id()),
                   .add_player =
                           net::play::cb::ActionAddPlayer{
                                   .name = msg.name(),
                                   .properties{},
                           },
                   .set_game_mode =
                           net::play::cb::ActionSetGameMode{
                                   .game_mode = static_cast<mb::u8>(msg.game_mode()),
                           },
                   .set_is_listed =
                           net::play::cb::ActionSetIsListed{
                                   .is_listed = 1,
                           },
                   .set_latency =
                           net::play::cb::ActionSetLatency{
                                   .ping = static_cast<std::int32_t>(msg.ping()),
                           },
           }},
   };
   send_message(add_player, recipient_list);
}

void EventHandler::handle_spawn_player(const clientbound_v1::SpawnPlayer &spawn,
                                       const event::RecipientList &recipient_list)
{
   auto player_id = game::player::read_id_from_proto(spawn.player_id());

   auto spawn_player = net::play::cb::SpawnPlayer{
           .entity_id = spawn.entity().entity_id(),
           .player_id = player_id,
           .position{
                     .x = spawn.entity().position().x(),
                     .y = spawn.entity().position().y(),
                     .z = spawn.entity().position().z(),
                     },
           .yaw   = encode_angle(spawn.entity().rotation().yaw()),
           .pitch = encode_angle(spawn.entity().rotation().pitch()),
   };

   send_message(spawn_player, recipient_list);

   for (const auto &equipment : spawn.entity().equipment()) {
      if (equipment.item().count() == 0)
         continue;

      send_message(
              net::play::cb::SetEquipment{
                      .entity_id = spawn.entity().entity_id(),
                      .slot_id   = static_cast<std::int8_t>(equipment.slot()),
                      .slot      = encode_slot(equipment.item()),
              },
              recipient_list);
   }
}

void EventHandler::handle_entity_move(const clientbound_v1::EntityMove &pos,
                                      const event::RecipientList &recipient_list)
{
   net::play::cb::EntityMove entity_move{
           .entity_id = pos.entity_id(),
           .difference{
                       .x = static_cast<short>(pos.movement().x()),
                       .y = static_cast<short>(pos.movement().y()),
                       .z = static_cast<short>(pos.movement().z()),
                       },
           .yaw          = encode_angle(pos.rotation().yaw()),
           .pitch        = encode_angle(pos.rotation().pitch()),
           .is_on_ground = pos.is_on_ground(),
   };

   send_message(entity_move, recipient_list);
}

void EventHandler::handle_entity_look(const clientbound_v1::EntityLook &pos,
                                      const event::RecipientList &recipient_list)
{
   net::play::cb::EntityLook entity_look{
           .entity_id    = pos.entity_id(),
           .yaw          = encode_angle(pos.rotation().yaw()),
           .pitch        = encode_angle(pos.rotation().pitch()),
           .is_on_ground = true,
   };
   send_message(entity_look, recipient_list);

   net::play::cb::EntityHeadLook entity_head_look{
           .entity_id = pos.entity_id(),
           .yaw       = encode_angle(pos.rotation().yaw()),
   };
   send_message(entity_head_look, recipient_list);
}

void EventHandler::handle_chat(const clientbound_v1::Chat &chat_msg,
                               const event::RecipientList &recipient_list)
{
   net::play::cb::SystemChat chat{
           .message = chat_msg.message(),
           .type    = static_cast<std::int8_t>(chat_msg.type()),
   };
   send_message(chat, recipient_list);
}

void EventHandler::handle_remove_player(const clientbound_v1::RemovePlayer &msg,
                                        const event::RecipientList &recipient_list)
{
   spdlog::info("event-handle: removing player");
   net::play::cb::RemovePlayerInfo remove_player{
           .player_ids{game::player::read_id_from_proto(msg.player_id())},
   };
   send_message_to_all_players(remove_player);

   net::play::cb::RemoveEntities destroy_entity{
           .entity_ids{msg.entity_id()},
   };
   send_message(destroy_entity, recipient_list);
}

void EventHandler::handle_update_block(const clientbound_v1::UpdateBlock &msg,
                                       const event::RecipientList &recipient_list)
{
   net::play::cb::BlockChange change{
           .block_position = static_cast<mb::u64>(msg.block_position()),
           .block_id       = static_cast<std::int32_t>(msg.state()),
   };
   send_message(change, recipient_list);
}

void EventHandler::handle_animate_entity(const clientbound_v1::AnimateEntity &msg,
                                         const event::RecipientList &recipient_list)
{
   net::play::cb::AnimateEntity animate{
           .entity_id = msg.entity_id(),
           .type      = static_cast<std::uint8_t>(msg.animation()),
   };

   send_message(animate, recipient_list);
}

void EventHandler::handle_acknowledge_block_change(const clientbound_v1::AcknowledgeBlockChange &msg,
                                                   const event::RecipientList &recipient_list)
{
   net::play::cb::AcknowledgeBlockChanges acknowledge{
           .sequence_id = static_cast<std::uint32_t>(msg.sequence_id()),
   };
   send_message(acknowledge, recipient_list);
}

void EventHandler::handle_load_terrain(const clientbound_v1::LoadTerrain &msg,
                                       const event::RecipientList &recipient_list)
{
   net::play::cb::UpdateChunkPosition update_chunk_position{
           .chunk_position{
                           .x = msg.central_chunk().x(),
                           .y = msg.central_chunk().z(),
                           }
   };

   this->send_message(update_chunk_position, recipient_list);
}

void EventHandler::handle_unload_chunk(const clientbound_v1::UnloadChunk &msg,
                                       const event::RecipientList &recipient_list)
{
   net::play::cb::UnloadChunk unload_chunk{
           .position{
                     .x = msg.chunk_position().x(),
                     .y = msg.chunk_position().z(),
                     }
   };
   send_message(unload_chunk, recipient_list);
}

void EventHandler::handle_accept_player(const clientbound_v1::AcceptPlayer &msg,
                                        const event::RecipientList &recipient_list)
{
   using namespace net::play::cb;

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

      conn->send_message(JoinGame{
              .entity_id = static_cast<mb::u32>(msg.player().entity_id()),
              .game_mode = static_cast<std::int8_t>(msg.gameplay().mode()),
              .available_dimensions{"overworld", "the_nether", "the_end", "overworld_caves"},
              .dimension_codec            = m_registry,
              .dimension_name             = "minecraft:overworld",
              .world_name                 = "overworld",
              .seed                       = msg.gameplay().seed(),
              .max_players                = static_cast<std::uint8_t>(msg.gameplay().max_players()),
              .view_distance              = static_cast<std::int32_t>(msg.gameplay().view_distance()),
              .reduced_debug_info         = msg.gameplay().reduced_debug_info(),
              .should_show_respawn_screen = msg.gameplay().do_immediate_respawn(),
              .is_debug                   = false,
              .is_flat                    = false,
              .death_location{}
      });

      conn->send_message(PluginMessage{"minecraft:brand", "minecpp"});

      conn->send_message(Difficulty{
              .difficulty = static_cast<mb::u8>(msg.gameplay().difficulty()),
              .locked     = false,
      });

      auto abilities = minecpp::game::Abilities::from_proto(msg.abilities());

      conn->send_message(PlayerAbilities{
              .flags         = static_cast<mb::u8>(abilities.flags()),
              .fly_speed     = abilities.fly_speed,
              .field_of_view = abilities.walk_speed,
      });

      // TODO: Send recipes and tags

      conn->send_message(EntityStatus{
              .entity_id = static_cast<mb::u8>(msg.player().entity_id()),
              .opcode    = 0x18,
      });

      // TODO: Send command list

      conn->send_message(RecipeBook{
              .state = 0,
              .crafting_table{
                              .is_open                = msg.player().recipe_book().gui_open(),
                              .is_filtering_craftable = msg.player().recipe_book().filtering_craftable(),
                              },
              .furnace{
                              .is_open                = msg.player().recipe_book().furnace_gui_open(),
                              .is_filtering_craftable = msg.player().recipe_book().furnace_filtering_craftable(),
                              },
              .blaster{
                              .is_open                = msg.player().recipe_book().furnace_gui_open(),
                              .is_filtering_craftable = msg.player().recipe_book().furnace_filtering_craftable(),
                              },
              .smoker{
                              .is_open                = msg.player().recipe_book().furnace_gui_open(),
                              .is_filtering_craftable = msg.player().recipe_book().furnace_filtering_craftable(),
                              },
              .recipes{},
              .additional_recipes{
                              RecipeList{},
                              },
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
      conn->send_message_then_disconnect(net::play::cb::Disconnect{
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
   auto add_player = net::play::cb::UpdatePlayerInfo{
           .action_bits = 0b11101,
   };
   for (const auto &item : msg.list()) {
      add_player.actions.push_back(net::play::cb::PlayerInfoChange{
              .player_id = game::player::read_id_from_proto(item.id()),
              .add_player =
                      net::play::cb::ActionAddPlayer{
                                                     .name = item.name(),
                                                     .properties{},
                                                     },
              .set_game_mode =
                      net::play::cb::ActionSetGameMode{
                                                     .game_mode = static_cast<mb::u8>(item.game_mode()),
                                                     },
              .set_is_listed =
                      net::play::cb::ActionSetIsListed{
                                                     .is_listed = 1,
                                                     },
              .set_latency =
                      net::play::cb::ActionSetLatency{
                                                     .ping = static_cast<std::int32_t>(item.ping()),
                                                     },
      });
   }
   send_message(add_player, recipient_list);
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
         conn->send_message(net::play::cb::SpawnPlayer{
                 .entity_id = entity.entity_id(),
                 .player_id = id,
                 .position{
                           .x = entity.position().x(),
                           .y = entity.position().y(),
                           .z = entity.position().z(),
                           },
                 .yaw   = encode_angle(entity.rotation().yaw()),
                 .pitch = encode_angle(entity.rotation().pitch()),
         });

         for (const auto &equipment : entity.equipment()) {
            if (equipment.item().count() == 0)
               continue;

            conn->send_message(net::play::cb::SetEquipment{
                    .entity_id = entity.entity_id(),
                    .slot_id   = static_cast<std::int8_t>(equipment.slot()),
                    .slot =
                            net::play::Slot{
                                            .item_id    = static_cast<std::int32_t>(equipment.item().item_id().id()),
                                            .item_count = static_cast<std::int8_t>(equipment.item().count()),
                                            },
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

   conn->send_message(net::play::cb::SetSlot{
           .window_id = 0,
           .state_id  = 0,
           .slot_id   = static_cast<short>(msg.slot_id()),
           .slot      = encode_slot(msg.slot()),
   });
}

void EventHandler::handle_update_block_light(const clientbound_v1::UpdateBlockLight &msg,
                                             const event::RecipientList &recipient_list)
{
   for (auto &chunk : msg.block_light()) {
      net::play::cb::UpdateLight update_block_light{
              .light_data{
                          .trust_edges = true,
                          }
      };
      update_block_light.position = net::play::Vector2vi{chunk.position().x(), chunk.position().z()};
      update_block_light.light_data.block_light.resize(chunk.sections_size());

      std::uint64_t empty_light{};
      std::uint64_t update_light{};

      // Update masks
      for (auto const &sec : chunk.sections()) {
         auto place = static_cast<char>(sec.y()) + 1;
         if (sec.block_light().empty()) {
            empty_light |= 1u << place;
         } else {
            update_light |= 1u << place;
         }
      }

      update_block_light.light_data.empty_block_light_mask.emplace_back(empty_light);
      update_block_light.light_data.block_light_mask.emplace_back(update_light);

      for (auto &section : chunk.sections()) {
         std::vector<std::uint8_t> data;
         data.resize(section.block_light().size());
         std::copy(section.block_light().begin(), section.block_light().end(), data.begin());
         update_block_light.light_data.block_light.emplace_back(std::move(data));
      }

      send_message(update_block_light, recipient_list);
   }
}

std::vector<std::uint8_t> get_chunk_data(const proto::chunk::Chunk &chunk)
{
   network::message::Writer chunk_data_writer;
   int index = 0;
   for (const auto &sec : chunk.sections()) {
      auto section = world::Section::from_proto(sec);

      chunk_data_writer.write_big_endian<short>(static_cast<short>(sec.ref_count()));

      if (section.data().indices().raw().empty()) {
         section.data().set(4095, 0);
      }

      if (section.data().indices().bits() <= 4) {
         section.data().indices().set_bits(5);
      }

      // write palette
      chunk_data_writer.write_byte(static_cast<uint8_t>(section.data().indices().bits()));
      chunk_data_writer.write_varint(static_cast<uint32_t>(section.data().palette().size()));
      for (auto item : section.data().palette()) {
         chunk_data_writer.write_varint(static_cast<uint32_t>(item));
      }


      // write data
      chunk_data_writer.write_big_endian_array(section.data().indices().raw().data(),
                                               static_cast<size_t>(section.data().indices().raw().size()));

      // write biomes
      chunk_data_writer.write_byte(6);// ignore palette

      auto biome_data = util::generate_packed(
              6, 64, [it = chunk.biomes().begin(), end = chunk.biomes().end()]() mutable {
                 if (it == end)
                    return 0;
                 return *(it++);
              });

      // write data
      chunk_data_writer.write_big_endian_array(biome_data.data(), biome_data.size());

      ++index;
   }

   for (int i = index; i < 16; ++i) {
      chunk_data_writer.write_big_endian<short>(0);

      // TODO: Abstract palatalized containers

      // write palette
      chunk_data_writer.write_byte(0);
      chunk_data_writer.write_varint(0);// AIR

      // write data
      chunk_data_writer.write_big_endian_array<uint64_t>(nullptr, 0);

      // write biomes
      chunk_data_writer.write_byte(0);  // ignore palette
      chunk_data_writer.write_varint(1);// default biome

      chunk_data_writer.write_big_endian_array<uint64_t>(nullptr, 0);
   }

   auto view = chunk_data_writer.view();
   std::vector<std::uint8_t> result{};
   result.resize(view.size());
   std::copy(view.data(), view.data() + view.size(), result.begin());
   return result;
}

void EventHandler::handle_chunk_data(const clientbound_v1::ChunkData &msg,
                                     const event::RecipientList &recipient_list)
{
   net::play::cb::UpdateChunk chunk_data{
           .position{
                     .x = msg.chunk().position().x(),
                     .y = msg.chunk().position().z(),
                     },
           .data = get_chunk_data(msg.chunk()),
           .light_data{
                     .trust_edges = true,
                     }
   };

   chunk_data.heightmaps.motion_blocking.resize(msg.chunk().hm_motion_blocking_size());
   std::copy(msg.chunk().hm_motion_blocking().begin(), msg.chunk().hm_motion_blocking().end(),
             chunk_data.heightmaps.motion_blocking.begin());

   chunk_data.heightmaps.world_surface.resize(msg.chunk().hm_world_surface_size());
   std::copy(msg.chunk().hm_world_surface().begin(), msg.chunk().hm_world_surface().end(),
             chunk_data.heightmaps.world_surface.begin());

   std::uint64_t empty_block_light{};
   std::uint64_t update_block_light{};
   std::uint64_t empty_sky_light{};
   std::uint64_t update_sky_light{};

   // Update masks
   for (auto const &sec : msg.chunk().sections()) {
      auto place = static_cast<char>(sec.y()) + 1;
      if (sec.sky_light().empty()) {
         empty_sky_light |= 1u << place;
      } else {
         update_sky_light |= 1u << place;
      }
      if (sec.block_light().empty()) {
         empty_block_light |= 1u << place;
      } else {
         update_block_light |= 1u << place;
      }
   }

   chunk_data.light_data.empty_block_light_mask.emplace_back(empty_block_light);
   chunk_data.light_data.block_light_mask.emplace_back(update_block_light);
   chunk_data.light_data.empty_sky_light_mask.emplace_back(empty_sky_light);
   chunk_data.light_data.sky_light_mask.emplace_back(update_sky_light);

   for (auto &section : msg.chunk().sections()) {
      std::vector<std::uint8_t> block_data;
      block_data.resize(section.block_light().size());
      std::copy(section.block_light().begin(), section.block_light().end(), block_data.begin());
      chunk_data.light_data.block_light.emplace_back(std::move(block_data));

      std::vector<std::uint8_t> sky_data;
      sky_data.resize(section.sky_light().size());
      std::copy(section.sky_light().begin(), section.sky_light().end(), sky_data.begin());
      chunk_data.light_data.sky_light.emplace_back(std::move(sky_data));
   }

   for (auto player_id : recipient_list.list) {
      auto conn = m_server.connection_by_player_id(player_id);
      if (not conn) {
         spdlog::error("connection {} is null", game::player::format_player_id(player_id));
         return;
      }

      conn->send_message(chunk_data);

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
   net::play::cb::UpdateChunkPosition chunk_position{
           .chunk_position{
                           .x = msg.position().x(),
                           .y = msg.position().z(),
                           }
   };

   for (auto player_id : recipient_list.list) {
      auto conn = m_server.connection_by_player_id(player_id);
      if (not conn) {
         spdlog::error("connection {} is null", game::player::format_player_id(player_id));
         return;
      }

      conn->send_message(chunk_position);
   }
}

void EventHandler::handle_player_position_rotation(const clientbound_v1::PlayerPositionRotation &msg,
                                                   const event::RecipientList &recipient_list)
{
   net::play::cb::PlayerPositionLook player_pos_look{
           .position =
                   {
                              .x = msg.position().x(),
                              .y = msg.position().y(),
                              .z = msg.position().z(),
                              },
           .yaw                    = msg.rotation().yaw(),
           .pitch                  = msg.rotation().pitch(),
           .flags                  = 0,
           .teleport_id            = 0,
           .has_dismounted_vehicle = false,
   };

   for (auto player_id : recipient_list.list) {
      auto conn = m_server.connection_by_player_id(player_id);
      if (not conn) {
         spdlog::error("connection {} is null", game::player::format_player_id(player_id));
         return;
      }

      conn->send_message(player_pos_look);
   }
}

void EventHandler::handle_set_spawn_position(const clientbound_v1::SetSpawnPosition &msg,
                                             const event::RecipientList &recipient_list)
{
   net::play::cb::SetDefaultSpawnPosition set_spawn{
           .position = msg.position(),
           .angle    = msg.angle(),
   };

   for (auto player_id : recipient_list.list) {
      auto conn = m_server.connection_by_player_id(player_id);
      if (not conn) {
         spdlog::error("connection {} is null", game::player::format_player_id(player_id));
         return;
      }

      conn->send_message(set_spawn);
   }
}

void EventHandler::handle_set_entity_equipment(const clientbound_v1::SetEntityEquipment &msg,
                                               const event::RecipientList &recipient_list)
{
   net::play::cb::SetEquipment set_equipment{
           .entity_id = msg.entity_id(),
           .slot_id   = static_cast<std::int8_t>(msg.equipment_slot()),
           .slot      = encode_slot(msg.item()),
   };

   send_message(set_equipment, recipient_list);
}

void EventHandler::handle_set_health(const clientbound_v1::SetHealth &msg,
                                     const event::RecipientList &recipient_list)
{
   net::play::cb::SetHealth set_health{
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
   net::play::cb::SpawnEntity spawn_entity{
           .entity_id   = entity.entity_id(),
           .unique_id   = util::read_uuid(entity.uuid().lower(), entity.uuid().upper()),
           .entity_type = static_cast<int>(entity.entity_type()),
           .position{
                     .x = entity.position().x(),
                     .y = entity.position().y(),
                     .z = entity.position().z(),
                     },
           .pitch    = encode_angle(entity.rotation().pitch()),
           .yaw      = encode_angle(entity.rotation().yaw()),
           .head_yaw = encode_angle(entity.head_yaw()),
           .data     = static_cast<int>(entity.data()),
           .velocity{
                     .x = static_cast<std::int16_t>(entity.velocity().x()),
                     .y = static_cast<std::int16_t>(entity.velocity().y()),
                     .z = static_cast<std::int16_t>(entity.velocity().z()),
                     }
   };
   send_message(spawn_entity, recipient_list);

   for (const auto &meta : entity.metadata()) {
      net::play::cb::SetEntityMetadata msg_meta{
              .entity_id = entity.entity_id(),
      };

      switch (meta.value_case()) {
      case proto::entity::Metadata::kSlot: {
         msg_meta.data[static_cast<uint8_t>(meta.index())] = encode_slot(meta.slot());
         break;
      }
      case proto::entity::Metadata::kByte: {
         msg_meta.data[static_cast<uint8_t>(meta.index())] = meta.byte();
         break;
      }
      default: break;
      }

      send_message(msg_meta, recipient_list);
   }
}

void EventHandler::handle_collect_item(const clientbound_v1::CollectItem &msg,
                                       const event::RecipientList &recipient_list)
{
   net::play::cb::PickupItem pickup_item{
           .collected_entity_id = msg.collected_entity_id(),
           .collector_entity_id = msg.collector_entity_id(),
           .count               = static_cast<std::int32_t>(msg.count()),
   };
   send_message(pickup_item, recipient_list);
}

void EventHandler::handle_remove_entity(const clientbound_v1::RemoveEntity &msg,
                                        const event::RecipientList &recipient_list)
{
   net::play::cb::RemoveEntities destroy_entity{
           .entity_ids{msg.entity_id()},
   };
   send_message(destroy_entity, recipient_list);
}

void EventHandler::handle_set_entity_velocity(const clientbound_v1::SetEntityVelocity &msg,
                                              const event::RecipientList &recipient_list)
{
   net::play::cb::SetEntityVelocity update_velocity{
           .entity_id = static_cast<std::uint32_t>(msg.entity_id()),
           .velocity{
                     .x = static_cast<std::int16_t>(msg.velocity().x()),
                     .y = static_cast<std::int16_t>(msg.velocity().y()),
                     .z = static_cast<std::int16_t>(msg.velocity().z()),
                     }
   };
   send_message(update_velocity, recipient_list);
}

void EventHandler::handle_display_death_screen(const clientbound_v1::DisplayDeathScreen &msg,
                                               const event::RecipientList &recipient_list)
{
   net::play::cb::DisplayDeathScreen display_death_screen{
           .victim_entity_id = msg.victim_entity_id(),
           .killer_entity_id = msg.killer_entity_id(),
           .message          = msg.death_message(),
   };
   send_message(display_death_screen, recipient_list);
}

void EventHandler::handle_respawn(const clientbound_v1::Respawn &msg,
                                  const event::RecipientList &recipient_list)
{
   net::play::cb::Respawn respawn{
           .dimension_codec = msg.dimension_type(),
           .dimension_name  = msg.dimension_name(),

           .seed               = static_cast<uint64_t>(msg.hashed_seed()),
           .game_mode          = static_cast<int8_t>(msg.game_mode()),
           .previous_game_mode = static_cast<int8_t>(msg.game_mode()),

           .is_debug             = msg.is_debug(),
           .is_flat              = msg.is_flat(),
           .should_copy_metadata = msg.copy_metadata(),
   };
   if (msg.has_death_location()) {
      respawn.death_location = net::play::cb::DeathLocation{
              .dimension = msg.death_dimension(),
              .position  = static_cast<int64_t>(math::Vector3::from_proto(msg.death_position()).sum()),
      };
   }

   send_message(respawn, recipient_list);
}

void EventHandler::handle_teleport_entity(const clientbound_v1::TeleportEntity &msg,
                                          const event::RecipientList &recipient_list)
{
   net::play::cb::TeleportEntity teleport_entity{
           .entity_id = msg.entity_id(),
           .position{
                     .x = msg.position().x(),
                     .y = msg.position().y(),
                     .z = msg.position().z(),
                     },
           .yaw          = encode_angle(msg.rotation().yaw()),
           .pitch        = encode_angle(msg.rotation().pitch()),
           .is_on_ground = msg.is_on_ground()
   };
   send_message(teleport_entity, recipient_list);
}

enum PlayerAbilityFlag : uint8_t
{
   None         = 0u,
   Invulnerable = 1u << 0u,
   IsFlying     = 1u << 1u,
   AllowFlying  = 1u << 2u,
   CreativeMode = 1u << 3u,
};

void EventHandler::handle_set_abilities(const clientbound_v1::SetAbilities &msg,
                                        const event::RecipientList &recipient_list)
{
   std::uint8_t flags{};
   flags |= msg.abilities().invulnerable() ? PlayerAbilityFlag::Invulnerable : PlayerAbilityFlag::None;
   flags |= msg.abilities().flying() ? PlayerAbilityFlag::IsFlying : PlayerAbilityFlag::None;
   flags |= msg.abilities().may_fly() ? PlayerAbilityFlag::AllowFlying : PlayerAbilityFlag::None;
   flags |= msg.abilities().may_build() ? PlayerAbilityFlag::CreativeMode : PlayerAbilityFlag::None;

   net::play::cb::PlayerAbilities player_abilities{
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
