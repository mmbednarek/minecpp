#pragma once
#include "../service.h"
#include "handler.h"
#include "play_handler.h"
#include <minenet/msg/io.h>

namespace Front::Protocol {

class LoginHandler : public Handler {
 public:
   explicit LoginHandler(Service &service);

   void handle(Connection &conn, MineNet::Message::Reader &r) override;
   void handle_login_start(Connection &conn, MineNet::Message::Reader &r);

   void reject(Connection &conn, std::string_view message);

 private:
   Service &service;
};

} // namespace Front::Protocol
