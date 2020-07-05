#include "login_handler.h"
#include <boost/uuid/uuid_io.hpp>
#include <spdlog/spdlog.h>

namespace Front::Protocol {

LoginHandler::LoginHandler(Service &service, PlayHandler &play_handler)
    : service(service), play_handler(play_handler) {}

void LoginHandler::handle(const std::shared_ptr<Connection> &conn,
                          MineNet::Message::Reader &r) {
   uint8_t op = r.read_byte();
   switch (op) {
   case 0:
      handle_login_start(conn, r);
      break;
   default:
      spdlog::debug("[login protocol] unknown operation code {}", (int)op);
   }
}

constexpr int compression_threshold = 256;

void LoginHandler::handle_login_start(const std::shared_ptr<Connection> &conn,
                                      MineNet::Message::Reader &r) {
   std::string user_name = r.read_string();

   auto response = service.login_player(user_name);
   if (!response.accepted) {
      reject(conn, response.refusal_reason);
      return;
   }

   // set compression
   MineNet::Message::Writer w_comp;
   w_comp.write_byte(3);
   w_comp.write_varint(compression_threshold);
   conn->send(conn, w_comp);
   conn->set_compression_threshold(compression_threshold);

   MineNet::Message::Writer w;
   w.write_byte(2);
   w.write_uuid(response.uuid);
   w.write_string(response.user_name);
   conn->send(conn, w);

   service.init_player(conn, response.uuid, response.user_name);
   conn->async_read_packet(conn, play_handler);
}

void LoginHandler::reject(const std::shared_ptr<Connection> &conn,
                          std::string_view message) {
   MineNet::Message::Writer w;

   w.write_byte(0);
   std::stringstream ss;
   ss << R"({"extra":[{"color": "red", "bold": true, "text": "Disconnected"}, {"color":"gray", "text": ")";
   ss << message;
   ss << R"("}], "text": ""})";
   w.write_string(ss.str());

   conn->send_and_disconnect(conn, w);
}

void LoginHandler::handle_disconnect(Connection &conn) {}

} // namespace Front::Protocol
