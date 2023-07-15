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

void LoginHandler::handle(const std::shared_ptr<Connection> &conn, minecpp::network::message::Reader &r)
{
   net::login::sb::visit_message(*this, conn, r);
}

void LoginHandler::accept_connection(const std::shared_ptr<Connection> &conn)
{
   auto response = Service::login_player(conn->user_name);
   if (!response.accepted) {
      reject(conn, response.refusal_reason);
      return;
   }

   // set compression
   net::login::cb::SetCompression set_compression;
   set_compression.threshold = g_compression_threshold;
   network::message::Writer w_comp;
   set_compression.serialize(w_comp);
   conn->send(conn, w_comp);
   conn->set_compression_threshold(g_compression_threshold);

   net::login::cb::LoginSuccess login_success;
   login_success.player_id = response.id;
   login_success.username = response.user_name;
   network::message::Writer w;
   login_success.serialize(w);
   conn->send(conn, w);

   m_service.init_player(conn, response.id, response.user_name);
   async_read_packet(conn, m_play_handler);
}

void LoginHandler::on_login_start(const std::shared_ptr<Connection> &conn,
                                  const net::login::sb::LoginStart &login_start)
{
   spdlog::info("login-handler: login request from user {}", login_start.name);
   if (m_private_key == nullptr) {
      accept_connection(conn);
      return;
   }

   auto public_key = m_private_key->public_key();
   if (public_key.has_failed()) {
      spdlog::warn("login-handler: no valid public key");
      accept_connection(conn);
      return;
   }

   net::login::cb::EncryptionRequest request;
   request.server_id = "minecpp";
   request.public_key.resize(public_key->size());
   std::copy(public_key->data(), public_key->data() + public_key->size(), request.public_key.begin());
   request.token = {'A', 'A', 'B', 'B'};

   minecpp::network::message::Writer writer;
   request.serialize(writer);
   conn->send(conn, writer);

   async_read_packet(conn, *this);
}

void LoginHandler::on_encryption_response(const std::shared_ptr<Connection> &conn,
                                          net::login::sb::EncryptionResponse &encryption_response)
{
   spdlog::debug("encryption enabled");

   container::BufferView shared_secret{encryption_response.shared_secret.data(), encryption_response.shared_secret.size()};
   auto encryption_key = m_private_key->decrypt_message(shared_secret);
   if (not encryption_key.ok()) {
      LoginHandler::reject(conn, "Failed to establish encryption");
      return;
   }

   conn->set_encryption(encryption_key->as_view());
   accept_connection(conn);
}

void LoginHandler::on_plugin_response(const std::shared_ptr<Connection> &/*conn*/,
                                      const net::login::sb::PluginResponse &plugin_response)
{
   spdlog::info("login-handler: received plugin response message: {}", plugin_response.message_id);
}

void LoginHandler::on_failure(const std::shared_ptr<Connection> &/*conn*/, std::uint8_t message_id)
{
   spdlog::warn("login-handler: unknown operation code {}", static_cast<int>(message_id));
}

void LoginHandler::handle_disconnect(Connection & /*conn*/) {
   spdlog::info("login-handler: player disconnected while logging in");
}

void LoginHandler::reject(const std::shared_ptr<Connection> &conn, std::string_view message)
{
   net::login::cb::Disconnect disconnect_msg;
   std::stringstream ss;
   ss << R"({"extra":[{"color": "red", "bold": true, "text": "Disconnected"}, {"color":"gray", "text": ")";
   ss << message;
   ss << R"("}], "text": ""})";
   disconnect_msg.reason = ss.str();
   minecpp::network::message::Writer w;
   disconnect_msg.serialize(w);
   conn->send_and_disconnect(conn, w);
}

}// namespace minecpp::service::front::protocol
