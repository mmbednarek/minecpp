#pragma once
#include "protocol/handler.h"
#include "protocol/protocol.h"
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/pool/object_pool.hpp>
#include <boost/uuid/uuid.hpp>
#include <mb/int.h>
#include <memory>
#include <minecpp/game/block/position.h>
#include <minecpp/network/message/io.h>
#include <minecpp/network/message/message.h>
#include <minecpp/util/static_queue.h>
#include <queue>
#include <spdlog/spdlog.h>
#include <tuple>

namespace minecpp::service::front {

using boost::asio::ip::tcp;
class Server;

using ConnectionId = mb::size;

class Connection {
   friend Server;

 public:
   using Ptr = std::shared_ptr<Connection>;

   explicit Connection(boost::asio::io_context &ctx, Server *server);
   ~Connection();

   void set_non_blocking();

   void async_write_then_read(const Ptr &conn, uint8_t *buff, size_t size,
                              Protocol::Handler &h);
   void async_write(const Ptr &conn, uint8_t *buff, size_t size);
   void async_write_then_disconnect(const Ptr &conn, uint8_t *buff,
                                    size_t size);

   void send(const Ptr &conn, minecpp::network::message::Writer &w);
   void send_and_read(const Ptr &conn, minecpp::network::message::Writer &w,
                      Protocol::Handler &h);
   void send_and_disconnect(const Ptr &conn, minecpp::network::message::Writer &w);

   Server *get_server();

   Protocol::State state();
   void set_state(Protocol::State s);
   void set_compression_threshold(std::size_t threshold);
   void set_service_id(boost::uuids::uuid id);
   boost::uuids::uuid service_id();

   void set_uuid(boost::uuids::uuid uuid);

   [[nodiscard]] const boost::uuids::uuid &uuid() const;
   [[nodiscard]] ConnectionId id() const;
   [[nodiscard]] mb::size compression_threshold() const;

   void push_chunk(int x, int z);
   minecpp::game::block::ChunkPos pop_chunk();
   bool has_chunks();

   [[nodiscard]] tcp::socket &socket();

   mb::u8 *alloc_byte();
   void free_byte(mb::u8 *byte);

 private:

   ConnectionId m_id = -1;
   tcp::socket m_socket;

   boost::uuids::uuid m_player_id{};
   boost::uuids::uuid m_engine_service_id{};

   Server *m_server;
   Protocol::State m_state;
   mb::size m_compression_threshold = 0;
   boost::object_pool<mb::u8> m_byte_pool;
   minecpp::util::StaticQueue<minecpp::game::block::ChunkPos, 200> m_chunk_queue{};
};

void async_read_varint(const Connection::Ptr &conn, mb::u32 result, mb::u32 shift, const std::function<void(mb::u32)>& callback);
void async_read_packet(const Connection::Ptr &conn, Protocol::Handler &handler);

template<typename M>
void send(const Connection::Ptr &conn, M msg) {
   auto w = msg.serialize();
   conn->send(conn, w);
}

template<typename M>
void send_and_read(const Connection::Ptr &conn, M msg, Protocol::Handler &h) {
   auto w = msg.serialize();
   conn->send_and_read(conn, w, h);
}

template<typename M>
void send_and_disconnect(const Connection::Ptr &conn, M msg) {
   auto w = msg.serialize();
   conn->send_and_disconnect(conn, w);
}

}// namespace minecpp::service::front
