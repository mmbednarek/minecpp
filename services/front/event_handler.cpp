#include "event_handler.h"
#include <boost/uuid/uuid.hpp>
#include <game/events.h>
#include <minenet/msg/clientbound.h>
#include <mineutils/uuid.h>
#include <spdlog/spdlog.h>

namespace Front {

EventHandler::EventHandler(Server &server) : server(server) {}

void EventHandler::accept_event(const minecpp::engine::Event &e) {
   using Game::Event;

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
   }
}

void EventHandler::on_event(AddPlayer &msg) {
   boost::uuids::uuid id{};
   Utils::decode_uuid(id, msg.uuid().data());

   auto add_player = MineNet::Message::AddPlayer{
       .id = id,
       .name = msg.name(),
       .game_mode = static_cast<uint8_t>(msg.game_mode()),
       .ping = static_cast<uint32_t>(msg.ping()),
   };
   server.for_each_connection(
       [id, add_player](const std::shared_ptr<Connection> &conn) {
          if (!conn)
             return;
          if (id == conn->get_uuid())
             return;
          send(conn, add_player);
       });
}

void EventHandler::on_event(SpawnPlayer &msg) {
   boost::uuids::uuid id{};
   Utils::decode_uuid(id, msg.uuid().data());

   auto spawn_player = MineNet::Message::SpawnPlayer{
       .entity_id = msg.id(),
       .id = id,
       .x = msg.x(),
       .y = msg.y(),
       .z = msg.z(),
       .yaw = msg.yaw(),
       .pitch = msg.pitch(),
   };

   server.for_each_connection(
       [spawn_player, id](const std::shared_ptr<Connection> &conn) {
          if (!conn)
             return;
          if (id == conn->get_uuid())
             return;
          send(conn, spawn_player);
       });
}

void EventHandler::on_event(EntityMove &pos) {
   boost::uuids::uuid id{};
   Utils::decode_uuid(id, pos.uuid().data());
   server.for_each_connection(
       [&pos, id](const std::shared_ptr<Connection> &conn) {
          if (!conn)
             return;
          if (conn->get_uuid() == id) {
             return;
          }
          send(conn, MineNet::Message::EntityMove{
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
   Utils::decode_uuid(id, pos.uuid().data());
   server.for_each_connection(
       [&pos, id](const std::shared_ptr<Connection> &conn) {
          if (!conn)
             return;
          if (conn->get_uuid() == id) {
             return;
          }
          spdlog::info("rot yaw: {}, pitch: {}", pos.yaw(), pos.pitch());
          send(conn, MineNet::Message::EntityLook{
                         .entity_id = pos.id(),
                         .yaw = pos.yaw(),
                         .pitch = pos.pitch(),
                         .on_ground = true,
                     });
          send(conn, MineNet::Message::EntityHeadLook{
                         .entity_id = pos.id(),
                         .yaw = pos.yaw(),
                     });
       });
}

void EventHandler::on_event(Chat &msg) {
   server.for_each_connection([&msg](const std::shared_ptr<Connection> &conn) {
      if (!conn)
         return;
      send(conn, MineNet::Message::Chat{
                     .message = msg.message(),
                     .type = MineNet::ChatType::System,
                     .user_id = boost::uuids::uuid(),
                 });
   });
}

void EventHandler::on_event(RemovePlayer &msg) {
   boost::uuids::uuid id{};
   Utils::decode_uuid(id, msg.uuid().data());

   server.for_each_connection(
       [&msg, id](const std::shared_ptr<Connection> &conn) {
          if (!conn)
             return;
          send(conn, MineNet::Message::RemovePlayer{
                         .id = id,
                     });
          send(conn, MineNet::Message::DestroyEntity{
                         .entity_id = static_cast<uint32_t>(msg.entity_id()),
                     });
       });
}

void EventHandler::on_event(UpdateBlock &msg) {
   MineNet::Message::MultiBlockChange change{
       .chunk_x = msg.chunk_x(),
       .chunk_z = msg.chunk_z(),
       .changes{
           MineNet::Message::MultiBlockChange::Change{
               .offset = static_cast<short>(msg.offset()),
               .state = msg.state(),
           },
       },
   };

   server.for_each_connection(
       [change](const std::shared_ptr<Connection> &conn) {
          if (!conn)
             return;
          send(conn, change);
       });
}

void EventHandler::on_event(AnimateHand &msg) {
   boost::uuids::uuid id{};
   Utils::decode_uuid(id, msg.uuid().data());

   MineNet::Message::AnimateHand animate{
       .entity_id = msg.entity_id(),
       .type = static_cast<uint8_t>(msg.hand()),
   };
   server.for_each_connection(
       [id, animate](const std::shared_ptr<Connection> &conn) {
          if (!conn)
             return;
          if (conn->get_uuid() == id)
             return;
          send(conn, animate);
       });
}

} // namespace Front
