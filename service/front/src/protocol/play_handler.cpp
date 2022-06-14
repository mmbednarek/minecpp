#include "play_handler.h"
#include "../connection.h"
#include "../service.h"
#include <minecpp/network/message/serverbound.h>
#include <minecpp/util/format.h>
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
   case 0x03: {
      ChatCommand msg;
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->uuid(), msg);
   } break;
   case 0x04: {
      ChatMessage msg;
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->uuid(), msg);
   } break;
   case 0x07: {
      ClientSettings msg;
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->uuid(), msg);
   } break;
   case 0x0a: {
      ClickWindow msg;
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->uuid(), msg);
   } break;
   case 0x0c: {
      PluginMessage msg;
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->uuid(), msg);
   } break;
   case 0x11: {
      KeepAliveClient msg{};
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->uuid(), msg);
   } break;
   case 0x13: {
      PlayerPosition msg{};
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->uuid(), msg);
   } break;
   case 0x14: {
      PlayerPositionRotation msg{};
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->uuid(), msg);
   } break;
   case 0x15: {
      PlayerRotation msg{};
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->uuid(), msg);
   } break;
   case 0x1c: {
      PlayerDigging msg;
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->uuid(), msg);
   } break;
   case 0x27: {
      HeldItemChange msg{};
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->uuid(), msg);
   } break;
   case 0x2e: {
      AnimateHandClient msg{};
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->uuid(), msg);
   } break;
   case 0x30: {
      PlayerBlockPlacement msg{};
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->uuid(), msg);
   } break;
   default:
      spdlog::info("unknown op {}, packet data: {}", (int) op, r.get_hex_data());
      send(conn, minecpp::network::message::SystemChat{
                         .message = minecpp::network::format_system_info(
                                 minecpp::util::format("unimplemented operation code {}", (int) op)),
                         .type = minecpp::network::ChatType::System,
                 });
   }
}

void PlayHandler::handle_disconnect(Connection &conn)
{
   service.on_player_disconnect(conn.service_id(), conn.uuid());
}

}// namespace minecpp::service::front::Protocol
