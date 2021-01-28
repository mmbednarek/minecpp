#pragma once
#include "protocol/handler.h"
#include "protocol/protocol.h"
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/uuid/uuid.hpp>
#include <memory>
#include <minecpp/minenet/msg/io.h>
#include <minecpp/minenet/msg/message.h>
#include <queue>
#include <spdlog/spdlog.h>
#include <tuple>

namespace Front {

using boost::asio::ip::tcp;
class Server;

class Connection {
   friend Server;

 public:
   using Ptr = std::shared_ptr<Connection>;

   explicit Connection(boost::asio::io_context &ctx, Server *server);
   ~Connection();

   void set_non_blocking();

   size_t read_packet_size();
   size_t read_packet_size(uint8_t leading);
   size_t read(void *ptr, size_t size);
   size_t read(boost::asio::streambuf &buff);
   void async_write_then_read(const Ptr &conn, uint8_t *buff, size_t size,
                              Protocol::Handler &h);
   void async_write(const Ptr &conn, uint8_t *buff, size_t size);
   void async_write_then_disconnect(const Ptr &conn, uint8_t *buff,
                                    size_t size);
   void async_read_packet(const Ptr &conn, Protocol::Handler &h);
   void async_read_packet_data(const Ptr &conn, Protocol::Handler &h);

   void send(const Ptr &conn, MineNet::Message::Writer &w);
   void send_and_read(const Ptr &conn, MineNet::Message::Writer &w,
                      Protocol::Handler &h);
   void send_and_disconnect(const Ptr &conn, MineNet::Message::Writer &w);

   Server *get_server();

   Protocol::State state();
   void set_state(Protocol::State s);
   void set_compression_threshold(std::size_t threshold);
   void set_service_id(boost::uuids::uuid id);
   boost::uuids::uuid service_id();

   void set_uuid(boost::uuids::uuid uuid);
   [[nodiscard]] const boost::uuids::uuid &get_uuid() const;

   void push_chunk(int x, int z);
   std::tuple<int, int> pop_chunk();
   bool has_chunks();

 private:
   inline size_t read_varint(uint32_t result, uint32_t shift);
   std::queue<std::tuple<int, int>> chunk_queue;

   boost::uuids::uuid player_id{};
   boost::uuids::uuid engine_service_id{};
   int id = -1;
   std::size_t compression_threshold = 0;
   tcp::socket socket;
   Protocol::State _state;
   uint8_t leading_byte;
   boost::asio::streambuf *packet_buff;
   Server *server;
};

template <typename M> void send(const Connection::Ptr &conn, M msg) {
   auto w = MineNet::Message::serialize(msg);
   conn->send(conn, w);
}

template <typename M>
void send_and_read(const Connection::Ptr &conn, M msg, Protocol::Handler &h) {
   auto w = MineNet::Message::serialize(msg);
   conn->send_and_read(conn, w, h);
}

template <typename M>
void send_and_disconnect(const Connection::Ptr &conn, M msg) {
   auto w = MineNet::Message::serialize(msg);
   conn->send_and_disconnect(conn, w);
}

} // namespace Front
