#pragma once
#include "connection.h"
#include "protocol/handler.h"
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>
#include <vector>
#include <functional>

namespace Front {

using boost::asio::ip::tcp;

class Server {
 public:
   explicit Server(boost::asio::io_context &ctx, short port,
                   Protocol::Handler *play, Protocol::Handler *status,
                   Protocol::Handler *login);
   ~Server();

   void accept_conn();
   void handshake(Connection *conn);
   void drop_connection(int id);
   void for_each_connection(std::function<void(Connection *)>);
   Protocol::Handler &get_handler(const Protocol::State state);

 private:
   std::vector<Connection *> connections;
   tcp::acceptor acceptor;
   Protocol::Handler *handlers[3];
};

} // namespace Front
