#include "server.h"
#include "protocol/protocol.h"
#include <boost/asio.hpp>
#include <minenet/msg/reader.h>
#include <spdlog/spdlog.h>

namespace Front {

Server::Server(boost::asio::io_context &ctx, short port,
               Protocol::Handler *play, Protocol::Handler *status,
               Protocol::Handler *login)
    : acceptor(ctx, tcp::endpoint(tcp::v4(), port)), handlers{play, status,
                                                              login} {
   accept_conn();
}

Server::~Server() {
   for (auto conn : connections) {
      delete conn;
   }
}

void Server::accept_conn() {
   auto conn = new Connection(
       (boost::asio::io_context &)acceptor.get_executor().context(), this);
   acceptor.async_accept(
       conn->socket, [this, conn](const boost::system::error_code &err) {
          if (err) {
             delete conn;
             spdlog::error("error accepting connection: {}", err.message());
             accept_conn();
             return;
          }

          handshake(conn);
          accept_conn();
       });
}

void Server::handshake(Connection *conn) {
   uint8_t packet_size;
   try {
      packet_size = conn->read_packet_size();
   } catch (std::exception &e) {
      delete conn;
      return;
   }

   if (packet_size == 0) {
      delete conn;
      return;
   }

   boost::asio::streambuf buff(packet_size);

   try {
      conn->read(buff);
   } catch (std::exception &e) {
      delete conn;
      return;
   }

   std::istream s(&buff);
   MineNet::Message::Reader r(s);

   if (r.read_byte() != 0) {
      delete conn;
      return;
   }

   auto protocol_version = r.read_varint();
   auto host = r.read_string();
   auto port = r.read_big_endian<uint16_t>();
   auto request_state = static_cast<Protocol::State>(r.read_varint());

   if (request_state != Protocol::Login && request_state != Protocol::Status) {
      delete conn;
      return;
   }

   conn->set_state(request_state);
   conn->id = connections.size();
   connections.emplace_back(conn);
   conn->async_read_packet(*handlers[request_state]);
}

void Server::drop_connection(int id) {
   if (id >= connections.size())
      return;

   delete connections[id];
   connections[id] = nullptr;
}

void Server::for_each_connection(std::function<void(Connection *)> f) {
   std::for_each(connections.begin(), connections.end(), f);
}

Protocol::Handler &Server::get_handler(const Protocol::State state) {
   return *handlers[state];
}

} // namespace Front
