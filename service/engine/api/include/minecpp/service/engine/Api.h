#pragma once

#include "minecpp/event/Clientbound.h"
#include "minecpp/network/Network.h"
#include "minecpp/stream/Client.h"
#include "minecpp/util/StaticQueue.h"

#include <fmt/core.h>
#include <mb/result.h>
#include <string_view>
#include <utility>

namespace minecpp::service::engine {

class IVisitor
{
 public:
   virtual ~IVisitor() noexcept = default;

   virtual void visit_event(const proto::event::clientbound::v1::Event &event) = 0;
};

class ClientStream
{
 public:
   ClientStream(stream::Client &client, const network::Endpoint &address);

   void send(const google::protobuf::Message &message, game::PlayerId id);
   [[nodiscard]] bool is_connected() const;

 private:
   std::shared_ptr<stream::Peer> m_peer;
};

class Client
{
 public:
   Client(IVisitor &visitor);

   Client(const Client &)                = delete;
   Client &operator=(const Client &)     = delete;
   Client(Client &&) noexcept            = delete;
   Client &operator=(Client &&) noexcept = delete;

   void connect(const network::Endpoint &address);
   bool send(const google::protobuf::Message &message, game::PlayerId id);
   void tick();

 private:
   void on_connected(std::shared_ptr<stream::Peer> peer);
   void on_received_message(std::shared_ptr<stream::Peer> peer, minecpp::container::BufferView message);
   void on_disconnected(std::shared_ptr<stream::Peer> peer, bool *try_reconnect);

   stream::Client m_client;
   std::vector<ClientStream> m_streams;
   std::size_t m_round{0};
   IVisitor &m_visitor;
};

}// namespace minecpp::service::engine