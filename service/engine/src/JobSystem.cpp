#include "JobSystem.h"
#include "minecpp/util/Threading.h"

#include <fmt/format.h>
#include <utility>

namespace minecpp::service::engine {

TicketBuilder::TicketBuilder(JobSystem &job_system, std::unique_ptr<IJobCondition> condition) :
    m_job_system(job_system)
{
   m_conditions.push_back(std::move(condition));
}

void JobSystem::issue_ticket(Ticket ticket)
{
   bool is_completed = true;
   for (auto &condition : ticket.conditions) {
      if (condition->status() == JobConditionStatus::Complete) {
         continue;
      }

      is_completed = false;
      condition->resolve(*this);
   }

   if (is_completed) {
      issue_job(std::move(ticket.job));
      return;
   }

   std::unique_lock lock{m_pending_tickets_mutex};
   m_pending_tickets.push_back(std::move(ticket));
}

void JobSystem::issue_job(std::unique_ptr<IJob> job)
{
   {
      std::lock_guard lock{m_job_ready_mutex};
      m_pending_jobs.push(std::move(job));
   }
   m_has_job_condition.notify_one();
}

void JobSystem::worker_routine()
{
   minecpp::util::label_thread("Job System worker {}");

   while (m_is_running) {
      std::unique_lock lock{m_job_ready_mutex};
      m_has_job_condition.wait(lock, [this] { return not m_pending_jobs.is_empty(); });

      auto job = m_pending_jobs.pop();
      assert(job);

      lock.unlock();

      job->run();

      process_awaiting_tickets();
   }
}

void JobSystem::process_awaiting_tickets()
{
   std::unique_lock lock{m_pending_tickets_mutex};
   for (auto &ticket : m_pending_tickets) {
      if (not ticket.is_completed())
         continue;

      issue_job(std::move(ticket.job));
   }

   m_pending_tickets.erase(std::remove_if(m_pending_tickets.begin(), m_pending_tickets.end(),
                                          [](Ticket &ticket) { return ticket.job == nullptr; }),
                           m_pending_tickets.end());
}

JobSystem::JobSystem(std::size_t thread_count)
{
   m_threads.reserve(thread_count);
   std::generate_n(std::back_inserter(m_threads), thread_count,
                   [this]() { return std::thread(&JobSystem::worker_routine, this); });
}

bool Ticket::is_completed() const
{
   for (const auto &condition : this->conditions) {
      if (condition->status() == JobConditionStatus::Complete)
         continue;

      return false;
   }
   return true;
}

void FunctorJob::run()
{
   m_callback();
}

FunctorJob::FunctorJob(std::function<void()> callback) :
    m_callback(std::move(callback))
{
}
}// namespace minecpp::service::engine