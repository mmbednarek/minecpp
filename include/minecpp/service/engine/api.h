#pragma once
#include <fmt/core.h>
#include <grpc++/grpc++.h>
#include <mb/result.h>
#include <minecpp/event/clientbound.h>
#include <minecpp/proto/service/engine/v1/engine.grpc.pb.h>
#include <spdlog/spdlog.h>
#include <string_view>
#include <thread>

namespace minecpp::service::engine {

using GrpcStream = grpc::ClientAsyncReaderWriter<proto::event::serverbound::v1::Event, proto::event::clientbound::v1::Event>;

enum class NotifyType {
   Read = 1,
   Write = 2,
   Join = 3,
};

inline NotifyType read_notify_type(void *tag) {
   return static_cast<NotifyType>(reinterpret_cast<mb::u64>(tag));
}

inline void *write_notify_type(NotifyType t) {
   return reinterpret_cast<void *>(t);
}

template<typename T>
requires event::ClientboundVisitor<T>
class Receiver {
   T &m_visitor;
   GrpcStream &m_stream;
   bool m_running = true;
   grpc::CompletionQueue &m_cq;
   std::thread m_thread;

 public:
   Receiver(T &visitor, GrpcStream &stream, grpc::CompletionQueue &cq) : m_visitor(visitor),
                                                                         m_stream(stream),
                                                                         m_cq(cq),
                                                                         m_thread(
                                                                                 [](Receiver *receiver) {
                                                                                    receiver->thread_routine();
                                                                                 },
                                                                                 this) {}

   void read_message() const {
      proto::event::clientbound::v1::Event cb_event;
      m_stream.Read(&cb_event, write_notify_type(NotifyType::Read));
      spdlog::info("received event {}", cb_event.payload().type_url());
      event::visit_clientbound(cb_event, m_visitor);
   }
};

class Stream {
   std::unique_ptr<GrpcStream> m_stream;
   std::unique_ptr<grpc::ClientContext> m_ctx;
   std::unique_ptr<grpc::CompletionQueue> m_cq;
   std::thread m_thread;
   std::atomic<bool> m_ready = false;
   bool m_running = true;

 public:
   explicit Stream(std::unique_ptr<GrpcStream> stream, std::unique_ptr<grpc::ClientContext> ctx, std::unique_ptr<grpc::CompletionQueue> cq) : m_stream(std::move(stream)),
                                                                                                                                              m_ctx(std::move(ctx)),
                                                                                                                                              m_cq(std::move(cq)),
                                                                                                                                              m_thread(
                                                                                                                                                      [](Stream *receiver) {
                                                                                                                                                         receiver->routine();
                                                                                                                                                      },
                                                                                                                                                      this) {}

   inline void send_event(const proto::event::serverbound::v1::Event &event) const {
      while (!m_ready.load())
         ;
      m_stream->Write(event, write_notify_type(NotifyType::Write));
   }

   void routine() {
      while (m_running) {
         void *tag;
         auto ok = false;
         if (!m_cq->Next(&tag, &ok))
            continue;
         if (!ok)
            continue;

         auto notify_type = read_notify_type(tag);

         switch (notify_type) {
         case NotifyType::Read:
            spdlog::info("message has been read");
            break;
         case NotifyType::Write:
            spdlog::info("message has been written");
            break;
         case NotifyType::Join:
            spdlog::info("player has join");
            m_ready = true;
            break;
         }
      }
   }

   template<typename T>
   void send(const T &event, player::Id player_id) const {
      proto::event::serverbound::v1::Event proto_event;
      proto_event.mutable_payload()->PackFrom(event);
      *proto_event.mutable_player_id() = player::write_id_to_proto(player_id);
      send_event(proto_event);
   }

   template<typename T>
   std::unique_ptr<Receiver<T>> make_receiver(T &visitor) {
      return std::make_unique<Receiver<T>>(visitor, *m_stream, *m_cq);
   }
};

class Client {
   std::shared_ptr<grpc::ChannelInterface> m_channel;
   std::unique_ptr<proto::service::engine::v1::EngineService::Stub> m_stub;

   Client(std::shared_ptr<grpc::ChannelInterface> channel, std::unique_ptr<proto::service::engine::v1::EngineService::Stub> stub);

 public:
   [[nodiscard]] static mb::result<Client> create(std::string_view address);

   inline mb::result<Stream> join() {
      auto ctx = std::make_unique<grpc::ClientContext>();
      auto cq = std::make_unique<grpc::CompletionQueue>();
      auto stream = m_stub->AsyncJoin(ctx.get(), cq.get(), write_notify_type(NotifyType::Join));
      if (!stream) {
         return mb::error("could not join stream");
      }
      return Stream(std::move(stream), std::move(ctx), std::move(cq));
   }
};

}// namespace minecpp::service::engine