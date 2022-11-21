#pragma once
#include <condition_variable>
#include <fmt/core.h>
#include <grpc++/grpc++.h>
#include <mb/result.h>
#include <minecpp/event/Clientbound.h>
#include <minecpp/grpc/client/Bidi.h>
#include <minecpp/proto/service/engine/v1/Engine.grpc.pb.h>
#include <minecpp/util/StaticQueue.h>
#include <spdlog/spdlog.h>
#include <string_view>
#include <thread>
#include <utility>

namespace minecpp::service::engine {

using ConnectionManager = grpc::client::ConnectionManager<proto::service::engine::v1::EngineService::Stub,
                                                          proto::event::serverbound::v1::Event,
                                                          proto::event::clientbound::v1::Event>;

using ClientBidiStream = grpc::client::Stream<ConnectionManager>;

class IStream
{
 public:
   virtual ~IStream() noexcept = default;

   virtual void send(const ::google::protobuf::Message &message, game::PlayerId id) = 0;
};

template<typename TVisitor>
class Stream : public IStream
{
 public:
   explicit Stream(ClientBidiStream stream, TVisitor &visitor) :
       m_stream{std::move(stream)},
       m_visitor{visitor}
   {
      m_stream.bind_read_callback(this, &Stream::on_read);
   }

   void send(const google::protobuf::Message &message, game::PlayerId id) override
   {
      proto::event::serverbound::v1::Event proto_event;
      proto_event.mutable_payload()->PackFrom(message);
      *proto_event.mutable_player_id() = game::player::write_id_to_proto(id);
      m_stream.write(proto_event);
   }

   void on_read(const proto::event::clientbound::v1::Event &info)
   {
      event::visit_clientbound(info, m_visitor);
   }

 private:
   ClientBidiStream m_stream;
   TVisitor &m_visitor;
};

template<typename TVisitor>
requires event::ClientboundVisitor<TVisitor>

class Client : public IStream
{
 public:
   explicit Client(const std::vector<std::string> &addresses, TVisitor &visitor) :
       m_visitor{visitor},
       m_connection_manager(std::make_unique<ConnectionManager>(
               &proto::service::engine::v1::EngineService::Stub::AsyncJoin, addresses, this,
               &Client::on_connected, 8))
   {
   }

   Client(const Client &)                = delete;
   Client &operator=(const Client &)     = delete;
   Client(Client &&) noexcept            = delete;
   Client &operator=(Client &&) noexcept = delete;

   void on_connected(ClientBidiStream stream)
   {
      {
         std::lock_guard lock{m_mutex};
         m_streams.emplace_back(std::move(stream), m_visitor);
      }
      m_condition.notify_one();
   };

   void send(const ::google::protobuf::Message &message, game::PlayerId id) override
   {
      std::unique_lock lock{m_mutex};
      m_condition.wait(lock, [this] { return not m_streams.empty(); });

      m_streams[m_round].send(message, id);
      m_round = (m_round + 1) % m_streams.size();
   }

 private:
   std::vector<Stream<TVisitor>> m_streams;
   std::mutex m_mutex;
   std::condition_variable m_condition;
   std::size_t m_round{0};
   TVisitor &m_visitor;
   std::unique_ptr<ConnectionManager> m_connection_manager;
};

}// namespace minecpp::service::engine