#pragma once

#include "../Service.h"
#include "Handler.h"
#include "PlayHandler.h"

#include "minecpp/crypto/Key.h"
#include "minecpp/network/message/Io.h"

namespace minecpp::net::login::sb {
class LoginStart;
class EncryptionResponse;
class PluginResponse;
}// namespace minecpp::net::login::sb

namespace minecpp::service::front::protocol {

class LoginHandler : public Handler
{
 public:
   explicit LoginHandler(Service &service, PlayHandler &play_handler, crypto::PrivateKey *private_key);

   void handle(const std::shared_ptr<Connection> &conn, minecpp::network::message::Reader &r) override;

   void on_login_start(const std::shared_ptr<Connection> &conn, const net::login::sb::LoginStart &login_start);
   void on_encryption_response(const std::shared_ptr<Connection> &conn, net::login::sb::EncryptionResponse &encryption_response);
   static void on_plugin_response(const std::shared_ptr<Connection> &conn, const net::login::sb::PluginResponse &plugin_response);
   static void on_failure(const std::shared_ptr<Connection> &conn, std::uint8_t message_id);
   void handle_disconnect(Connection &conn) override;

   bool write_encryption_request(const std::shared_ptr<Connection> &conn);

   static void reject(const std::shared_ptr<Connection> &conn, std::string_view message);

 private:
   void accept_connection(const std::shared_ptr<Connection> &conn);

   crypto::PrivateKey *m_private_key;
   Service &m_service;
   PlayHandler &m_play_handler;
};

}// namespace minecpp::service::front::protocol
