#include "play_handler.h"
#include "../connection.h"
#include "../service.h"
#include <minenet/msg/serverbound.h>
#include <mineutils/format.h>
#include <spdlog/spdlog.h>

namespace Front::Protocol {

PlayHandler::PlayHandler(Service &service) : service(service) {}

void PlayHandler::handle(Connection &conn, Reader &r) {
   using namespace MineNet::Message;

   auto op = r.read_byte();
   switch (op) {
   case 0x00:
      break; // confirm teleport
   case 0x03: {
      ChatMessage msg;
      deserialize(r, msg);
      service.on_message(conn.get_uuid(), msg);
   } break;
   case 0x05: {
      ClientSettings msg;
      deserialize(r, msg);
      service.on_message(conn.get_uuid(), msg);
   } break;
   case 0x11: {
      PlayerPosition msg;
      deserialize(r, msg);
      service.on_message(conn.get_uuid(), msg);
   } break;
   case 0x12: {
      PlayerPositionRotation msg;
      deserialize(r, msg);
      service.on_message(conn.get_uuid(), msg);
   } break;
   case 0x13: {
      PlayerRotation msg;
      deserialize(r, msg);
      service.on_message(conn.get_uuid(), msg);
   } break;
   default:
      spdlog::info("unknown op {}, packet data: {}", (int)op, r.get_hex_data());
      conn.send(MineNet::Message::Chat{
          .message = MineNet::format_system_info(
              Utils::format("unimplemented operation code {}", (int)op)),
          .type = MineNet::ChatType::System,
      });
   }

   conn.async_read_packet(*this);
}

} // namespace Front::Protocol
