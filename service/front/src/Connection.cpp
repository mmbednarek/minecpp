#include "Connection.h"
#include "Server.h"
#include <boost/asio.hpp>
#include <boost/asio/socket_base.hpp>
#include <boost/endian/conversion.hpp>
#include <minecpp/util/Compression.h>
#include <minecpp/util/Time.h>
#include <spdlog/spdlog.h>

namespace minecpp::service::front {

Connection::Connection(boost::asio::io_context &ctx, Server *server) :
    m_socket(ctx),
    m_server(server),
    m_state(Protocol::Handshake)
{
}

Connection::~Connection()
{
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

Protocol::State Connection::state()
{
   return m_state;
}

void Connection::set_state(Protocol::State s)
{
   m_state = s;
}

void Connection::async_write_then_read(const Ptr &conn, container::Buffer buffer, Protocol::Handler &h)
{
   boost::asio::async_write(
           m_socket, boost::asio::buffer(buffer.data(), buffer.size()),
           [conn, &h, buffer = std::move(buffer)](const boost::system::error_code &err, size_t size) {
              if (err) {
                 spdlog::error("error reading data from client: {}", err.message());
                 conn->get_server()->drop_connection(conn->m_id);
                 return;
              }

              async_read_packet(conn, h);
           });
}

void Connection::async_write(const Ptr &conn, container::Buffer buffer)
{
   boost::asio::async_write(
           m_socket, boost::asio::buffer(buffer.data(), buffer.size()),
           [conn, buffer = std::move(buffer)](const boost::system::error_code &err, size_t size) {
              if (err) {
                 spdlog::error("error reading data from client: {}", err.message());
                 conn->get_server()->drop_connection(conn->m_id);
                 return;
              }
           });
}

void Connection::async_write_then_disconnect(const Ptr &conn, container::Buffer buffer)
{
   boost::asio::async_write(
           m_socket, boost::asio::buffer(buffer.data(), buffer.size()),
           [conn, buffer = std::move(buffer)](const boost::system::error_code &err, size_t size) {
              if (err) {
                 spdlog::debug("error reading data from client: {}", err.message());
              }

              conn->get_server()->drop_connection(conn->m_id);
           });
}

void Connection::send(const Ptr &conn, minecpp::network::message::Writer &w)
{
   auto [bf, bf_size] = w.buff(m_compression_threshold);

   if (m_encryption_key != nullptr) {
      container::Buffer buffer(bf_size);
      m_encryption_key->encrypt_update_buffer({bf, bf_size}, buffer);
      async_write(conn, std::move(buffer));
   } else {
      async_write(conn, {bf, bf_size});
   }
}

void Connection::send_and_read(const Ptr &conn, minecpp::network::message::Writer &w, Protocol::Handler &h)
{
   auto [bf, bf_size] = w.buff(m_compression_threshold);

   if (m_encryption_key != nullptr) {
      container::Buffer buffer(bf_size);
      m_encryption_key->encrypt_update_buffer({bf, bf_size}, buffer);
      async_write_then_read(conn, std::move(buffer), h);
   } else {
      async_write_then_read(conn, {bf, bf_size}, h);
   }
}

void Connection::send_and_disconnect(const Ptr &conn, minecpp::network::message::Writer &w)
{
   auto [bf, bf_size] = w.buff(m_compression_threshold);

   if (m_encryption_key != nullptr) {
      container::Buffer buffer(bf_size);
      m_encryption_key->encrypt_update_buffer({bf, bf_size}, buffer);
      async_write_then_disconnect(conn, std::move(buffer));
   } else {
      async_write_then_disconnect(conn, {bf, bf_size});
   }
}

void Connection::set_compression_threshold(std::size_t threshold)
{
   m_compression_threshold = threshold;
}

void Connection::set_uuid(boost::uuids::uuid uuid)
{
   m_player_id = uuid;
   m_server->index_connection(uuid, m_id);
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
   m_chunk_queue.push({x, z});
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

ConnectionId Connection::id() const
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

void Connection::set_encryption(container::Buffer key)
{
   container::Buffer iv(key);
   m_encryption_key = std::make_unique<crypto::AESKey>(std::move(key), std::move(iv));
   if (m_encryption_key->initialise().has_failed()) {
      spdlog::error("failed to initialise encryption key");
   }
}

crypto::AESKey *Connection::encryption_key() const
{
   return m_encryption_key.get();
}

void handle_message(const Connection::Ptr &conn, Protocol::Handler &handler, const container::Buffer &buffer);

void async_read_packet(const Connection::Ptr &conn, Protocol::Handler &handler)
{
   async_read_varint(conn, 0u, 0u, [conn, &handler](mb::u32 packet_size) {
      if (packet_size == 0)
         return;

      auto buffer = container::Buffer(packet_size);
      boost::asio::async_read(conn->socket(), boost::asio::buffer(buffer.data(), buffer.size()),
                              [conn, &handler, buffer = std::move(buffer)](
                                      const boost::system::error_code &err, size_t size) {
                                 if (err) {
                                    spdlog::debug("error reading data from client: {}", err.message());
                                    conn->get_server()->drop_connection(conn->id());
                                    return;
                                 }

                                 if (conn->encryption_key() != nullptr) {
                                    container::Buffer decrypted_buffer(size);
                                    conn->encryption_key()->decrypt_update_buffer(buffer, decrypted_buffer);
                                    handle_message(conn, handler, decrypted_buffer);
                                 } else  {
                                    handle_message(conn, handler, buffer);
                                 }
                              });
   });
}

void handle_message(const Connection::Ptr &conn, Protocol::Handler &handler, const container::Buffer &buffer)
{
   auto stream = buffer.make_stream();

   if (conn->compression_threshold() > 0) {
      // compressed
      network::message::Reader r(stream);
      auto decompressed_size = r.read_varint();
      if (decompressed_size == 0) {
         // threshold not reached
         handler.handle(conn, r);
      } else {
         util::ZlibInputStream decompress(stream);
         network::message::Reader decompress_reader(decompress);
         handler.handle(conn, decompress_reader);
      }
   } else {
      // not compressed
      network::message::Reader r(stream);
      handler.handle(conn, r);
   }
}

void handle_varint_byte(const Connection::Ptr &conn, mb::u32 result, mb::u32 shift,
                        const std::function<void(mb::u32)> &callback, mb::u8 b);

void async_read_varint(const Connection::Ptr &conn, mb::u32 result, mb::u32 shift,
                       const std::function<void(mb::u32)> &callback)
{
   auto bp = conn->alloc_byte();
   boost::asio::async_read(
           conn->socket(), boost::asio::buffer(bp, 1),
           [conn, result, shift, callback, bp](const boost::system::error_code &err, size_t size) {
              if (err) {
                 conn->free_byte(bp);
                 spdlog::debug("error reading data from client: {}", err.message());
                 conn->get_server()->drop_connection(conn->id());
                 return;
              }

              mb::u8 b = *bp;
              conn->free_byte(bp);

              if (conn->encryption_key() != nullptr) {
                 mb::u8 decrypted_byte;
                 container::Buffer buffer{&decrypted_byte, 1};
                 conn->encryption_key()->decrypt_update_buffer({&b, 1}, buffer);
                 handle_varint_byte(conn, result, shift, callback, decrypted_byte);
              } else {
                 handle_varint_byte(conn, result, shift, callback, b);
              }
           });
}

void handle_varint_byte(const Connection::Ptr &conn, mb::u32 result, mb::u32 shift,
                        const std::function<void(mb::u32)> &callback, mb::u8 b)
{
   if (b & 0x80u) {
      async_read_varint(conn, result | ((b & 0x7Fu) << shift), shift + 7u, callback);
      return;
   }

   callback(result | (b << shift));
}

}// namespace minecpp::service::front
