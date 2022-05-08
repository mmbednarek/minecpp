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

constexpr std::size_t g_steam_queue_size = 1024;

class Stream {
   ClientBidiStream &m_stream;
   std::mutex &m_mtx;
   util::StaticQueue<OutEvent, g_steam_queue_size> &m_out_queue;

 public:
   Stream(ClientBidiStream &stream, std::mutex &mtx, util::StaticQueue<OutEvent, g_steam_queue_size> &out_queue) : m_stream(stream), m_mtx(mtx), m_out_queue(out_queue) {}

   template<typename TEvent>
   void send(const TEvent &event, player::Id player_id) const {
      proto::event::serverbound::v1::Event proto_event;
      proto_event.mutable_payload()->PackFrom(event);
      *proto_event.mutable_player_id() = player::write_id_to_proto(player_id);
      if (m_mtx.try_lock()) {
         // good we're free to write
         m_stream.write(proto_event);
         return;
      }
      // we're currently writing, just push it onto the queue
      m_out_queue.push(std::move(proto_event));
   }
};

template<typename TVisitor>
requires event::ClientboundVisitor<TVisitor>
class ClientEventHandler {
   TVisitor &m_visitor;
   std::unique_ptr<ClientBidiStream> m_stream;
   util::StaticQueue<OutEvent, g_steam_queue_size> m_out_queue;
   std::mutex m_mtx;

 public:
   explicit ClientEventHandler(TVisitor &visitor) : m_visitor(visitor) {}

   void on_connected(ClientBidiStream stream) {
      stream.read();
      m_stream = std::make_unique<ClientBidiStream>(stream);
   };

   void on_finish_write(ClientBidiStream stream) {
      if (m_out_queue.empty()) {
         // queue is empty, we can unlock the mutex, so next
         // thread can write directly
         m_mtx.unlock();
         return;
      }
      // queue is not empty write another message
      stream.write(m_out_queue.pop());
   }

   void on_finish_read(ClientBidiStream stream, const proto::event::clientbound::v1::Event &info) {
      stream.read();// read next message
      event::visit_clientbound(info, m_visitor);
   }

   void on_disconnect(ClientBidiStream stream) {}

   Stream stream() {
      while (m_stream == nullptr) {
         using namespace std::chrono_literals;
         spdlog::info("awaiting connection to engine...");
         std::this_thread::sleep_for(1s);
      }
      return {*m_stream, m_mtx, m_out_queue};
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
   explicit Client(const std::string &address, TVisitor &visitor) : m_connection(address, m_handler, 4), m_handler(visitor) {}

   [[nodiscard]] Stream join() {
      return m_handler.stream();
   }
};

}// namespace minecpp::service::engine