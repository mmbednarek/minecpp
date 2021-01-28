#include "connection.h"
#include "server.h"
#include <boost/asio.hpp>
#include <boost/asio/socket_base.hpp>
#include <boost/endian/conversion.hpp>
#include <minecpp/util/compression.h>
#include <spdlog/spdlog.h>

namespace Front {

Connection::Connection(boost::asio::io_context &ctx, Server *server)
    : socket(ctx), _state(Protocol::Handshake), server(server) {}

Connection::~Connection() {
   if (server && state() != Protocol::State::Handshake) {
      server->get_handler(_state).handle_disconnect(*this);
   }

   if (!socket.is_open())
      return;

   try {
      socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
      socket.close();
   } catch (std::runtime_error &e) {
      spdlog::info("exception while closing connection: {}", e.what());
   }
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

// we need to make sure
void Connection::async_read_packet(const Ptr &conn, Protocol::Handler &h) {
   boost::asio::async_read(
       socket, boost::asio::buffer(&leading_byte, 1),
       [conn, &h](const boost::system::error_code &err, size_t size) {
          if (err) {
             spdlog::debug("error reading data from client: {}", err.message());
             conn->get_server()->drop_connection(conn->id);
             return;
          }

          conn->async_read_packet_data(conn, h);
       });
}

void Connection::async_read_packet_data(const Ptr &conn, Protocol::Handler &h) {
   size_t msg_size = read_packet_size(leading_byte);
   if (msg_size > 0) {
      packet_buff = new boost::asio::streambuf(msg_size);
   }

   boost::asio::async_read(
       socket, *packet_buff,
       [conn, &h](const boost::system::error_code &err, size_t size) {
          if (err) {
             delete conn->packet_buff;
             conn->packet_buff = nullptr;
             spdlog::debug("error reading data from client: {}", err.message());
             conn->get_server()->drop_connection(conn->id);
             return;
          }
          std::istream s(conn->packet_buff);

          if (conn->compression_threshold > 0) {
             // compressed
             MineNet::Message::Reader r(s);
             auto decompressed_size = r.read_varint();
             if (decompressed_size == 0) {
                // threshold not reached
                h.handle(conn, r);
             } else {
                Utils::ZlibInputStream decompress(s);
                MineNet::Message::Reader decompress_reader(decompress);
                h.handle(conn, decompress_reader);
             }
          } else {
             // not compressed
             MineNet::Message::Reader r(s);
             h.handle(conn, r);
          }

          delete conn->packet_buff;
          conn->packet_buff = nullptr;
       });
}

void Connection::async_write_then_read(const Ptr &conn, uint8_t *buff,
                                       size_t size, Protocol::Handler &h) {
   boost::asio::async_write(
       socket, boost::asio::buffer(buff, size),
       [conn, buff, &h](const boost::system::error_code &err, size_t size) {
          delete[] buff;

          if (err) {
             spdlog::debug("error reading data from client: {}", err.message());
             conn->get_server()->drop_connection(conn->id);
             return;
          }

          conn->async_read_packet(conn, h);
       });
}

void Connection::async_write(const Ptr &conn, uint8_t *buff, size_t size) {
   boost::asio::async_write(
       socket, boost::asio::buffer(buff, size),
       [conn, buff](const boost::system::error_code &err, size_t size) {
          delete[] buff;

          if (err) {
             spdlog::debug("error reading data from client: {}", err.message());
             conn->get_server()->drop_connection(conn->id);
             return;
          }
       });
}

void Connection::async_write_then_disconnect(const Ptr &conn, uint8_t *buff,
                                             size_t size) {
   boost::asio::async_write(
       socket, boost::asio::buffer(buff, size),
       [conn, buff](const boost::system::error_code &err, size_t size) {
          delete[] buff;

          if (err) {
             spdlog::debug("error reading data from client: {}", err.message());
          }

          conn->get_server()->drop_connection(conn->id);
       });
}

void Connection::send(const Ptr &conn, MineNet::Message::Writer &w) {
   auto bf = w.buff(compression_threshold);
   async_write(conn, std::get<0>(bf), std::get<1>(bf));
}

void Connection::send_and_read(const Ptr &conn, MineNet::Message::Writer &w,
                               Protocol::Handler &h) {
   auto bf = w.buff(compression_threshold);
   async_write_then_read(conn, std::get<0>(bf), std::get<1>(bf), h);
}

void Connection::send_and_disconnect(const Ptr &conn,
                                     MineNet::Message::Writer &w) {
   auto bf = w.buff(compression_threshold);
   async_write_then_disconnect(conn, std::get<0>(bf), std::get<1>(bf));
}

void Connection::set_compression_threshold(std::size_t threshold) {
   compression_threshold = threshold;
}

void Connection::set_uuid(boost::uuids::uuid uuid) {
   player_id = uuid;
   server->index_connection(uuid, id);
}

const boost::uuids::uuid &Connection::get_uuid() const { return player_id; }

Server *Connection::get_server() { return server; }

void Connection::set_non_blocking() { socket.non_blocking(true); }

void Connection::set_service_id(boost::uuids::uuid id) {
   this->engine_service_id = id;
}

boost::uuids::uuid Connection::service_id() {
   return this->engine_service_id;
}

void Connection::push_chunk(int x, int z) {
   chunk_queue.push(std::make_tuple(x, z));
}

std::tuple<int, int> Connection::pop_chunk() {
   auto chunk = chunk_queue.front();
   chunk_queue.pop();
   return chunk;
}

bool Connection::has_chunks() { return !chunk_queue.empty(); }

} // namespace Front
