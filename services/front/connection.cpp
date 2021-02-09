#include "connection.h"
#include "server.h"
#include <boost/asio.hpp>
#include <boost/asio/socket_base.hpp>
#include <boost/endian/conversion.hpp>
#include <minecpp/util/compression.h>
#include <minecpp/util/time.h>
#include <spdlog/spdlog.h>

namespace Front {

Connection::Connection(boost::asio::io_context &ctx, Server *server)
    : m_socket(ctx), m_server(server), m_state(Protocol::Handshake) {}

Connection::~Connection() {
   if (m_server && state() != Protocol::State::Handshake) {
      m_server->get_handler(m_state).handle_disconnect(*this);
   }

   if (!m_socket.is_open())
      return;

   try {
      m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
      m_socket.close();
   } catch (std::runtime_error &e) {
      spdlog::info("exception while closing connection: {}", e.what());
   }
}

Protocol::State Connection::state() { return m_state; }

void Connection::set_state(Protocol::State s) { m_state = s; }

void Connection::async_write_then_read(const Ptr &conn, uint8_t *buff, size_t size, Protocol::Handler &h) {
   boost::asio::async_write(m_socket, boost::asio::buffer(buff, size), [conn, buff, &h](const boost::system::error_code &err, size_t size) {
      delete[] buff;

      if (err) {
         spdlog::debug("error reading data from client: {}", err.message());
         conn->get_server()->drop_connection(conn->m_id);
         return;
      }

      async_read_packet(conn, h);
   });
}

void Connection::async_write(const Ptr &conn, uint8_t *buff, size_t size) {
   auto start = minecpp::util::now_milis();
   boost::asio::async_write(m_socket, boost::asio::buffer(buff, size), [conn, start, buff](const boost::system::error_code &err, size_t size) {
      delete[] buff;

      if (err) {
         spdlog::debug("error reading data from client: {}", err.message());
         conn->get_server()->drop_connection(conn->m_id);
         return;
      }
   });
}

void Connection::async_write_then_disconnect(const Ptr &conn, uint8_t *buff, size_t size) {
   boost::asio::async_write(m_socket, boost::asio::buffer(buff, size), [conn, buff](const boost::system::error_code &err, size_t size) {
      delete[] buff;
      if (err) {
         spdlog::debug("error reading data from client: {}", err.message());
      }

      conn->get_server()->drop_connection(conn->m_id);
   });
}

void Connection::send(const Ptr &conn, minecpp::network::message::Writer &w) {
   auto bf = w.buff(m_compression_threshold);
   async_write(conn, std::get<0>(bf), std::get<1>(bf));
}

void Connection::send_and_read(const Ptr &conn, minecpp::network::message::Writer &w,
                               Protocol::Handler &h) {
   auto bf = w.buff(m_compression_threshold);
   async_write_then_read(conn, std::get<0>(bf), std::get<1>(bf), h);
}

void Connection::send_and_disconnect(const Ptr &conn,
                                     minecpp::network::message::Writer &w) {
   auto bf = w.buff(m_compression_threshold);
   async_write_then_disconnect(conn, std::get<0>(bf), std::get<1>(bf));
}

void Connection::set_compression_threshold(std::size_t threshold) {
   m_compression_threshold = threshold;
}

void Connection::set_uuid(boost::uuids::uuid uuid) {
   m_player_id = uuid;
   m_server->index_connection(uuid, m_id);
}

const boost::uuids::uuid &Connection::uuid() const { return m_player_id; }

Server *Connection::get_server() { return m_server; }

void Connection::set_non_blocking() { m_socket.non_blocking(true); }

void Connection::set_service_id(boost::uuids::uuid id) {
   this->m_engine_service_id = id;
}

boost::uuids::uuid Connection::service_id() {
   return this->m_engine_service_id;
}

void Connection::push_chunk(int x, int z) {
   m_chunk_queue.push(minecpp::game::block::ChunkPos(x, z));
}

minecpp::game::block::ChunkPos Connection::pop_chunk() {
   return m_chunk_queue.pop();
}

bool Connection::has_chunks() { return !m_chunk_queue.empty(); }

tcp::socket &Connection::socket() {
   return m_socket;
}

ConnectionId Connection::id() const {
   return m_id;
}

mb::size Connection::compression_threshold() const {
   return m_compression_threshold;
}
mb::u8 *Connection::alloc_byte() {
   return m_byte_pool.construct(0);
}

void Connection::free_byte(mb::u8 *byte) {
   m_byte_pool.destroy(byte);
}

void async_read_packet(const Connection::Ptr &conn, Protocol::Handler &handler) {
   async_read_varint(conn, 0u, 0u, [conn, &handler](mb::u32 packet_size) {
      if (packet_size == 0)
         return;

      auto packet_buff = new boost::asio::streambuf(packet_size);
      boost::asio::async_read(conn->socket(), *packet_buff, [conn, &handler, packet_buff](const boost::system::error_code &err, size_t size) {
         if (err) {
            delete packet_buff;
            spdlog::debug("error reading data from client: {}", err.message());
            conn->get_server()->drop_connection(conn->id());
            return;
         }
         std::istream s(packet_buff);

         if (conn->compression_threshold() > 0) {
            // compressed
            minecpp::network::message::Reader r(s);
            auto decompressed_size = r.read_varint();
            if (decompressed_size == 0) {
               // threshold not reached
               handler.handle(conn, r);
            } else {
               minecpp::util::ZlibInputStream decompress(s);
               minecpp::network::message::Reader decompress_reader(decompress);
               handler.handle(conn, decompress_reader);
            }
         } else {
            // not compressed
            minecpp::network::message::Reader r(s);
            handler.handle(conn, r);
         }

         delete packet_buff;
      });
   });
}

void async_read_varint(const Connection::Ptr &conn, mb::u32 result, mb::u32 shift, std::function<void(mb::u32)> callback) {
   auto bp = conn->alloc_byte();
   boost::asio::async_read(conn->socket(), boost::asio::buffer(bp, 1), [conn, result, shift, callback, bp](const boost::system::error_code &err, size_t size) {
      if (err) {
         conn->free_byte(bp);
         spdlog::debug("error reading data from client: {}", err.message());
         conn->get_server()->drop_connection(conn->id());
         return;
      }
      mb::u8 b = *bp;
      conn->free_byte(bp);

      if (b & 0x80u) {
         async_read_varint(conn, result | ((b & 0x7Fu) << shift), shift + 7u, callback);
         return;
      }

      callback(result | (b << shift));
   });
}

}// namespace Front
