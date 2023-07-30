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

   void handle(Connection &connection, minecpp::network::message::Reader &reader) override;

   void on_login_start(Connection &connection, const net::login::sb::LoginStart &login_start);
   void on_encryption_response(Connection &connection,
                               net::login::sb::EncryptionResponse &encryption_response);
   static void on_plugin_response(Connection &connection,
                                  const net::login::sb::PluginResponse &plugin_response);
   static void on_failure(Connection &connection, std::uint8_t message_id);
   void handle_disconnect(Connection &conn) override;

   bool write_encryption_request(Connection &connection);

   static void reject(Connection &connection, std::string_view message);

 private:
   void accept_connection(Connection &connection);

   crypto::PrivateKey *m_private_key;
   Service &m_service;
   PlayHandler &m_play_handler;
};

}// namespace minecpp::service::front::protocol
