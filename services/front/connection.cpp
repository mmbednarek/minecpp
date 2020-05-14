#include "connection.h"
#include "server.h"
#include <boost/asio.hpp>
#include <boost/endian/conversion.hpp>
#include <boost/log/trivial.hpp>

namespace Front {

Connection::Connection(boost::asio::io_context &ctx, Server *server)
    : socket(ctx), _state(Protocol::Handshake), server(server) {}

Connection::~Connection() {
   socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
   socket.close();
}

size_t Connection::read(void *ptr, size_t size) {
   return boost::asio::read(socket, boost::asio::buffer(ptr, size));
}

size_t Connection::read(boost::asio::streambuf &buff) {
   return boost::asio::read(socket, buff);
}

size_t Connection::read_packet_size() { return read_varint(0u, 0u); }

size_t Connection::read_packet_size(uint8_t leading) {
   if (~leading & 0x80u) {
      return leading;
   }
   return read_varint(leading & 0x7Fu, 7u);
}

inline size_t Connection::read_varint(uint32_t result, uint32_t shift) {
   for (;;) {
      uint8_t b;
      read(&b, sizeof(uint8_t));
      if (b & 0x80u) {
         result |= (b & 0x7Fu) << shift;
         shift += 7u;
         continue;
      }
      result |= b << shift;
      break;
   }
   return result;
}

Protocol::State Connection::state() { return _state; }

void Connection::set_state(Protocol::State s) { _state = s; }

void Connection::async_read_packet(Protocol::Handler &h) {
   boost::asio::async_read(
       socket, boost::asio::buffer(&leading_byte, 1),
       [this, &h](const boost::system::error_code &err, size_t size) {
          if (err) {
             BOOST_LOG_TRIVIAL(debug) << "inbound error " << err.message();
             server->drop_connection(id);
             return;
          }

          async_read_packet_data(h);
       });
}

void Connection::async_read_packet_data(Protocol::Handler &h) {
   BOOST_LOG_TRIVIAL(debug)
       << "reading packet data leading_byte =" << (int)leading_byte;

   size_t msg_size = read_packet_size(leading_byte);
   if (msg_size > 0) {
      packet_buff = new boost::asio::streambuf(msg_size);
   }

   boost::asio::async_read(
       socket, *packet_buff,
       [this, &h](const boost::system::error_code &err, size_t size) {
          if (err) {
             delete packet_buff;
             packet_buff = nullptr;
             BOOST_LOG_TRIVIAL(debug) << "inbound error " << err.message();
             server->drop_connection(id);
             return;
          }

          std::istream s(packet_buff);
          MineNet::Message::Reader r(s);
          h.handle(*this, r);

          delete packet_buff;
          packet_buff = nullptr;
       });
}

void Connection::async_write_then_read(uint8_t *buff, size_t size,
                                       Protocol::Handler &h) {
   boost::asio::async_write(
       socket, boost::asio::buffer(buff, size),
       [this, buff, &h](const boost::system::error_code &err, size_t size) {
          delete[] buff;

          if (err) {
             BOOST_LOG_TRIVIAL(debug)
                 << "error writing message " << err.message();
             server->drop_connection(id);
             return;
          }

          BOOST_LOG_TRIVIAL(debug) << "wrote " << size << " bytes";

          async_read_packet(h);
       });
}

void Connection::async_write(uint8_t *buff, size_t size) {
   boost::asio::async_write(
       socket, boost::asio::buffer(buff, size),
       [this, buff](const boost::system::error_code &err, size_t size) {
          delete[] buff;

          if (err) {
             BOOST_LOG_TRIVIAL(debug)
                 << "error writing message " << err.message();
             server->drop_connection(id);
             return;
          }

          BOOST_LOG_TRIVIAL(debug) << "wrote " << size << " bytes";
       });
}

void Connection::async_write_then_disconnect(uint8_t *buff, size_t size) {
   boost::asio::async_write(
       socket, boost::asio::buffer(buff, size),
       [this, buff](const boost::system::error_code &err, size_t size) {
          delete[] buff;

          if (err) {
             BOOST_LOG_TRIVIAL(debug)
                 << "error writing message " << err.message();
          } else {
             BOOST_LOG_TRIVIAL(debug) << "wrote " << size << " bytes";
          }

          server->drop_connection(id);
       });
}

void Connection::send(MineNet::Message::Writer &w) {
   auto bf = w.buff();
   async_write(std::get<0>(bf), std::get<1>(bf));
}

void Connection::send_and_read(MineNet::Message::Writer &w,
                               Protocol::Handler &h) {
   auto bf = w.buff();
   async_write_then_read(std::get<0>(bf), std::get<1>(bf), h);
}

void Connection::send_and_disconnect(MineNet::Message::Writer &w) {
   auto bf = w.buff();
   async_write_then_disconnect(std::get<0>(bf), std::get<1>(bf));
}

} // namespace Front
