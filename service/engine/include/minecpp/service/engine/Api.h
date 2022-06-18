#pragma once
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

using ClientBidiStream =
        grpc::client::Stream<proto::event::serverbound::v1::Event, proto::event::clientbound::v1::Event>;

using StreamWeakPtr = std::weak_ptr<ClientBidiStream>;

using OutEvent = proto::event::serverbound::v1::Event;

constexpr std::size_t g_steam_queue_size = 4 * 1024;

class Stream
{
   StreamWeakPtr m_stream;
   std::mutex m_mtx;
   util::StaticQueue<OutEvent, g_steam_queue_size> m_out_queue;

 public:
   template<typename TEvent>
   void send(const TEvent &event, game::PlayerId player_id)
   {
      proto::event::serverbound::v1::Event proto_event;
      proto_event.mutable_payload()->PackFrom(event);
      *proto_event.mutable_player_id() = game::player::write_id_to_proto(player_id);
      if (m_mtx.try_lock()) {
         auto stream = m_stream.lock();
         if (!stream) {
            // client is not connected yet, or has disconnected, write to the queue
            m_out_queue.push(std::move(proto_event));
            return;
         }

         // good we're free to write
         stream->write(proto_event);
         return;
      }
      // we're currently writing, just push it onto the queue
      m_out_queue.push(std::move(proto_event));
   }

   void set_stream_reference(StreamWeakPtr ptr)
   {
      m_stream = std::move(ptr);
   }

   void on_finish_write(const StreamWeakPtr &weak_stream)
   {
      if (m_out_queue.empty()) {
         // queue is empty, we can unlock the mutex, so next
         // thread can write directly
         m_mtx.unlock();
         return;
      }
      // queue is not empty write another message
      if (auto locked_stream = weak_stream.lock(); locked_stream) {
         locked_stream->write(m_out_queue.pop());
      }
   }

   [[nodiscard]] constexpr util::StaticQueue<OutEvent, g_steam_queue_size> &out_queue()
   {
      return m_out_queue;
   }
};

template<typename TVisitor>
requires event::ClientboundVisitor<TVisitor>

class ClientEventHandler
{
   TVisitor &m_visitor;
   Stream m_stream;

 public:
   explicit ClientEventHandler(TVisitor &visitor) :
       m_visitor(visitor)
   {
   }

   void on_connected(const StreamWeakPtr &stream)
   {
      try {
         spdlog::info("calling on connected");
         if (auto locked_stream = stream.lock(); locked_stream) {
            locked_stream->read();
            m_stream.set_stream_reference(stream);
         }
      } catch (std::runtime_error &err) {
         spdlog::info("runtime error while receiving connection:  {}", err.what());
      }
   };

   void on_finish_write(const StreamWeakPtr &stream)
   {
      m_stream.on_finish_write(stream);
   }

   void on_finish_read(const StreamWeakPtr &stream, const proto::event::clientbound::v1::Event &info)
   {
      if (auto locked_stream = stream.lock(); locked_stream) {
         locked_stream->read();
      }
      event::visit_clientbound(info, m_visitor);
   }

   void on_disconnect(const StreamWeakPtr &stream) {}

   Stream *stream()
   {
      return &m_stream;
   }
};

template<typename TVisitor>
using BidiConnection =
        grpc::client::Connection<proto::service::engine::v1::EngineService::Stub,
                                 proto::event::serverbound::v1::Event, proto::event::clientbound::v1::Event,
                                 ClientEventHandler<TVisitor>>;

template<typename TVisitor>
class Client
{
   BidiConnection<TVisitor> m_connection;
   ClientEventHandler<TVisitor> m_handler;

 public:
   explicit Client(const std::string &address, TVisitor &visitor) :
       m_connection(&proto::service::engine::v1::EngineService::Stub::AsyncJoin, address, m_handler, 8),
       m_handler(visitor)
   {
   }

   [[nodiscard]] Stream *join()
   {
      return m_handler.stream();
   }
};

}// namespace minecpp::service::engine