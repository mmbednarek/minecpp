#include "server.h"
#include "protocol/protocol.h"
#include <boost/asio.hpp>
#include <minecpp/network/message/reader.h>
#include <spdlog/spdlog.h>
#include <utility>

namespace Front {

Server::Server(boost::asio::io_context &ctx, short port,
               Protocol::Handler *play, Protocol::Handler *status,
               Protocol::Handler *login)
    : acceptor(ctx, tcp::endpoint(tcp::v4(), port)), m_handlers{play, status,
                                                                login} {
   accept_conn();
}

void Server::accept_conn() {
   auto conn = std::make_shared<Connection>(
           (boost::asio::io_context &) acceptor.get_executor().context(), this);
   acceptor.async_accept(
           conn->m_socket, [this, conn](const boost::system::error_code &err) {
              if (err) {
                 spdlog::error("error accepting connection: {}", err.message());
                 accept_conn();
                 return;
              }

              handshake(conn);
              accept_conn();
           });
}

void Server::handshake(const std::shared_ptr<Connection> &conn) {
   while (!conn->socket().non_blocking()) {
      spdlog::info("blocking socket setting to nonblocking");
      conn->socket().non_blocking(true);
   }

   async_read_varint(conn, 0u, 0u, [this, conn](mb::u32 packet_size) {
      if (packet_size == 0)
         return;

      auto buff = new boost::asio::streambuf(packet_size);
      boost::asio::async_read(conn->socket(), *buff, [this, conn, buff](const boost::system::error_code &err, size_t size) {
         if (err) {
            delete buff;
            spdlog::debug("error reading data from client: {}", err.message());
            return;
         }

         std::istream s(buff);
         minecpp::network::message::Reader r(s);
         if (r.read_byte() != 0) {
            delete buff;
            return;
         }

         auto protocol_version = r.read_varint();
         auto host = r.read_string();
         auto port = r.read_big_endian<uint16_t>();
         auto request_state = static_cast<Protocol::State>(r.read_varint());
         delete buff;

         if (request_state != Protocol::Login && request_state != Protocol::Status) {
            delete buff;
            return;
         }

         conn->set_state(request_state);
         conn->m_id = m_connections.size();
         m_connections.emplace_back(conn);

         async_read_packet(conn, *m_handlers[request_state]);
      });
   });
}

void Server::drop_connection(ConnectionId id) {
   if (id >= m_connections.size())
      return;
   m_connections[id] = nullptr;
}

void Server::for_each_connection(
        std::function<void(const std::shared_ptr<Connection> &)> f) {
   std::for_each(m_connections.begin(), m_connections.end(), std::move(f));
}

Protocol::Handler &Server::get_handler(const Protocol::State state) {
   return *m_handlers[state];
}

void Server::index_connection(boost::uuids::uuid index, std::size_t id) {
   conn_ids[index] = id;
}

bool Server::has_connection(boost::uuids::uuid player_id) {
   return conn_ids.contains(player_id);
}

std::shared_ptr<Connection>
Server::connection_by_id(boost::uuids::uuid player_id) {
   return m_connections.at(conn_ids.at(player_id));
}

}// namespace Front
