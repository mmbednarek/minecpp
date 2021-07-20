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
class Receiver {
   T &m_visitor;
   bool m_running = true;
   std::thread m_thread;
   GrpcStream &m_stream;

 public:
   Receiver(T &visitor, GrpcStream &stream) : m_visitor(visitor),
                                              m_stream(stream),
                                              m_thread(
                                                      [](Receiver *receiver) {
                                                         receiver->thread_routine();
                                                      },
                                                      this) {}

   void thread_routine() const {
      while (m_running) {
         proto::event::clientbound::v1::Event cb_event;
         m_stream.Read(&cb_event);
         event::visit_clientbound(cb_event, m_visitor);
      }
   }
};

class Stream {
   std::unique_ptr<GrpcStream> m_stream;

 public:
   explicit Stream(std::unique_ptr<GrpcStream> stream) : m_stream(std::move(stream)) {}

   void send(const proto::event::serverbound::v1::Event &event) const {
      m_stream->Write(event);
   }

   template<typename T>
   std::unique_ptr<Receiver<T>> make_receiver(T &visitor) {
      return std::make_unique<Receiver<T>>(visitor, m_stream);
   }
};

class Client {
   std::shared_ptr<grpc::ChannelInterface> m_channel;
   std::unique_ptr<proto::service::engine::v1::EngineService::Stub> m_stub;

   Client(std::shared_ptr<grpc::ChannelInterface> channel, std::unique_ptr<proto::service::engine::v1::EngineService::Stub> stub);

 public:
   static mb::result<Client> create(std::string_view address);

   Stream join() {
      grpc::ClientContext ctx;
      return Stream(m_stub->Join(&ctx));
   }
};

}// namespace minecpp::service::engine