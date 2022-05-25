#pragma once

#include "connection.h"
#include "protocol/handler.h"
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <functional>
#include <map>
#include <minecpp/player/id.h>
#include <string>
#include <vector>

namespace minecpp::service::front {

using boost::asio::ip::tcp;

class Server
{
   using ConnectionPtr       = std::shared_ptr<Connection>;
   using ConnectionIter      = std::vector<ConnectionPtr>::iterator;
   using ConstConnectionIter = std::vector<ConnectionPtr>::const_iterator;

 public:
   explicit Server(boost::asio::io_context &ctx, short port, Protocol::Handler *play,
                   Protocol::Handler *status, Protocol::Handler *login);

   void accept_conn();

   void handshake(const std::shared_ptr<Connection> &conn);

   void drop_connection(ConnectionId id);

   [[nodiscard]] inline ConnectionIter begin()
   {
      return m_connections.begin();
   }

   [[nodiscard]] inline ConnectionIter end()
   {
      return m_connections.end();
   }

   [[nodiscard]] inline ConstConnectionIter cbegin() const
   {
      return m_connections.cbegin();
   }

   [[nodiscard]] inline ConstConnectionIter cend() const
   {
      return m_connections.cend();
   }

   void for_each_connection(std::function<void(const std::shared_ptr<Connection> &)>);

   bool has_connection(player::Id player_id);

   std::shared_ptr<Connection> connection_by_id(player::Id player_id);

   Protocol::Handler &get_handler(Protocol::State state);

   void index_connection(boost::uuids::uuid index, std::size_t id);

 private:
   std::map<boost::uuids::uuid, std::size_t> conn_ids;
   std::vector<ConnectionPtr> m_connections;
   tcp::acceptor acceptor;
   Protocol::Handler *m_handlers[3];
};

}// namespace minecpp::service::front
