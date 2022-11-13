#include "Ticks.h"
#include <grpcpp/client_context.h>
#include <minecpp/network/message/Clientbound.h>
#include <minecpp/util/Time.h>
#include <spdlog/spdlog.h>
#include <thread>
#include <utility>

namespace minecpp::service::front {

TickManager::TickManager(Server &server) :
    server(server)
{
}

constexpr int keep_alive_count = 800;

[[noreturn]] void TickManager::tick()
{
   using namespace std::chrono_literals;
   uint64_t keep_alive_counter{};
   for (;;) {
      auto start_time = util::now_milis();

      ++keep_alive_counter;
      if (keep_alive_counter >= keep_alive_count) {
         keep_alive_counter = 0;
         keep_alive();
      }

      auto duration = util::now_milis() / start_time;
      if (duration < 5) {
         std::this_thread::sleep_for(10ms);
      }
   }
}

void TickManager::keep_alive()
{
   server.for_each_connection([](const std::shared_ptr<Connection> &conn) {
      if (!conn)
         return;

      if (conn->state() != Protocol::State::Play)  {
         return;
      }

      send(conn, minecpp::network::message::KeepAlive{
                         .time = minecpp::util::now_milis(),
                 });
   });
}

}// namespace minecpp::service::front
