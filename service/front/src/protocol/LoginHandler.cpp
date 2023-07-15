#include "LoginHandler.h"

#include "minecpp/crypto/AESKey.h"
#include "minecpp/net/login/Clientbound.schema.h"
#include "minecpp/net/login/Serverbound.schema.h"

#include <boost/uuid/uuid_io.hpp>
#include <spdlog/spdlog.h>

namespace minecpp::service::front::protocol {

constexpr int g_compression_threshold = 256;

LoginHandler::LoginHandler(Service &service, PlayHandler &play_handler, crypto::PrivateKey *private_key) :
    m_private_key(private_key),
    m_service(service),
    m_play_handler(play_handler)
{
}

void LoginHandler::handle(Connection &connection, minecpp::network::message::Reader &r)
{
   net::login::sb::visit_message(*this, connection, r);
}

void LoginHandler::accept_connection(Connection &connection)
{
   auto response = Service::login_player(connection.user_name);
   if (not response.accepted) {
      reject(connection, response.refusal_reason);
      return;
   }

   net::login::cb::SetCompression set_compression;
   set_compression.threshold = g_compression_threshold;
   connection.send_message(set_compression);
   connection.set_compression_threshold(g_compression_threshold);

   net::login::cb::LoginSuccess login_success;
   login_success.player_id = response.id;
   login_success.username  = response.user_name;
   connection.send_message(login_success);

   m_service.init_player(connection, response.id, response.user_name);
   connection.async_read_packet(m_play_handler);
}

void LoginHandler::on_login_start(Connection &connection, const net::login::sb::LoginStart &login_start)
{
   spdlog::info("login-handler: login request from user {}", login_start.name);
   connection.user_name = login_start.name;

   if (m_private_key == nullptr) {
      accept_connection(connection);
      return;
   }

   auto public_key = m_private_key->public_key();
   if (public_key.has_failed()) {
      spdlog::warn("login-handler: no valid public key");
      accept_connection(connection);
      return;
   }

   net::login::cb::EncryptionRequest request;
   request.server_id = "minecpp";
   request.public_key.resize(public_key->size());
   std::copy(public_key->data(), public_key->data() + public_key->size(), request.public_key.begin());
   request.token = {'A', 'A', 'B', 'B'};
   connection.send_message(request);

   connection.async_read_packet(*this);
}

void LoginHandler::on_encryption_response(Connection &connection,
                                          net::login::sb::EncryptionResponse &encryption_response)
{
   spdlog::debug("encryption enabled");

   container::BufferView shared_secret{encryption_response.shared_secret.data(),
                                       encryption_response.shared_secret.size()};
   auto encryption_key = m_private_key->decrypt_message(shared_secret);
   if (not encryption_key.ok()) {
      LoginHandler::reject(connection, "Failed to establish encryption");
      return;
   }

   connection.set_encryption(encryption_key->as_view());
   accept_connection(connection);
}

void LoginHandler::on_plugin_response(Connection & /*connection*/,
                                      const net::login::sb::PluginResponse &plugin_response)
{
   spdlog::info("login-handler: received plugin response message: {}", plugin_response.message_id);
}

void LoginHandler::on_failure(Connection & /*connection*/, std::uint8_t message_id)
{
   spdlog::warn("login-handler: unknown operation code {}", static_cast<int>(message_id));
}

void LoginHandler::handle_disconnect(Connection & /*connection*/)
{
   spdlog::info("login-handler: player disconnected while logging in");
}

void LoginHandler::reject(Connection &connection, std::string_view message)
{
   std::stringstream ss;
   ss << R"({"extra":[{"color": "red", "bold": true, "text": "Disconnected"}, {"color":"gray", "text": ")";
   ss << message;
   ss << R"("}], "text": ""})";

   net::login::cb::Disconnect disconnect_msg;
   disconnect_msg.reason = ss.str();
   connection.send_message_then_disconnect(disconnect_msg);
}

}// namespace minecpp::service::front::protocol
