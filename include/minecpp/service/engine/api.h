#pragma once
#include <fmt/core.h>
#include <grpc++/grpc++.h>
#include <mb/result.h>
#include <minecpp/event/clientbound.h>
#include <minecpp/grpc/client/bidi.h>
#include <minecpp/proto/service/engine/v1/engine.grpc.pb.h>
#include <minecpp/util/static_queue.h>
#include <spdlog/spdlog.h>
#include <string_view>
#include <thread>

namespace minecpp::service::engine {

using ClientBidiStream =
        grpc::client::Stream<proto::event::serverbound::v1::Event, proto::event::clientbound::v1::Event>;

using OutEvent = proto::event::serverbound::v1::Event;

class Stream {
   ClientBidiStream &m_stream;
   std::atomic<bool> &m_writing;
   util::StaticQueue<OutEvent, 256> &m_out_queue;

 public:
   Stream(ClientBidiStream &stream, std::atomic<bool> &writing, util::StaticQueue<OutEvent, 256> &out_queue) : m_stream(stream), m_writing(writing), m_out_queue(out_queue) {}

   template<typename TEvent>
   void send(const TEvent &event, player::Id player_id) const {
      proto::event::serverbound::v1::Event proto_event;
      proto_event.mutable_payload()->PackFrom(event);
      *proto_event.mutable_player_id() = player::write_id_to_proto(player_id);
      if (!m_writing) {
         m_writing = true;
         m_stream.write(proto_event);
         return;
      }
      m_out_queue.push(std::move(proto_event));
   }
};

template<typename TVisitor>
requires event::ClientboundVisitor<TVisitor>
class ClientEventHandler {
   TVisitor &m_visitor;
   std::unique_ptr<ClientBidiStream> m_stream;
   util::StaticQueue<OutEvent, 256> m_out_queue;
   std::atomic<bool> m_writing = false;

 public:
   explicit ClientEventHandler(TVisitor &visitor) : m_visitor(visitor) {}

   void on_connected(ClientBidiStream stream) {
      stream.read();
      m_stream = std::make_unique<ClientBidiStream>(stream);
   };

   void on_finish_write(ClientBidiStream stream) {
      if (!m_out_queue.empty()) {
         m_writing = true;
         auto event = m_out_queue.pop();
         stream.write(event);
         return;
      }
      m_writing = false;
   }

   void on_finish_read(ClientBidiStream stream, const proto::event::clientbound::v1::Event &info) {
      stream.read();// read next message
      event::visit_clientbound(info, m_visitor);
   }

   void on_disconnect(ClientBidiStream stream) {}

   Stream stream() {
      while (m_stream == nullptr)
         ;
      return {*m_stream, m_writing, m_out_queue};
   }
};

template<typename TVisitor>
using BidiConnection =
        grpc::client::Connection<proto::service::engine::v1::EngineService::Stub, proto::event::serverbound::v1::Event, proto::event::clientbound::v1::Event, ClientEventHandler<TVisitor>, &proto::service::engine::v1::EngineService::Stub::AsyncJoin>;

template<typename TVisitor>
class Client {
   BidiConnection<TVisitor> m_connection;
   ClientEventHandler<TVisitor> m_handler;

 public:
   explicit Client(const std::string &address, TVisitor &visitor) : m_connection(address, m_handler, 1), m_handler(visitor) {}

   [[nodiscard]] Stream join() {
      return m_handler.stream();
   }
};

}// namespace minecpp::service::engine