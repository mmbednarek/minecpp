#include "PlayHandler.h"
#include "../Connection.h"
#include "../Service.h"
#include <fmt/core.h>
#include <minecpp/chat/Chat.h>
#include <minecpp/network/message/Clientbound.h>
#include <minecpp/network/message/Serverbound.h>
#include <spdlog/spdlog.h>

namespace minecpp::service::front::Protocol {

PlayHandler::PlayHandler(Service &service) :
    service(service)
{
}

void PlayHandler::handle(const std::shared_ptr<Connection> &conn, Reader &r)
{
   using namespace minecpp::network::message;
   async_read_packet(conn, *this);

   auto op = r.read_byte();
   switch (op) {
   case 0x00: break;// confirm teleport
   case 0x04: {     //  1.19.3 OK
      ChatCommand msg;
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->uuid(), msg);
   } break;
   case 0x05: {// 1.19.3 OK
      ChatMessage msg;
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->uuid(), msg);
   } break;
   case 0x06: {// 1.19.3 OK
      ClientCommand msg;
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->uuid(), msg);
   } break;
   case 0x07: {// 1.19.3 OK
      ClientSettings msg;
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->uuid(), msg);
   } break;
   case 0x0a: {// 1.19.3 OK
      ClickWindow msg;
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->uuid(), msg);
   } break;
   case 0x0b: {// 1.19.3 OK
      // TODO: Implement
      // Close window
   } break;
   case 0x0c: {// 1.19.3 OK
      PluginMessage msg;
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->uuid(), msg);
   } break;
   case 0x0f: {// 1.19.3 OK
      Interact msg;
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->uuid(), msg);
   } break;
   case 0x11: {// 1.19.3 OK
      KeepAliveClient msg{};
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->uuid(), msg);
   } break;
   case 0x13: {// 1.19.3 OK
      PlayerPosition msg{};
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->uuid(), msg);
   } break;
   case 0x14: {// 1.19.3 OK
      PlayerPositionRotation msg{};
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->uuid(), msg);
   } break;
   case 0x15: {// 1.19.3 OK
      PlayerRotation msg{};
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->uuid(), msg);
   } break;
   case 0x16: {// 1.19.3 OK
      PlayerOnGround msg{};
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->uuid(), msg);
   } break;
   case 0x1b: {// 1.19.3 OK
      // TODO: Implement
      // Flying
   } break;
   case 0x1c: {// 1.19.3 OK
      PlayerDigging msg;
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->uuid(), msg);
   } break;
   case 0x1d: {// 1.19.3 OK
      // TODO: Implement
      // Crouching
   } break;
   case 0x28: {// 1.19.3 OK
      HeldItemChange msg{};
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->uuid(), msg);
   } break;
   case 0x2f: {// 1.19.3 OK
      AnimateHandClient msg{};
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->uuid(), msg);
   } break;
   case 0x31: {// 1.19.3 OK
      PlayerBlockPlacement msg{};
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->uuid(), msg);
   } break;
   case 0x32: {// 1.19.3 OK
      UseItem msg{};
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->uuid(), msg);
   } break;
   default:
      spdlog::info("unknown op {}, packet data: {}", op, r.get_hex_data());
      send(conn, minecpp::network::message::SystemChat{
                         .message = minecpp::chat::format_warning_unknown_op_code(op),
                         .type    = minecpp::chat::MessageType::PlayerMessage,
                 });
   }
}

void PlayHandler::handle_disconnect(Connection &conn)
{
   service.on_player_disconnect(conn.service_id(), conn.uuid());
}

}// namespace minecpp::service::front::Protocol
