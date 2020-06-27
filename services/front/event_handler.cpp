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
   }
}

void EventHandler::on_event(EntityMove &pos) {
   boost::uuids::uuid id{};
   Utils::decode_uuid(id, pos.uuid().data());
   server.for_each_connection([&pos, id](Connection *conn) {
      if (!conn)
         return;
      if (conn->get_uuid() == id) {
         return;
      }
      conn->send(MineNet::Message::EntityMove{
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
   server.for_each_connection([&pos, id](Connection *conn) {
      if (!conn)
         return;
      if (conn->get_uuid() == id) {
         return;
      }
      spdlog::info("rot yaw: {}, pitch: {}", pos.yaw(), pos.pitch());
      conn->send(MineNet::Message::EntityLook{
          .entity_id = pos.id(),
          .yaw = pos.yaw(),
          .pitch = pos.pitch(),
          .on_ground = true,
      });
      conn->send(MineNet::Message::EntityHeadLook{
          .entity_id = pos.id(),
          .yaw = pos.yaw(),
      });
   });
}

void EventHandler::on_event(SpawnPlayer &pos) {
   boost::uuids::uuid id{};
   Utils::decode_uuid(id, pos.uuid().data());

   server.for_each_connection([&pos, id](Connection *conn) {
      conn->send(MineNet::Message::SpawnPlayer{
          .entity_id = pos.id(),
          .id = id,
          .x = pos.x(),
          .y = pos.y(),
          .z = pos.z(),
          .yaw = pos.yaw(),
          .pitch = pos.pitch(),
      });
   });
}

void EventHandler::on_event(Chat &msg) {
   server.for_each_connection([&msg](Connection *conn) {
      if (!conn)
         return;
      conn->send(MineNet::Message::Chat{
          .message = msg.message(),
      });
   });
}

void EventHandler::on_event(RemovePlayer &msg) {
   boost::uuids::uuid id{};
   Utils::decode_uuid(id, msg.uuid().data());

   server.for_each_connection([&msg, id](Connection *conn) {
      if (!conn)
         return;
      conn->send(MineNet::Message::RemovePlayer{
          .id = id,
      });
      conn->send(MineNet::Message::DestroyEntity{
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

   server.for_each_connection([change](Connection *conn) {
      if (!conn)
         return;
      conn->send(change);
   });
}

} // namespace Front
