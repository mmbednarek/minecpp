#pragma once
#include "event_manager.h"
#include <minecpp/grpc/server/bidi.h>
#include <minecpp/proto/event/clientbound/v1/clientbound.pb.h>
#include <minecpp/proto/event/serverbound/v1/serverbound.pb.h>
#include <minecpp/proto/service/engine/v1/engine.grpc.pb.h>
#include <string>

namespace minecpp::service::engine {

class EventHandler;

using BidiStream = grpc::server::Stream<proto::event::clientbound::v1::Event,
                                        proto::event::serverbound::v1::Event, std::string>;

class ApiHandler
{
   EventHandler &m_event_handler;
   EventManager<BidiStream> &m_event_manager;

 public:
   ApiHandler(EventHandler &event_handler, EventManager<BidiStream> &event_manager);

   void on_connected(BidiStream stream);

   void on_finish_write(BidiStream stream);

   void on_finish_read(BidiStream, const proto::event::serverbound::v1::Event &event);

   inline void on_disconnect(BidiStream stream) {}
};

}// namespace minecpp::service::engine