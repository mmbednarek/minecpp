#pragma once

#include "IConnection.h"
#include "JobSystem.h"

#include "minecpp/proto/event/clientbound/Clientbound.pb.h"
#include "minecpp/proto/event/serverbound/Serverbound.pb.h"
#include "minecpp/stream/Server.h"

#include <string>

namespace minecpp::service::engine {

class EventHandler;
class Service;
class EventManager;
class ApiHandler;

class Connection : public IConnection
{
 public:
   explicit Connection(std::shared_ptr<stream::Peer> peer);

   void send_to_many(const google::protobuf::Message &message, std::span<game::PlayerId> player_ids) override;
   void send_to_player(const google::protobuf::Message &message, game::PlayerId player_id) override;
   void send_to_all(const google::protobuf::Message &message) override;
   void send_to_all_excluding(const google::protobuf::Message &message, game::PlayerId player_id) override;

 private:
   void send(const proto::event::clientbound::Event &event);

   std::shared_ptr<stream::Peer> m_peer;
};

class ApiHandler
{
 public:
   ApiHandler(Service &service, EventManager &event_manager, JobSystem &job_system, std::uint16_t port);

   ApiHandler(const ApiHandler &)                = delete;
   ApiHandler &operator=(const ApiHandler &)     = delete;
   ApiHandler(ApiHandler &&) noexcept            = delete;
   ApiHandler &operator=(ApiHandler &&) noexcept = delete;

   void tick();

 private:
   void on_connected(std::shared_ptr<stream::Peer> peer);
   void on_received_message(std::shared_ptr<stream::Peer> peer, container::BufferView message);
   void on_disconnected(std::shared_ptr<stream::Peer> peer, bool *try_reconnect);

   Service &m_service;
   EventManager &m_event_manager;
   stream::Server m_server;
   JobSystem &m_job_system;
};

}// namespace minecpp::service::engine