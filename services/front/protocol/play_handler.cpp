#include "play_handler.h"
#include "../connection.h"
#include "../service.h"
#include <minenet/msg/serverbound.h>
#include <mineutils/format.h>
#include <spdlog/spdlog.h>

namespace Front::Protocol {

PlayHandler::PlayHandler(Service &service) : service(service) {}

void PlayHandler::handle(const std::shared_ptr<Connection> &conn, Reader &r) {
   using namespace MineNet::Message;
   conn->async_read_packet(conn, *this);

   auto op = r.read_byte();
   switch (op) {
   case 0x00:
      break; // confirm teleport
   case 0x03: {
      ChatMessage msg;
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->get_uuid(), msg);
   } break;
   case 0x05: {
      ClientSettings msg;
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->get_uuid(), msg);
   } break;
   case 0x10: {
      KeepAliveClient msg{};
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->get_uuid(), msg);
   } break;
   case 0x12: {
      PlayerPosition msg{};
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->get_uuid(), msg);
   } break;
   case 0x13: {
      PlayerPositionRotation msg{};
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->get_uuid(), msg);
   } break;
   case 0x14: {
      PlayerRotation msg{};
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->get_uuid(), msg);
   } break;
   case 0x1b: {
      PlayerDigging msg;
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->get_uuid(), msg);
   } break;
   case 0x2b: {
      AnimateHandClient msg{};
      deserialize(r, msg);
      service.on_message(conn->service_id(), conn->get_uuid(), msg);
   } break;
   default:
      spdlog::info("unknown op {}, packet data: {}", (int)op, r.get_hex_data());
      send(conn, MineNet::Message::Chat{
                     .message = MineNet::format_system_info(Utils::format(
                         "unimplemented operation code {}", (int)op)),
                     .type = MineNet::ChatType::System,
                 });
   }
}

void PlayHandler::handle_disconnect(Connection &conn) {
   service.on_player_disconnect(conn.service_id(), conn.get_uuid());
}

} // namespace Front::Protocol
