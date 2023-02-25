#include "TickSystem.h"
#include "JobSystem.h"
#include "World.h"
#include <chrono>
#include <spdlog/spdlog.h>

namespace minecpp::service::engine {

TickSystem::TickSystem(World &world) :
    m_world(world),
    m_tick_thread(&TickSystem::worker_routine, this)
{
}

void TickSystem::worker_routine()
{
   using namespace std::chrono_literals;
   using std::chrono::duration_cast;
   using std::chrono::milliseconds;
   using std::chrono::system_clock;

   auto last_frame_tp = system_clock::now();
   while (m_running) {
      auto last_frame_diff = system_clock::now() - last_frame_tp;
      auto milis           = duration_cast<milliseconds>(last_frame_diff).count();
      auto prop            = static_cast<double>(milis) / 50.0;

      last_frame_tp = system_clock::now();

      run_tick(prop);
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
}

}// namespace minecpp::service::engine
