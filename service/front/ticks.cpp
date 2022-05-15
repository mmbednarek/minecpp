#include "ticks.h"
#include <grpcpp/client_context.h>
#include <minecpp/network/message/clientbound.h>
#include <minecpp/util/time.h>
#include <spdlog/spdlog.h>
#include <thread>
#include <utility>

namespace minecpp::service::front {

TickManager::TickManager(Server &server, const ChunkService &chunks) : server(server), chunk_service(chunks) {}

constexpr int keep_alive_count = 160;
constexpr int thread_limit     = 5;

[[noreturn]] void TickManager::tick()
{
   using namespace std::chrono_literals;
   uint64_t keep_alive_counter{};
   for (;;) {
      load_chunks();
      ++keep_alive_counter;
      if (keep_alive_counter >= keep_alive_count) {
         keep_alive_counter = 0;
         keep_alive();
      }
      std::this_thread::sleep_for(50ms);
   }
}

void TickManager::keep_alive()
{
   server.for_each_connection([](const std::shared_ptr<Connection> &conn) {
      if (!conn)
         return;
      send(conn, minecpp::network::message::KeepAlive{
                         .time = minecpp::util::now_milis(),
                 });
   });
}

void TickManager::load_chunks()
{
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

      m_future_chunks.emplace_back(std::async(
              std::launch::async,
              [](std::shared_ptr<Connection> conn, ChunkService chunk_service, int x, int z) {
                 grpc::ClientContext ctx;
                 ChunkLoadTicket ticket{.conn = std::move(conn)};
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
              },
              conn, chunk_service, chunk_pos.x, chunk_pos.z));
   });
}

}// namespace minecpp::service::front
