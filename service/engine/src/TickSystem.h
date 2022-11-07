#pragma once
#include <atomic>

namespace minecpp::service::engine {

class JobSystem;

class TickSystem
{
 public:
   void run_tick(double delta_time);
   void worker_routine();

 private:
   std::atomic_bool m_running{true};
   //   JobSystem &m_job_system;
};

}// namespace minecpp::service::engine