#pragma once
#include "IConnection.h"
#include <minecpp/game/Game.h>
#include <minecpp/grpc/server/Bidi.h>
#include <minecpp/proto/event/clientbound/v1/Clientbound.pb.h>
#include <minecpp/proto/event/serverbound/v1/Serverbound.pb.h>
#include <minecpp/proto/service/engine/v1/Engine.grpc.pb.h>
#include <string>

namespace minecpp::service::engine {

class EventHandler;
class EventManager;

MINECPP_DECLARE_BIDI_SERVER(EngineServer, minecpp::proto::service::engine::v1::EngineService::AsyncService,
                            Join, minecpp::proto::event::clientbound::v1::Event,
                            minecpp::proto::event::serverbound::v1::Event)

using BidiStream = grpc::server::Stream<EngineServer>;

class Connection : public IConnection
{
 public:
   explicit Connection(EventHandler &event_handler, BidiStream stream);

   void on_read(const proto::event::serverbound::v1::Event &event);

   void send_to_player(const google::protobuf::Message &message, game::PlayerId player_id) override;
   void send_to_all(const google::protobuf::Message &message) override;

 private:
   EventHandler &m_event_handler;
   BidiStream m_stream;
};

class ApiHandler
{
 public:
   ApiHandler(EventHandler &event_handler, EventManager &event_manager, const std::string &address);

   void on_connected(BidiStream stream);
   mb::emptyres wait();

 private:
   EventHandler &m_event_handler;
   EventManager &m_event_manager;
   EngineServer m_server;
};

}// namespace minecpp::service::engine