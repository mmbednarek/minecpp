#pragma once
#include "protocol/handler.h"
#include "protocol/protocol.h"
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/streambuf.hpp>
#include <memory>

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

   Protocol::State state();
   void set_state(Protocol::State s);

 private:
   inline size_t read_varint(uint32_t result, uint32_t shift);

   int id = -1;
   tcp::socket socket;
   Protocol::State _state;
   uint8_t leading_byte;
   boost::asio::streambuf *packet_buff;
   Server *server;
};

} // namespace Front
