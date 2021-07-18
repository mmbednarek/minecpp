#pragma once
#include <grpc++/grpc++.h>
#include <mb/result.h>
#include <minecpp/event/clientbound.h>
#include <minecpp/proto/service/engine/v1/engine.grpc.pb.h>
#include <string_view>
#include <thread>

namespace minecpp::service::engine {

using GrpcStream = grpc::ClientReaderWriter<proto::event::serverbound::v1::Event, proto::event::clientbound::v1::Event>;

template<typename T>
requires event::ClientboundVisitor<T>
class Stream {
   T &m_visitor;
   std::unique_ptr<GrpcStream> m_stream;
   bool m_running = true;
   std::thread m_thread;

 public:
   Stream(T &visitor, std::unique_ptr<GrpcStream> stream) : m_visitor(visitor),
                                                            m_stream(std::move(stream)),
                                                            m_thread(
                                                                    [](Stream *stream) {
                                                                       stream->thread_routine();
                                                                    },
                                                                    this) {}

   void thread_routine() const {
      while (m_running) {
         proto::event::clientbound::v1::Event cb_event;
         m_stream->Read(&cb_event);
         event::visit_clientbound(cb_event, m_visitor);
      }
   }

   void send(const proto::event::serverbound::v1::Event &event) const {
      m_stream->Write(event);
   }
};

class Client {
   std::shared_ptr<grpc::ChannelInterface> m_channel;
   std::unique_ptr<proto::service::engine::v1::EngineService::Stub> m_stub;

   Client(std::shared_ptr<grpc::ChannelInterface> channel, std::unique_ptr<proto::service::engine::v1::EngineService::Stub> stub);

 public:
   static mb::result<Client> create(std::string_view address);

   template<typename T>
   std::unique_ptr<Stream<T>> join(T &visitor) {
      grpc::ClientContext ctx;
      auto stream = m_stub->Join(&ctx);
      return std::make_unique<Stream<T>>(visitor, stream);
   }
};

}// namespace minecpp::service::engine