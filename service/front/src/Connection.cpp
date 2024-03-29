#include "Connection.h"
#include "Server.h"
#include <boost/asio.hpp>
#include <boost/asio/socket_base.hpp>
#include <boost/endian/conversion.hpp>
#include <minecpp/util/Compression.h>
#include <minecpp/util/Time.h>
#include <spdlog/spdlog.h>

namespace minecpp::service::front {

void handle_message(const Connection::Ptr &conn, protocol::Handler &handler, const container::Buffer &buffer);

Connection::Connection(boost::asio::io_context &ctx, Server *server) :
    m_socket(ctx),
    m_server(server),
    m_state(protocol::Handshake)
{
}

Connection::~Connection()
{
   if (!m_socket.is_open())
      return;

   try {
      m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
      m_socket.close();
   } catch (std::runtime_error &e) {
      spdlog::info("exception while closing connection: {}", e.what());
   }
}

protocol::State Connection::state()
{
   return m_state;
}

void Connection::set_state(protocol::State s)
{
   m_state = s;
}

void Connection::async_write_then_read(container::Buffer buffer, protocol::Handler &handler)
{
   auto asio_buffer = boost::asio::buffer(buffer.data(), buffer.size());
   boost::asio::async_write(m_socket, asio_buffer,
                            [conn = this->shared_from_this(), &handler, buffer = std::move(buffer)](
                                    const boost::system::error_code &err, size_t /*size*/) {
                               if (err) {
                                  spdlog::error("error reading data from client: {}", err.message());
                                  if (conn->m_id.has_value()) {
                                     conn->get_server()->drop_connection(*conn->m_id);
                                  }
                                  return;
                               }

                               conn->async_read_packet(handler);
                            });
}

void Connection::async_write(container::Buffer buffer)
{
   auto asio_buffer = boost::asio::buffer(buffer.data(), buffer.size());
   boost::asio::async_write(m_socket, asio_buffer,
                            [conn = this->shared_from_this(), buffer = std::move(buffer)](
                                    const boost::system::error_code &err, size_t /*size*/) {
                               if (err) {
                                  spdlog::error("error reading data from client: {}", err.message());
                                  if (conn->m_id.has_value()) {
                                     conn->get_server()->drop_connection(*conn->m_id);
                                  }
                                  return;
                               }
                            });
}

void Connection::async_write_then_disconnect(container::Buffer buffer)
{
   auto asio_buffer = boost::asio::buffer(buffer.data(), buffer.size());
   boost::asio::async_write(m_socket, asio_buffer,
                            [conn = this->shared_from_this(), buffer = std::move(buffer)](
                                    const boost::system::error_code &err, size_t /*size*/) {
                               if (err) {
                                  spdlog::debug("error reading data from client: {}", err.message());
                               }

                               if (conn->m_id.has_value()) {
                                  conn->get_server()->drop_connection(*conn->m_id);
                               }
                            });
}

void Connection::send(minecpp::network::message::Writer &w)
{
   auto buffer = w.buff(m_compression_threshold);

   if (m_encryption_key != nullptr) {
      container::Buffer encrypt_buffer(buffer.size());
      m_encryption_key->encrypt_update_buffer(buffer.as_view(), encrypt_buffer.as_view());
      async_write(std::move(encrypt_buffer));
   } else {
      async_write(std::move(buffer));
   }
}

void Connection::send_and_read(minecpp::network::message::Writer &w, protocol::Handler &h)
{
   auto buffer = w.buff(m_compression_threshold);

   if (m_encryption_key != nullptr) {
      container::Buffer encrypt_buffer(buffer.size());
      m_encryption_key->encrypt_update_buffer(buffer.as_view(), encrypt_buffer.as_view());
      async_write_then_read(std::move(encrypt_buffer), h);
   } else {
      async_write_then_read(std::move(buffer), h);
   }
}

void Connection::send_and_disconnect(minecpp::network::message::Writer &w)
{
   auto buffer = w.buff(m_compression_threshold);

   if (m_encryption_key != nullptr) {
      container::Buffer encrypt_buffer(buffer.size());
      m_encryption_key->encrypt_update_buffer(buffer.as_view(), encrypt_buffer.as_view());
      async_write_then_disconnect(std::move(encrypt_buffer));
   } else {
      async_write_then_disconnect(std::move(buffer));
   }
}

void Connection::set_compression_threshold(std::size_t threshold)
{
   m_compression_threshold = threshold;
}

void Connection::set_uuid(boost::uuids::uuid uuid)
{
   assert(m_id.has_value());

   m_player_id = uuid;
   m_server->index_connection(uuid, *m_id);
}

const boost::uuids::uuid &Connection::uuid() const
{
   return m_player_id;
}

Server *Connection::get_server()
{
   return m_server;
}

void Connection::set_non_blocking()
{
   m_socket.non_blocking(true);
}

void Connection::set_service_id(boost::uuids::uuid id)
{
   this->m_engine_service_id = id;
}

boost::uuids::uuid Connection::service_id()
{
   return this->m_engine_service_id;
}

void Connection::push_chunk(int x, int z)
{
   m_chunk_queue.push(game::ChunkPosition{x, z});
}

minecpp::game::ChunkPosition Connection::pop_chunk()
{
   return m_chunk_queue.pop();
}

bool Connection::has_chunks()
{
   return !m_chunk_queue.empty();
}

tcp::socket &Connection::socket()
{
   return m_socket;
}

std::optional<ConnectionId> Connection::id() const
{
   return m_id;
}

mb::size Connection::compression_threshold() const
{
   return m_compression_threshold;
}

mb::u8 *Connection::alloc_byte()
{
   return m_byte_pool.construct(0);
}

void Connection::free_byte(mb::u8 *byte)
{
   m_byte_pool.destroy(byte);
}

void Connection::set_encryption(container::BufferView key)
{
   m_encryption_key = std::make_unique<crypto::AESKey>(key, key);
   if (m_encryption_key->initialise().has_failed()) {
      spdlog::error("failed to initialise encryption key");
   }
}

crypto::AESKey *Connection::encryption_key() const
{
   return m_encryption_key.get();
}

void Connection::async_read_packet(protocol::Handler &handler)
{
   this->async_read_varint(0u, 0u, [conn = this->shared_from_this(), &handler](mb::u32 packet_size) {
      if (packet_size == 0) {
         return;
      }

      container::Buffer buffer(packet_size);
      auto read_count = boost::asio::read(conn->socket(), boost::asio::buffer(buffer.data(), buffer.size()));

      if (read_count != packet_size) {
         spdlog::error("could not read packet correctly");
         return;
      }

      if (conn->encryption_key() != nullptr) {
         container::Buffer decrypted_buffer(packet_size);
         conn->encryption_key()->decrypt_update_buffer(buffer.as_view(), decrypted_buffer.as_view());
         handle_message(conn, handler, decrypted_buffer);
      } else {
         handle_message(conn, handler, buffer);
      }
   });
}

void handle_message(const Connection::Ptr &conn, protocol::Handler &handler, const container::Buffer &buffer)
{
   auto stream = buffer.make_stream();

   if (conn->compression_threshold() > 0) {
      // compressed
      network::message::Reader r(stream);
      auto decompressed_size = r.read_varint();
      if (decompressed_size == 0) {
         // threshold not reached
         handler.handle(*conn, r);
      } else {
         util::ZlibInputStream decompress(stream);
         network::message::Reader decompress_reader(decompress);
         handler.handle(*conn, decompress_reader);
      }
   } else {
      // not compressed
      network::message::Reader r(stream);
      handler.handle(*conn, r);
   }
}

void Connection::async_read_varint(mb::u32 /*result*/, mb::u32 /*shift*/,
                                   const std::function<void(mb::u32)> &callback)
{
   auto bp = this->alloc_byte();
   boost::asio::async_read(this->socket(), boost::asio::buffer(bp, 1),
                           [conn = this->shared_from_this(), callback,
                            bp](const boost::system::error_code &err, size_t size) {
                              if (err) {
                                 conn->free_byte(bp);
                                 spdlog::warn("error reading data from client: {}", err.message());
                                 const auto connection_id = conn->id();
                                 if (connection_id.has_value()) {
                                    conn->get_server()->drop_connection(*connection_id);
                                 }
                                 return;
                              }

                              if (size != 1) {
                                 spdlog::error("could not read varint byte correctly");
                                 return;
                              }

                              mb::u32 result{};
                              mb::u32 shift{};
                              mb::u8 b{};

                              for (;;) {
                                 b = *bp;

                                 if (conn->encryption_key() != nullptr) {
                                    mb::u8 decrypted_byte;
                                    container::BufferView buffer{&decrypted_byte, 1};
                                    conn->encryption_key()->decrypt_update_buffer({&b, 1}, buffer);
                                    b = decrypted_byte;
                                 }

                                 if (b & 0x80u) {
                                    result |= (b & 0x7Fu) << shift;
                                    shift += 7u;
                                    if (boost::asio::read(conn->socket(), boost::asio::buffer(bp, 1)) != 1) {
                                       spdlog::error("could not read varint byte correctly");
                                       return;
                                    }
                                    continue;
                                 }

                                 callback(result | (static_cast<mb::u32>(b) << shift));
                                 break;
                              }
                              conn->free_byte(bp);
                           });
}

}// namespace minecpp::service::front
