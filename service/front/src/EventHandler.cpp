#include "EventHandler.h"
#include <boost/uuid/uuid_io.hpp>
#include <minecpp/player/Player.h>
#include <minecpp/repository/Repository.h>
#include <minecpp/util/Time.h>
#include <minecpp/util/Uuid.h>
#include <spdlog/spdlog.h>

namespace minecpp::service::front {

EventHandler::EventHandler(Server &server, nbt::repository::v1::Registry &registry) :
    m_server(server),
    m_registry(registry)
{
}

void EventHandler::handle_add_player(const clientbound_v1::AddPlayer &msg,
                                     const std::vector<player::Id> &player_ids)
{
   auto add_player = minecpp::network::message::AddPlayer{
           .id        = player::read_id_from_proto(msg.player_id()),
           .name      = msg.name(),
           .game_mode = static_cast<mb::u8>(msg.game_mode()),
           .ping      = static_cast<mb::u32>(msg.ping()),
   };
   send_message(add_player, player_ids);
}

void EventHandler::handle_spawn_player(const clientbound_v1::SpawnPlayer &pos,
                                       const std::vector<player::Id> &player_ids)
{
   auto player_id = player::read_id_from_proto(pos.player_id());

   auto spawn_player = minecpp::network::message::SpawnPlayer{
           .entity_id = pos.entity_id(),
           .id        = player_id,
           .x         = pos.position().x(),
           .y         = pos.position().y(),
           .z         = pos.position().z(),
           .yaw       = pos.rotation().yaw(),
           .pitch     = pos.rotation().pitch(),
   };
   // FIXME: temporary hack to not send a Player.himself
   send_message_excluding(spawn_player, player_id);
}

void EventHandler::handle_entity_move(const clientbound_v1::EntityMove &pos,
                                      const std::vector<player::Id> &player_ids)
{
   minecpp::network::message::EntityMove entity_move{
           .entity_id = static_cast<int>(pos.entity_id()),
           .x         = static_cast<short>(pos.movement().x()),
           .y         = static_cast<short>(pos.movement().y()),
           .z         = static_cast<short>(pos.movement().z()),
           .yaw       = pos.rotation().yaw(),
           .pitch     = pos.rotation().pitch(),
           .on_ground = true,
   };
   // FIXME: temporary hack to not send a Player.himself
   auto player_id = player::read_id_from_proto(pos.player_id());
   send_message_excluding(entity_move, player_id);
}

void EventHandler::handle_entity_look(const clientbound_v1::EntityLook &pos,
                                      const std::vector<player::Id> &player_ids)
{
   minecpp::network::message::EntityLook entity_look{
           .entity_id = static_cast<int>(pos.entity_id()),
           .yaw       = pos.rotation().yaw(),
           .pitch     = pos.rotation().pitch(),
           .on_ground = true,
   };
   minecpp::network::message::EntityHeadLook entity_head_look{
           .entity_id = static_cast<int>(pos.entity_id()),
           .yaw       = pos.rotation().yaw(),
   };
   // FIXME: temporary hack to not send a Player.himself
   auto player_id = player::read_id_from_proto(pos.player_id());
   send_message_excluding(entity_look, player_id);
   send_message_excluding(entity_head_look, player_id);
}

void EventHandler::handle_chat(const clientbound_v1::Chat &chat_msg,
                               const std::vector<player::Id> &player_ids)
{
   minecpp::network::message::SystemChat chat{
           .message = chat_msg.message(),
           .type    = static_cast<chat::MessageType>(chat_msg.type()),
   };
   send_message(chat, player_ids);
}

void EventHandler::handle_remove_player(const clientbound_v1::RemovePlayer &msg,
                                        const std::vector<player::Id> &player_ids)
{
   network::message::RemovePlayer remove_player{
           .id = player::read_id_from_proto(msg.player_id()),
   };
   network::message::DestroyEntity destroy_entity{
           .entity_id = static_cast<uint32_t>(msg.entity_id()),
   };
   send_message(remove_player, player_ids);
   send_message(destroy_entity, player_ids);
}

void EventHandler::handle_update_block(const clientbound_v1::UpdateBlock &msg,
                                       const std::vector<player::Id> &player_ids)
{
   minecpp::network::message::BlockChange change{
           .block_position = static_cast<mb::u64>(msg.block_position()),
           .block_id       = msg.state(),
   };
   send_message(change, player_ids);
}

void EventHandler::handle_animate_hand(const clientbound_v1::AnimateHand &msg,
                                       const std::vector<player::Id> &player_ids)
{
   minecpp::network::message::AnimateHand animate{
           .entity_id = static_cast<int>(msg.entity_id()),
           .type      = static_cast<uint8_t>(msg.hand()),
   };
   auto player_id = player::read_id_from_proto(msg.player_id());
   send_message_excluding(animate, player_id);
}

void EventHandler::handle_acknowledge_block_change(const clientbound_v1::AcknowledgeBlockChange &msg,
                                                   const std::vector<player::Id> &player_ids)
{
   minecpp::network::message::AcknowledgeBlockChanges acknowledge{
           .sequence_id = msg.sequence_id(),
   };
   send_message(acknowledge, player_ids);
}

void EventHandler::handle_load_terrain(const clientbound_v1::LoadTerrain &msg,
                                       const std::vector<player::Id> &player_ids)
{
   for (auto &player_id : player_ids) {
      if (!m_server.has_connection(player_id)) {
         spdlog::error("connection {} not found", boost::uuids::to_string(player_id));
         return;
      }

      auto conn = m_server.connection_by_id(player_id);
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

      for (const auto &coord : msg.coords()) {
         conn->push_chunk(coord.x(), coord.z());
      }
   }
}

const char *player_transfer_message =
        R"({"extra":[{"color":"dark_green", "text": "player transfer"}], "text": ""})";

void EventHandler::handle_transfer_player(const clientbound_v1::TransferPlayer &msg,
                                          const std::vector<player::Id> &player_ids)
{
   // TODO: Implement this
}

void EventHandler::handle_update_player_abilities(const clientbound_v1::UpdatePlayerAbilities &msg,
                                                  const std::vector<player::Id> &player_ids)
{
   using minecpp::network::message::PlayerAbilityFlag;
   uint8_t flags = 0;
   flags |= msg.invulnerable() ? PlayerAbilityFlag::Invulnerable : 0;
   flags |= msg.is_flying() ? PlayerAbilityFlag::IsFlying : 0;
   flags |= msg.allow_flying() ? PlayerAbilityFlag::AllowFlying : 0;
   flags |= msg.creative_mode() ? PlayerAbilityFlag::CreativeMode : 0;

   minecpp::network::message::PlayerAbilities player_abilities{
           .flags         = flags,
           .fly_speed     = msg.fly_speed(),
           .field_of_view = msg.walk_speed(),
   };

   send_message(player_abilities, player_ids);
}

void EventHandler::handle_unload_chunk(const clientbound_v1::UnloadChunk &msg,
                                       const std::vector<player::Id> &player_ids)
{
   minecpp::network::message::UnloadChunk unload_chunk{
           .chunk_x = msg.chunk_position().x(),
           .chunk_z = msg.chunk_position().z(),
   };
   send_message(unload_chunk, player_ids);
}

void EventHandler::handle_accept_player(const clientbound_v1::AcceptPlayer &msg,
                                        const std::vector<player::Id> &player_ids)
{
   using namespace minecpp::network::message;

   for (auto player_id : player_ids) {
      spdlog::info("got player accepted");

      if (!m_server.has_connection(player_id)) {
         spdlog::error("connection {} not found", player::format_player_id(player_id));
         return;
      }

      auto conn = m_server.connection_by_id(player_id);
      if (!conn) {
         spdlog::error("connection {} is null", player::format_player_id(player_id));
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

      auto abilities = minecpp::player::Abilities::from_proto(msg.player().abilities());

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

      send(conn, PlayerPositionLook{
                         .x     = msg.player().position().x(),
                         .y     = msg.player().position().y(),
                         .z     = msg.player().position().z(),
                         .yaw   = msg.player().rotation().yaw(),
                         .pitch = msg.player().rotation().pitch(),
                         .flags = 0,
                         .tp_id = 0,
                 });


      if (m_stream != nullptr) {
         m_stream->send(proto::event::serverbound::v1::LoadInitialChunks{}, player_id);
      }
   }
}

void EventHandler::handle_deny_player(const clientbound_v1::DenyPlayer &msg,
                                      const std::vector<player::Id> &player_ids)
{
   for (auto player_id : player_ids) {
      if (!m_server.has_connection(player_id)) {
         spdlog::error("connection {} not found", player::format_player_id(player_id));
         return;
      }

      auto conn = m_server.connection_by_id(player_id);
      if (!conn) {
         spdlog::error("connection {} is null", player::format_player_id(player_id));
         return;
      }

      spdlog::error("could not join player {}.", msg.denial_reason());
      send_and_disconnect(conn, minecpp::network::message::Disconnect{
                                        .reason = msg.denial_reason(),
                                });
   }
}

void EventHandler::handle_player_list(const clientbound_v1::PlayerList &msg,
                                      const std::vector<player::Id> &player_ids)
{
   for (auto player_id : player_ids) {
      if (!m_server.has_connection(player_id)) {
         spdlog::error("connection {} not found", player::format_player_id(player_id));
         return;
      }

      auto conn = m_server.connection_by_id(player_id);
      if (!conn) {
         spdlog::error("connection {} is null", player::format_player_id(player_id));
         return;
      }

      for (auto const &player_status : msg.list()) {
         send(conn, network::message::AddPlayer{
                            .id        = player::read_id_from_proto(player_status.id()),
                            .name      = player_status.name(),
                            .game_mode = static_cast<mb::u8>(player_status.game_mode()),
                            .ping      = static_cast<mb::u32>(player_status.ping()),
                    });
      }
   }
}

void EventHandler::handle_entity_list(const clientbound_v1::EntityList &msg,
                                      const std::vector<player::Id> &player_ids)
{
   for (auto player_id : player_ids) {
      if (!m_server.has_connection(player_id)) {
         spdlog::error("connection {} not found", player::format_player_id(player_id));
         return;
      }

      auto conn = m_server.connection_by_id(player_id);
      if (!conn) {
         spdlog::error("connection {} is null", player::format_player_id(player_id));
         return;
      }

      for (auto const &entity : msg.list()) {
         auto id = player::read_id_from_proto(entity.id());
         spdlog::info("sending player data {}", to_string(id));

         if (id == player_id) {
            spdlog::info("skipping same as player id {}", to_string(player_id));
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
      }
   }
}

void EventHandler::handle_set_inventory_slot(const clientbound_v1::SetInventorySlot &msg,
                                             const std::vector<player::Id> &player_ids)
{
   assert(player_ids.size() == 1);

   const auto player_id = player_ids.front();

   auto conn = m_server.connection_by_id(player_id);
   if (!conn) {
      spdlog::error("connection {} is null", player::format_player_id(player_id));
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

}// namespace minecpp::service::front
