#pragma once
#include "../packet/reader.h"
#include "../packet/writer.h"
#include "../players.h"
#include "handler.h"
#include "play_handler.h"

namespace Front::Protocol {

class LoginHandler : public Handler {
 public:
   LoginHandler(PlayerManager &players, PlayHandler &play_handler);

   void handle(Connection &conn, Packet::Reader &r) override;
   void handle_login_start(Packet::Writer &w, Packet::Reader &r);

   void reject(Packet::Writer &w, std::string_view message);

 private:
   PlayerManager &players;
   PlayHandler &play_handler;
};

} // namespace Front::Protocol
