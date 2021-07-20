#include "event_handler.h"
#include <boost/uuid/uuid_io.hpp>
#include <minecpp/game/events.h>
#include <minecpp/util/time.h>
#include <minecpp/util/uuid.h>
#include <spdlog/spdlog.h>

namespace Front {

EventHandler::EventHandler(Server &server) : server(server) {}

void EventHandler::accept_event(const minecpp::engine::Event &e) {
   using minecpp::game::Event;

   switch (e.kind()) {
   case Event::index_of<ENU("AddPlayer")>(): {
      AddPlayer pos;
      pos.ParseFromString(e.data());
      on_event(pos);
   } break;
   case Event::index_of<ENU("SpawnPlayer")>(): {
      SpawnPlayer pos;
      pos.ParseFromString(e.data());
      on_event(pos);
   } break;
   case Event::index_of<ENU("EntityMove")>(): {
      EntityMove pos;
      pos.ParseFromString(e.data());
      on_event(pos);
   } break;
   case Event::index_of<ENU("EntityLook")>(): {
      EntityLook pos;
      pos.ParseFromString(e.data());
      on_event(pos);
   } break;
   case Event::index_of<ENU("RemovePlayer")>(): {
      RemovePlayer pos;
      pos.ParseFromString(e.data());
      on_event(pos);
   } break;
   case Event::index_of<ENU("UpdateBlock")>(): {
      UpdateBlock pos;
      pos.ParseFromString(e.data());
      on_event(pos);
   } break;
   case Event::index_of<ENU("Chat")>(): {
      Chat pos;
      pos.ParseFromString(e.data());
      on_event(pos);
   } break;
   case Event::index_of<ENU("AnimateHand")>(): {
      AnimateHand pos;
      pos.ParseFromString(e.data());
      on_event(pos);
   } break;
   case Event::index_of<ENU("LoadTerrain")>(): {
      LoadTerrain pos;
      pos.ParseFromString(e.data());
      on_event(pos);
   } break;
   case Event::index_of<ENU("TransferPlayer")>(): {
      TransferPlayer pos;
      pos.ParseFromString(e.data());
      on_event(pos);
   } break;
   case Event::index_of<ENU("UnloadChunk")>(): {
      UnloadChunk pos;
      pos.ParseFromString(e.data());
      on_unload_chunk(pos);
   } break;
   }
}

void EventHandler::on_event(AddPlayer &msg) {
   boost::uuids::uuid id{};
   minecpp::util::decode_uuid(id, msg.uuid().data());

   auto add_player = minecpp::network::message::AddPlayer{
           .id = id,
           .name = msg.name(),
           .game_mode = static_cast<uint8_t>(msg.game_mode()),
           .ping = static_cast<uint32_t>(msg.ping()),
   };
   server.for_each_connection([id, add_player](const std::shared_ptr<Connection> &conn) {
      if (!conn)
         return;
      if (id == conn->uuid())
         return;
      send(conn, add_player);
   });
}

void EventHandler::on_event(SpawnPlayer &msg) {
   boost::uuids::uuid id{};
   minecpp::util::decode_uuid(id, msg.uuid().data());

   auto spawn_player = minecpp::network::message::SpawnPlayer{
           .entity_id = msg.id(),
           .id = id,
           .x = msg.x(),
           .y = msg.y(),
           .z = msg.z(),
           .yaw = msg.yaw(),
           .pitch = msg.pitch(),
   };

   server.for_each_connection([spawn_player, id](const std::shared_ptr<Connection> &conn) {
      if (!conn)
         return;
      if (id == conn->uuid())
         return;
      send(conn, spawn_player);
   });
}

void EventHandler::on_event(EntityMove &pos) {
   boost::uuids::uuid id{};
   minecpp::util::decode_uuid(id, pos.uuid().data());
   server.for_each_connection([&pos, id](const std::shared_ptr<Connection> &conn) {
      if (!conn)
         return;
      if (conn->uuid() == id) {
         return;
      }
      send(conn, minecpp::network::message::EntityMove{
                         .entity_id = pos.id(),
                         .x = static_cast<short>(pos.x()),
                         .y = static_cast<short>(pos.y()),
                         .z = static_cast<short>(pos.z()),
                         .yaw = pos.yaw(),
                         .pitch = pos.pitch(),
                         .on_ground = true,
                 });
   });
}

void EventHandler::on_event(EntityLook &pos) {
   boost::uuids::uuid id{};
   minecpp::util::decode_uuid(id, pos.uuid().data());
   server.for_each_connection([&pos, id](const std::shared_ptr<Connection> &conn) {
      if (!conn)
         return;
      if (conn->uuid() == id) {
         return;
      }
      spdlog::info("rot yaw: {}, pitch: {}", pos.yaw(), pos.pitch());
      send(conn, minecpp::network::message::EntityLook{
                         .entity_id = pos.id(),
                         .yaw = pos.yaw(),
                         .pitch = pos.pitch(),
                         .on_ground = true,
                 });
      send(conn, minecpp::network::message::EntityHeadLook{
                         .entity_id = pos.id(),
                         .yaw = pos.yaw(),
                 });
   });
}

void EventHandler::on_event(Chat &msg) {
   server.for_each_connection([&msg](const std::shared_ptr<Connection> &conn) {
      if (!conn)
         return;
      send(conn, minecpp::network::message::Chat{
                         .message = msg.message(),
                         .type = minecpp::network::ChatType::System,
                         .user_id = boost::uuids::uuid(),
                 });
   });
}

void EventHandler::on_event(RemovePlayer &msg) {
   boost::uuids::uuid id{};
   minecpp::util::decode_uuid(id, msg.uuid().data());

   server.for_each_connection([&msg, id](const std::shared_ptr<Connection> &conn) {
      if (!conn)
         return;
      send(conn, minecpp::network::message::RemovePlayer{
                         .id = id,
                 });
      send(conn, minecpp::network::message::DestroyEntity{
                         .entity_id = static_cast<uint32_t>(msg.entity_id()),
                 });
   });
}

void EventHandler::on_event(UpdateBlock &msg) {
   minecpp::network::message::BlockChange change{
           .block_position = static_cast<mb::u64>(msg.block_position()),
           .block_id = msg.state(),
   };

   server.for_each_connection([change](const std::shared_ptr<Connection> &conn) {
      if (!conn)
         return;
      send(conn, change);
   });
}

void EventHandler::on_event(AnimateHand &msg) {
   boost::uuids::uuid id{};
   minecpp::util::decode_uuid(id, msg.uuid().data());

   minecpp::network::message::AnimateHand animate{
           .entity_id = msg.entity_id(),
           .type = static_cast<uint8_t>(msg.hand()),
   };
   server.for_each_connection([id, animate](const std::shared_ptr<Connection> &conn) {
      if (!conn)
         return;
      if (conn->uuid() == id)
         return;
      send(conn, animate);
   });
}

void EventHandler::on_event(LoadTerrain &msg) {
   player::Id player_id{};
   minecpp::util::decode_uuid(player_id, msg.uuid().data());

   if (!server.has_connection(player_id)) {
      spdlog::error("connection {} not found", boost::uuids::to_string(player_id));
      return;
   }

   auto conn = server.connection_by_id(player_id);
   if (!conn) {
      spdlog::error("connection {} is null", boost::uuids::to_string(player_id));
      return;
   }

   send(conn, minecpp::network::message::UpdateChunkPosition{
                      .x = msg.central_chunk().x(),
                      .z = msg.central_chunk().z(),
              });

   for (const auto &coord : msg.coords()) {
      conn->push_chunk(coord.x(), coord.z());
   }
}

const char *player_transfer_message = R"({"extra":[{"color":"dark_green", "text": "player transfer"}], "text": ""})";

void EventHandler::on_event(TransferPlayer &msg) {
   player::Id player_id{};
   minecpp::util::decode_uuid(player_id, msg.player().data());

   if (!server.has_connection(player_id))
      return;

   auto conn = server.connection_by_id(player_id);

   send(conn, minecpp::network::message::Chat{
                      .message = player_transfer_message,
              });
}

void EventHandler::on_event(UpdatePlayerAbilities &msg) {
   player::Id player_id{};
   minecpp::util::decode_uuid(player_id, msg.uuid().data());
   auto conn = server.connection_by_id(player_id);

   using minecpp::network::message::PlayerAbilityFlag;
   uint8_t flags = 0;
   flags |= msg.invulnerable() ? PlayerAbilityFlag::Invulnerable : 0;
   flags |= msg.is_flying() ? PlayerAbilityFlag::IsFlying : 0;
   flags |= msg.allow_flying() ? PlayerAbilityFlag::AllowFlying : 0;
   flags |= msg.creative_mode() ? PlayerAbilityFlag::CreativeMode : 0;

   send(conn, minecpp::network::message::PlayerAbilities{
                      .flags = flags,
                      .fly_speed = msg.fly_speed(),
                      .walk_speed = msg.walk_speed(),
              });
}

void EventHandler::on_unload_chunk(UnloadChunk &msg) {
   if (auto res = minecpp::util::make_uuid(msg.uuid()); res.ok()) {
      send(server.connection_by_id(res.unwrap()), minecpp::network::message::UnloadChunk{
                                                          .chunk_x = msg.x(),
                                                          .chunk_z = msg.z(),
                                                  });
   }
}

}// namespace Front
