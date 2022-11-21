#include "TickSystem.h"
#include "JobSystem.h"
#include <chrono>
#include <spdlog/spdlog.h>

namespace minecpp::service::engine {

void TickSystem::worker_routine()
{
   using namespace std::chrono_literals;
   using std::chrono::duration_cast;
   using std::chrono::milliseconds;
   using std::chrono::system_clock;

   auto last_frame_tp = system_clock::now();
   while (m_running) {
      auto last_frame_diff = system_clock::now() - last_frame_tp;
      auto prop            = static_cast<double>(duration_cast<milliseconds>(last_frame_diff).count()) / 16.6;

      last_frame_tp = system_clock::now();

      run_tick(prop);
   }
}

void TickSystem::run_tick(double delta_time)
{
   using namespace std::chrono_literals;
   std::this_thread::sleep_for(16ms);
}

}// namespace minecpp::service::engine
