#include "login_handler.h"
#include "../connection.h"
#include <boost/log/trivial.hpp>

namespace Front::Protocol {

LoginHandler::LoginHandler(PlayerManager &players, PlayHandler &play_handler)
    : players(players), play_handler(play_handler) {}

void LoginHandler::handle(Packet::Writer &w, Packet::Reader &r) {
   uint8_t op = r.read_byte();
   BOOST_LOG_TRIVIAL(debug) << "handling status op = " << (int)op;
   switch (op) {
   case 0:
      handle_login_start(w, r);
      break;
   default:
      BOOST_LOG_TRIVIAL(info)
          << "status handler: invalid operation code " << (int)op;
   }
}

void LoginHandler::handle_login_start(Packet::Writer &w, Packet::Reader &r) {
   std::string user_name = r.read_string();
   BOOST_LOG_TRIVIAL(info) << "establishing connection with player "
                           << user_name;

   auto player = new Player(user_name);

   try {
      players.add_player(player);
   } catch (PlayerException &e) {
      BOOST_LOG_TRIVIAL(info)
          << "rejected player " << player->name() << ", reason: " << e.what();
      reject(w, e.what());
      return;
   }

   // TODO: Encryption authentication etc.

   w.write_byte(2);
   w.write_string(player->user_id());
   w.write_string(player->name());

   //	play_handler.init_player(w, *player);
}

void LoginHandler::reject(Packet::Writer &w, std::string_view message) {
   w.write_byte(0);

   std::stringstream ss;
   ss << R"({"extra":[{"color": "red", "bold": true, "text": "Disconnected"}, {"color":"gray", "text": ")";
   ss << message;
   ss << R"("}], "text": ""})";

   w.write_string(ss.str());
   w.disconnect();
}

} // namespace Front::Protocol
