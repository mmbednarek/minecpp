#include "Ticks.h"
#include <minecpp/network/message/Clientbound.h>
#include <minecpp/util/Time.h>
#include <spdlog/spdlog.h>
#include <thread>

namespace minecpp::service::front {

constexpr int g_keep_alive_count = 800;

TickManager::TickManager(Server &server, engine::Client &client) :
    m_server(server),
    m_client(client)
{
}

[[noreturn]] void TickManager::tick()
{
   using namespace std::chrono_literals;
   uint64_t keep_alive_counter{};
   for (;;) {
      auto start_time = util::now_milis();

      ++keep_alive_counter;
      if (keep_alive_counter >= g_keep_alive_count) {
         keep_alive_counter = 0;
         keep_alive();
      }

      m_client.tick();

      auto duration = util::now_milis() / start_time;
      if (duration < 5) {
         std::this_thread::sleep_for(10ms);
      }
   }
}

void TickManager::keep_alive()
{
   m_server.for_each_connection([](const std::shared_ptr<Connection> &conn) {
      if (!conn)
         return;

      if (conn->state() != protocol::State::Play) {
         return;
      }

      send(conn,
         minecpp::network::message::KeepAlive{
            .time = static_cast<std::uint32_t>(minecpp::util::now_milis()),
         }
      );
   });
}

}// namespace minecpp::service::front
