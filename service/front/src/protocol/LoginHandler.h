#pragma once
#include "../Service.h"
#include "Handler.h"
#include "PlayHandler.h"
#include <minecpp/network/message/Io.h>

namespace minecpp::service::front::Protocol {

class LoginHandler : public Handler
{
 public:
   explicit LoginHandler(Service &service, PlayHandler &play_handler);

   void handle(const std::shared_ptr<Connection> &conn, minecpp::network::message::Reader &r) override;
   void handle_login_start(const std::shared_ptr<Connection> &conn, minecpp::network::message::Reader &r);
   void handle_disconnect(Connection &conn) override;

   void reject(const std::shared_ptr<Connection> &conn, std::string_view message);

 private:
   Service &service;
   PlayHandler &play_handler;
};

}// namespace minecpp::service::front::Protocol
