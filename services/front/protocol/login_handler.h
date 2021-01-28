#pragma once
#include "../service.h"
#include "handler.h"
#include "play_handler.h"
#include <minecpp/network/msg/io.h>

namespace Front::Protocol {

class LoginHandler : public Handler {
 public:
   explicit LoginHandler(Service &service, PlayHandler &play_handler);

   void handle(const std::shared_ptr<Connection> &conn, MineNet::Message::Reader &r) override;
   void handle_login_start(const std::shared_ptr<Connection> &conn, MineNet::Message::Reader &r);
   void handle_disconnect(Connection &conn) override;

   void reject(const std::shared_ptr<Connection> &conn, std::string_view message);

 private:
   Service &service;
   PlayHandler &play_handler;
};

} // namespace Front::Protocol
