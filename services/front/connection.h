#pragma once
#include "protocol/handler.h"
#include "protocol/protocol.h"
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/uuid/uuid.hpp>
#include <memory>
#include <minenet/msg/io.h>
#include <minenet/msg/message.h>

namespace Front {

using boost::asio::ip::tcp;
class Server;

class Connection {
   friend Server;

 public:
   explicit Connection(boost::asio::io_context &ctx, Server *server);
   ~Connection();

   size_t read_packet_size();
   size_t read_packet_size(uint8_t leading);
   size_t read(void *ptr, size_t size);
   size_t read(boost::asio::streambuf &buff);
   void async_write_then_read(uint8_t *buff, size_t size, Protocol::Handler &h);
   void async_write(uint8_t *buff, size_t size);
   void async_write_then_disconnect(uint8_t *buff, size_t size);
   void async_read_packet(Protocol::Handler &h);
   void async_read_packet_data(Protocol::Handler &h);

   void send(MineNet::Message::Writer &w);
   void send_and_read(MineNet::Message::Writer &w, Protocol::Handler &h);
   void send_and_disconnect(MineNet::Message::Writer &w);

   Server *get_server();

   template <typename M> void send(M msg) {
      auto w = MineNet::Message::serialize(msg);
      send(w);
   }

   template <typename M> void send_and_read(M msg, Protocol::Handler &h) {
      auto w = MineNet::Message::serialize(msg);
      send_and_read(w, h);
   }

   template <typename M> void send_and_disconnect(M msg) {
      auto w = MineNet::Message::serialize(msg);
      send_and_disconnect(w);
   }

   Protocol::State state();
   void set_state(Protocol::State s);
   void set_compression_threshold(std::size_t threshold);

   void set_uuid(boost::uuids::uuid uuid);
   const boost::uuids::uuid &get_uuid() const;


 private:
   inline size_t read_varint(uint32_t result, uint32_t shift);

   boost::uuids::uuid player_id{};
   int id = -1;
   std::size_t compression_threshold = 0;
   tcp::socket socket;
   Protocol::State _state;
   uint8_t leading_byte;
   boost::asio::streambuf *packet_buff;
   Server *server;
};

} // namespace Front
