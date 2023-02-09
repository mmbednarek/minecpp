#pragma once

#include "Connection.h"
#include "protocol/Handler.h"
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <functional>
#include <map>
#include <minecpp/game/player/Id.h>
#include <string>
#include <vector>

namespace minecpp::service::front {

using boost::asio::ip::tcp;

class Server
{
   using ConnectionPtr       = std::shared_ptr<Connection>;
   using ConnectionStorage   = std::map<ConnectionId, ConnectionPtr>;
   using ConnectionIter      = ConnectionStorage::iterator;
   using ConstConnectionIter = ConnectionStorage::const_iterator;

 public:
   explicit Server(boost::asio::io_context &ctx, mb::u16 port, Protocol::Handler *play,
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

   template<typename TCallback>
   void for_each_connection(TCallback &&f)
   {
      for (auto &[_, conn] : m_connections) {
         f(conn);
      }
   }

   bool has_connection(game::PlayerId player_id);

   std::shared_ptr<Connection> connection_by_player_id(game::PlayerId player_id);

   Protocol::Handler &get_handler(Protocol::State state);

   void index_connection(game::PlayerId index, ConnectionId id);

 private:
   std::map<game::PlayerId, ConnectionId> m_player_id_to_connection_id_map;
   std::map<ConnectionId, ConnectionPtr> m_connections;
   tcp::acceptor m_acceptor;
   Protocol::Handler *m_handlers[3];
   ConnectionId m_top_connection{};
};

}// namespace minecpp::service::front
