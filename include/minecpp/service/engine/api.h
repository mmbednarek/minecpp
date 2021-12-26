#pragma once
#include <fmt/core.h>
#include <grpc++/grpc++.h>
#include <mb/result.h>
#include <minecpp/event/clientbound.h>
#include <minecpp/grpc/client/bidi.h>
#include <minecpp/proto/service/engine/v1/engine.grpc.pb.h>
#include <spdlog/spdlog.h>
#include <string_view>
#include <thread>

namespace minecpp::service::engine {

using BidiStream =
        grpc::client::Stream<proto::event::serverbound::v1::Event, proto::event::clientbound::v1::Event>;

class Stream {
   BidiStream &m_stream;
 public:
   explicit Stream(BidiStream &stream) : m_stream(stream) {}

   template<typename TEvent>
   void send(const TEvent &event, player::Id player_id) const {
      proto::event::serverbound::v1::Event proto_event;
      proto_event.mutable_payload()->PackFrom(event);
      *proto_event.mutable_player_id() = player::write_id_to_proto(player_id);
      m_stream.write(proto_event);
   }
};

template<typename TVisitor>
requires event::ClientboundVisitor<TVisitor>
class EventHandler {
   TVisitor &m_visitor;
   std::unique_ptr<BidiStream> m_stream;

 public:
   explicit EventHandler(TVisitor &visitor) : m_visitor(visitor) {}

   void on_connected(BidiStream stream) {
      m_stream = std::make_unique<BidiStream>(stream);
   };

   void on_finish_write(BidiStream) {}

   void on_finish_read(BidiStream, const proto::event::clientbound::v1::Event &info) {
      event::visit_clientbound(info, m_visitor);
   }

   void on_disconnect(BidiStream stream) {}

   Stream stream() {
      while(m_stream == nullptr)
         ;
      return Stream(*m_stream);
   }
};

template<typename TVisitor>
using BidiConnection =
        grpc::client::Connection<proto::service::engine::v1::EngineService::Stub, proto::event::serverbound::v1::Event, proto::event::clientbound::v1::Event, EventHandler<TVisitor>, &proto::service::engine::v1::EngineService::Stub::AsyncJoin>;

template<typename TVisitor>
class Client {
   BidiConnection<TVisitor> m_connection;
   EventHandler<TVisitor> m_handler;

 public:
   explicit Client(const std::string &address, TVisitor &visitor) : m_connection(address, m_handler, 1), m_handler(visitor) {}

   [[nodiscard]] Stream join() {
      return m_handler.stream();
   }
};

}// namespace minecpp::service::engine