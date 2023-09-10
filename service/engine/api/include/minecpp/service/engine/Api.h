#pragma once

#include "minecpp/net/engine/Clientbound.schema.h"
#include "minecpp/net/engine/Serverbound.schema.h"
#include "minecpp/network/Network.h"
#include "minecpp/stream/Client.h"
#include "minecpp/util/StaticQueue.h"

#include <fmt/core.h>
#include <mb/result.h>
#include <string_view>
#include <utility>

namespace minecpp::service::engine {

class ClientStream
{
 public:
   ClientStream(stream::Client &client, const network::Endpoint &address);

   void send(container::BufferView message);
   [[nodiscard]] bool is_connected() const;

 private:
   std::shared_ptr<stream::Peer> m_peer;
};

class Client;

class IVisitor
{
 public:
   virtual ~IVisitor() noexcept = default;

   virtual void on_send_msg_to_single_player(Client &client,
                                             const net::engine::cb::SendMsgToSinglePlayer &msg)          = 0;
   virtual void on_send_msg_to_some_players(Client &client,
                                            const net::engine::cb::SendMsgToSomePlayers &msg)            = 0;
   virtual void on_send_msg_to_all_players(Client &client,
                                           const net::engine::cb::SendMsgToAllPlayers &msg)              = 0;
   virtual void on_send_msg_to_all_players_except(Client &client,
                                                  const net::engine::cb::SendMsgToAllPlayersExcept &msg) = 0;
   virtual void on_failure(Client &client, std::uint8_t message_id)                                      = 0;
};

class Client
{
 public:
   explicit Client(IVisitor &visitor);

   Client(const Client &)                = delete;
   Client &operator=(const Client &)     = delete;
   Client(Client &&) noexcept            = delete;
   Client &operator=(Client &&) noexcept = delete;

   void connect(const network::Endpoint &address);
   bool send(container::BufferView message);
   void tick();

 private:
   void on_connected(stream::Peer *peer);
   void on_received_message(stream::Peer *peer, minecpp::container::BufferView message);
   void on_disconnected(stream::Peer *peer, bool *try_reconnect);

   stream::Client m_client;
   std::vector<ClientStream> m_streams;
   std::size_t m_round{0};
   IVisitor &m_visitor;
};

}// namespace minecpp::service::engine