#include "TickSystem.h"
#include "JobSystem.h"
#include "World.h"

#include "minecpp/debug/TraceManager.h"
#include "minecpp/util/Threading.h"

#include <chrono>
#include <spdlog/spdlog.h>

namespace minecpp::service::engine {

TickSystem::TickSystem(World &world, ApiHandler &api_handler, storage::StorageClient &storage_client) :
    m_world(world),
    m_api_handler(api_handler),
    m_storage_client(storage_client)
{
}

void TickSystem::loop()
{
   using namespace std::chrono_literals;
   using std::chrono::duration_cast;
   using std::chrono::milliseconds;
   using std::chrono::system_clock;

   minecpp::util::set_debug_thread_info(minecpp::util::ThreadType::TickThread, 0);

   auto last_frame_tp = system_clock::now();
   while (m_running) {
      auto last_frame_diff = system_clock::now() - last_frame_tp;
      auto milis           = duration_cast<milliseconds>(last_frame_diff).count();
      auto prop            = static_cast<double>(milis) / 50.0;

      last_frame_tp = system_clock::now();

      run_tick(prop);

      m_api_handler.tick();
      m_storage_client.tick();
   }
}

void TickSystem::run_tick(double delta_time)
{
   using namespace std::chrono_literals;
   auto tps = 20.0 / delta_time;

   m_world.tick(delta_time);
   if (tps > 120.0) {
      std::this_thread::sleep_for(5ms);
   }

   if (static_cast<int>(tps) != m_last_tps) {
      spdlog::debug("system: tps={}", tps);
      m_last_tps = static_cast<int>(tps);
   }

   minecpp::debug::TraceManager::the().flush();
}

}// namespace minecpp::service::engine
