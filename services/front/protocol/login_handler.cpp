#include "login_handler.h"
#include <boost/log/trivial.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace Front::Protocol {

LoginHandler::LoginHandler(Service &service) : service(service) {}

void LoginHandler::handle(Connection &conn, MineNet::Message::Reader &r) {
   uint8_t op = r.read_byte();
   BOOST_LOG_TRIVIAL(debug) << "handling status op = " << (int)op;
   switch (op) {
   case 0:
      handle_login_start(conn, r);
      break;
   default:
      BOOST_LOG_TRIVIAL(info)
          << "status handler: invalid operation code " << (int)op;
   }
}

void LoginHandler::handle_login_start(Connection &conn, MineNet::Message::Reader &r) {
   std::string user_name = r.read_string();

   BOOST_LOG_TRIVIAL(info) << "establishing connection with player "
                           << user_name;

   auto response = service.login_player(user_name);
   if (!response.accepted) {
      reject(conn, response.refusal_reason);
      return;
   }

   MineNet::Message::Writer w;
   w.write_byte(2);
   w.write_string(response.user_name);
   w.write_string(boost::uuids::to_string(response.uuid));
   conn.send(w);

   service.init_player(conn, response.uuid);
}

void LoginHandler::reject(Connection &conn, std::string_view message) {
   MineNet::Message::Writer w;

   w.write_byte(0);
   std::stringstream ss;
   ss << R"({"extra":[{"color": "red", "bold": true, "text": "Disconnected"}, {"color":"gray", "text": ")";
   ss << message;
   ss << R"("}], "text": ""})";
   w.write_string(ss.str());

   conn.send_and_disconnect(w);
}

} // namespace Front::Protocol
