#pragma once
#include <atomic>
#include <condition_variable>
#include <memory>
#include <minecpp/container/Queue.h>
#include <minecpp/game/Game.h>
#include <mutex>
#include <vector>

namespace minecpp::service::engine {

class JobSystem;

class IJob
{
 public:
   virtual ~IJob() noexcept = default;

   virtual void run() = 0;
};

class FunctorJob : public IJob
{
 public:
   explicit FunctorJob(std::function<void()> callback);

   void run() override;

 private:
   std::function<void()> m_callback;
};

enum class JobConditionStatus
{
   NotQueued,
   Queued,
   Complete,
};

class IJobCondition
{
 public:
   virtual ~IJobCondition() noexcept = default;

   [[nodiscard]] virtual JobConditionStatus status() const = 0;
   virtual void resolve(JobSystem &job_system)             = 0;
};

struct Ticket
{
   std::unique_ptr<IJob> job;
   std::vector<std::unique_ptr<IJobCondition>> conditions;

   [[nodiscard]] bool is_completed() const;
};

// m_job_system.when<ChunkIsPresent>(position).run([] () { });

class JobSystem;

class TicketBuilder
{
 public:
   explicit TicketBuilder(JobSystem &job_system, std::unique_ptr<IJobCondition> condition);

   template<typename TCondition, typename... TArgs>
   [[nodiscard]] TicketBuilder &when(TArgs &&...args);

   template<typename TFunctor>
   void run(TFunctor &&callback);

 private:
   JobSystem &m_job_system;
   std::vector<std::unique_ptr<IJobCondition>> m_conditions;
};

class JobSystem
{
 public:
   explicit JobSystem(std::size_t thread_count);

   void issue_ticket(Ticket ticket);
   void issue_job(std::unique_ptr<IJob> job);
   void worker_routine();

   template<typename TCondition, typename... TArgs>
   TicketBuilder when(TArgs &&...args);

   void process_awaiting_tickets();

 private:
   std::atomic_bool m_is_running{true};

   container::Queue<std::unique_ptr<IJob>> m_pending_jobs{};

   std::mutex m_job_ready_mutex;
   std::condition_variable m_has_job_condition;

   std::mutex m_pending_tickets_mutex;
   std::vector<Ticket> m_pending_tickets{};

   std::vector<std::thread> m_threads;
};

template<typename TCondition, typename... TArgs>
TicketBuilder &TicketBuilder::when(TArgs &&...args)
{
   m_conditions.push_back(std::make_unique<TCondition>(std::forward<TArgs>(args)...));
   return *this;
}

template<typename TFunctor>
void TicketBuilder::run(TFunctor &&callback)
{
   m_job_system.issue_ticket(
           {std::make_unique<FunctorJob>(std::forward<TFunctor>(callback)), std::move(m_conditions)});
}

template<typename TCondition, typename... TArgs>
TicketBuilder JobSystem::when(TArgs &&...args)
{
   return TicketBuilder(*this, std::make_unique<TCondition>(std::forward<TArgs>(args)...));
}
}// namespace minecpp::service::engine