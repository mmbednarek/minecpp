#include "ticks.h"
#include <grpcpp/client_context.h>
#include <minecpp/network/message/clientbound.h>
#include <minecpp/util/time.h>
#include <spdlog/spdlog.h>
#include <thread>
#include <utility>

namespace minecpp::service::front {

TickManager::TickManager(Server &server, const ChunkService &chunks) : server(server), chunk_service(chunks) {}

constexpr int keep_alive_interval = 8000;
constexpr int load_chunks_interval = 10;
constexpr int thread_limit = 5;

[[noreturn]] void TickManager::tick() {
   uint64_t last_keep_alive = 0;
   uint64_t last_load_chunks = 0;
   for (;;) {
      auto now = minecpp::util::now_milis();
      if (now - last_keep_alive >= keep_alive_interval) {
         keep_alive();
         last_keep_alive = minecpp::util::now_milis();
      }
      if (now - last_load_chunks >= load_chunks_interval) {
         load_chunks();
         last_load_chunks = minecpp::util::now_milis();
      }
   }
}

void TickManager::keep_alive() {
   server.for_each_connection([](const std::shared_ptr<Connection> &conn) {
      if (!conn)
         return;
      send(conn, minecpp::network::message::KeepAlive{
                         .time = minecpp::util::now_milis(),
                 });
   });
}

void TickManager::load_chunks() {
   while (m_future_chunks.size() > 4) {
      for (auto at = m_future_chunks.begin(); at != m_future_chunks.end();) {
         auto &future_ticket = *at;
         if (!future_ticket.valid()) {
            m_future_chunks.erase(at);
            at = m_future_chunks.begin();
            continue;
         }
         if (future_ticket.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto ticket = future_ticket.get();
            m_future_chunks.erase(at);
            at = m_future_chunks.begin();
            spdlog::info("sending chunk {} {}", ticket.chunk.pos_x(), ticket.chunk.pos_z());
            if (ticket.loaded) {
               send(ticket.conn, minecpp::network::message::ChunkData{
                       .chunk = ticket.chunk,
               });
               send(ticket.conn, minecpp::network::message::UpdateLight{
                       .chunk = ticket.chunk,
               });
            }
            continue;
         }
         ++at;
      }
   }

   server.for_each_connection([this](const std::shared_ptr<Connection> &conn) {
      if (!conn)
         return;
      if (!conn->has_chunks())
         return;

      auto chunk_pos = conn->pop_chunk();

      m_future_chunks.emplace_back(std::async(std::launch::async, [](std::shared_ptr<Connection> conn, ChunkService chunk_service, int x, int z) {
         grpc::ClientContext ctx;
         ChunkLoadTicket ticket{ .conn = std::move(conn) };
         minecpp::proto::service::chunk_storage::v1::LoadChunkRequest load_chunk_request;
         load_chunk_request.set_x(x);
         load_chunk_request.set_z(z);

         auto status = chunk_service->LoadChunk(&ctx, load_chunk_request, &ticket.chunk);
         if (!status.ok()) {
            spdlog::error("error loading chunk: {}", status.error_message());
            return ticket;
         }

         ticket.loaded = true;
         return ticket;
      }, conn, chunk_service, chunk_pos.x, chunk_pos.z));
   });
}

}// namespace minecpp::service::front
