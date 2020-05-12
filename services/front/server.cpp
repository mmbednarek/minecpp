#include "server.h"
#include "protocol/protocol.h"
#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>
#include <packet/reader.h>

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
   acceptor.async_accept(conn->socket,
                         [this, conn](const boost::system::error_code &err) {
                            if (err) {
                               delete conn;
                               BOOST_LOG_TRIVIAL(error)
                                   << "tcp connection error: " << err.message();
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
      BOOST_LOG_TRIVIAL(debug)
          << "exception reading packet size (invalid protocol?): " << e.what();
      delete conn;
      return;
   }

   if (packet_size == 0) {
      BOOST_LOG_TRIVIAL(debug) << "required message size to be larger than 0";
      delete conn;
      return;
   }

   boost::asio::streambuf buff(packet_size);

   try {
      conn->read(buff);
   } catch (std::exception &e) {
      BOOST_LOG_TRIVIAL(debug)
          << "exception reading new client socket: " << e.what();
      delete conn;
      return;
   }

   std::istream s(&buff);
   Packet::Reader r(s);

   if (r.read_byte() != 0) {
      BOOST_LOG_TRIVIAL(debug) << "invalid handshake request";
      delete conn;
      return;
   }

   auto protocol_version = r.read_varint();
   auto host = r.read_string();
   auto port = r.read_big_endian<uint16_t>();
   auto request_state = static_cast<Protocol::State>(r.read_varint());

   if (request_state != Protocol::Login && request_state != Protocol::Status) {
      BOOST_LOG_TRIVIAL(debug) << "invalid requested state";
      delete conn;
      return;
   }

   BOOST_LOG_TRIVIAL(debug)
       << "incoming connection: protocol_ver = " << protocol_version
       << " host = " << host << " port = " << port
       << " req_state = " << Protocol::state_to_str(request_state);

   conn->set_state(request_state);
   conn->id = connections.size();
   connections.emplace_back(conn);
   conn->async_read_packet(*handlers[request_state]);
}

void Server::drop_connection(int id) {
   delete connections[id];
   connections[id] = nullptr;
}

} // namespace Front
