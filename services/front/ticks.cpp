#include "ticks.h"
#include <grpcpp/client_context.h>
#include <minenet/msg/clientbound.h>
#include <minepb/chunk_storage.pb.h>
#include <mineutils/time.h>
#include <spdlog/spdlog.h>

namespace Front {

TickManager::TickManager(Server &server, const ChunkService &chunks) : server(server), chunk_service(chunks) {}

constexpr int keep_alive_interval = 8000;
constexpr int load_chunks_interval = 100;

[[noreturn]] void TickManager::tick() {
   uint64_t last_keep_alive = 0;
   uint64_t last_load_chunks = 0;
   for (;;) {
      auto now = Utils::now_milis();
      if (now - last_keep_alive >= keep_alive_interval) {
         keep_alive();
         last_keep_alive = Utils::now_milis();
      }
      if (now - last_load_chunks >= load_chunks_interval) {
         load_chunks();
         last_load_chunks = Utils::now_milis();
      }
   }
}

void TickManager::keep_alive() {
   server.for_each_connection([](const std::shared_ptr<Connection> &conn) {
      if (!conn)
         return;
      send(conn, MineNet::Message::KeepAlive{
                     .time = Utils::now_milis(),
                 });
   });
}

void TickManager::load_chunks() {
   server.for_each_connection([this](const std::shared_ptr<Connection> &conn) {
      if (!conn)
         return;
      if (!conn->has_chunks())
         return;

      auto chunk_pos = conn->pop_chunk();

      grpc::ClientContext ctx;
      minecpp::chunk::NetChunk chunk;
      minecpp::chunk_storage::LoadChunkRequest load_chunk_request;
      load_chunk_request.set_x(std::get<0>(chunk_pos));
      load_chunk_request.set_z(std::get<1>(chunk_pos));

      auto status = chunk_service->LoadChunk(&ctx, load_chunk_request, &chunk);
      if (!status.ok()) {
         spdlog::error("error loading chunk: {}", status.error_message());
         return;
      }

      send(conn, MineNet::Message::ChunkData{
                     .chunk = chunk,
                 });
      send(conn, MineNet::Message::UpdateLight{
                     .chunk = chunk,
                 });
   });
}

} // namespace Front
