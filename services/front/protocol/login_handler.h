#pragma once
#include "../service.h"
#include "handler.h"
#include "play_handler.h"
#include <minenet/msg/io.h>

namespace Front::Protocol {

class LoginHandler : public Handler {
 public:
   explicit LoginHandler(Service &service, PlayHandler &play_handler);

   void handle(Connection &conn, MineNet::Message::Reader &r) override;
   void handle_login_start(Connection &conn, MineNet::Message::Reader &r);
   void handle_disconnect(Connection &conn) override;

   void reject(Connection &conn, std::string_view message);

 private:
   Service &service;
   PlayHandler &play_handler;
};

} // namespace Front::Protocol
