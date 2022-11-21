#include "LoginHandler.h"
#include <boost/uuid/uuid_io.hpp>
#include <minecpp/crypto/AESKey.h>
#include <spdlog/spdlog.h>

namespace minecpp::service::front::Protocol {

LoginHandler::LoginHandler(Service &service, PlayHandler &play_handler, crypto::PrivateKey *private_key) :
    m_private_key(private_key),
    service(service),
    play_handler(play_handler)
{
}

void LoginHandler::handle(const std::shared_ptr<Connection> &conn, minecpp::network::message::Reader &r)
{
   uint8_t op = r.read_byte();
   switch (op) {
   case 0: handle_login_start(conn, r); break;
   case 1: handle_encryption_response(conn, r); break;
   default: spdlog::debug("[login protocol] unknown operation code {}", (int) op);
   }
}

constexpr int compression_threshold = 256;

void LoginHandler::handle_login_start(const std::shared_ptr<Connection> &conn,
                                      minecpp::network::message::Reader &r)
{
   spdlog::info("login start");

   conn->user_name = r.read_string();

   if (m_private_key == nullptr) {
      accept_connection(conn);
      return;
   }

   this->write_encryption_request(conn);
   async_read_packet(conn, *this);
}

void LoginHandler::reject(const std::shared_ptr<Connection> &conn, std::string_view message)
{
   minecpp::network::message::Writer w;

   w.write_byte(0);
   std::stringstream ss;
   ss << R"({"extra":[{"color": "red", "bold": true, "text": "Disconnected"}, {"color":"gray", "text": ")";
   ss << message;
   ss << R"("}], "text": ""})";
   w.write_string(ss.str());

   conn->send_and_disconnect(conn, w);
}

void LoginHandler::handle_disconnect(Connection &conn) {}

bool LoginHandler::write_encryption_request(std::shared_ptr<Connection> conn)
{
   auto public_key = m_private_key->public_key();
   if (public_key.has_failed()) {
      return false;
   }

   minecpp::network::message::Writer writer;
   writer.write_byte(0x01);
   writer.write_string("");// server ID
   writer.write_varint(static_cast<std::uint32_t>(public_key->size()));
   writer.write_bytes(reinterpret_cast<const char *>(public_key->data()), public_key->size());
   writer.write_varint(4);
   writer.write_bytes("AAAA", 4);
   conn->send(conn, writer);

   return true;
}

void LoginHandler::handle_encryption_response(const std::shared_ptr<Connection> &conn, Reader &r)
{
   spdlog::debug("encryption enabled");

   auto secret = r.read_buffer();

   container::Buffer token;
   container::Buffer message;

   bool has_verify_token = r.read_byte();
   if (has_verify_token) {
      auto token   = r.read_buffer();
      auto salt    = r.read_long();
      auto message = r.read_buffer();
      // OK idk
   }

   auto encryption_key = m_private_key->decrypt_message(secret);
   if (not encryption_key.ok()) {
      this->reject(conn, "Failed to establish encryption");
      return;
   }

   conn->set_encryption(std::move(*encryption_key));

   accept_connection(conn);
}

void LoginHandler::accept_connection(const std::shared_ptr<Connection> &conn)
{
   auto response = service.login_player(conn->user_name);
   if (!response.accepted) {
      reject(conn, response.refusal_reason);
      return;
   }

   // set compression
   network::message::Writer w_comp;
   w_comp.write_byte(3);
   w_comp.write_varint(compression_threshold);
   conn->send(conn, w_comp);
   conn->set_compression_threshold(compression_threshold);

   network::message::Writer w;
   w.write_byte(0x02);
   w.write_uuid(response.id);
   w.write_string(response.user_name);
   w.write_varint(0);
   conn->send(conn, w);

   service.init_player(conn, response.id, response.user_name);
   async_read_packet(conn, play_handler);
}

}// namespace minecpp::service::front::Protocol
