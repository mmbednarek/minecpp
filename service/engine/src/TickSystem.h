#pragma once
#include <atomic>
#include <thread>

namespace minecpp::service::engine {

class World;

class TickSystem
{
 public:
   explicit TickSystem(World &world);

   void run_tick(double delta_time);
   void worker_routine();

 private:
   World &m_world;
   std::atomic_bool m_running{true};
   std::thread m_tick_thread;
   double m_delta_sum{};
};

}// namespace minecpp::service::engine