#pragma once
#include "../Service.h"
#include "Handler.h"
#include "PlayHandler.h"
#include <minecpp/crypto/Key.h>
#include <minecpp/network/message/Io.h>

namespace minecpp::service::front::Protocol {

class LoginHandler : public Handler
{
 public:
   explicit LoginHandler(Service &service, PlayHandler &play_handler, crypto::PrivateKey *private_key);

   void handle(const std::shared_ptr<Connection> &conn, minecpp::network::message::Reader &r) override;
   void handle_login_start(const std::shared_ptr<Connection> &conn, minecpp::network::message::Reader &r);
   void handle_encryption_response(const std::shared_ptr<Connection> &conn,
                                   minecpp::network::message::Reader &r);
   void handle_disconnect(Connection &conn) override;

   bool write_encryption_request(std::shared_ptr<Connection> conn);

   void reject(const std::shared_ptr<Connection> &conn, std::string_view message);

 private:
   crypto::PrivateKey *m_private_key;
   Service &service;
   PlayHandler &play_handler;
   void accept_connection(const std::shared_ptr<Connection> &conn);
};

}// namespace minecpp::service::front::Protocol
