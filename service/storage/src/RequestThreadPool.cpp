#include "RequestThreadPool.h"

namespace minecpp::service::storage {

RequestThreadPool::RequestThreadPool(IHandler &handler, std::size_t thread_count) :
    m_handler(handler)
{
   m_threads.reserve(thread_count);
   std::generate_n(std::back_inserter(m_threads), thread_count, [this] {
      return std::thread{&RequestThreadPool::loop, this};
   });
}

RequestThreadPool::~RequestThreadPool()
{
   m_is_running = false;
}

void RequestThreadPool::loop()
{
   while (m_is_running) {
      std::unique_lock lk{m_mutex};
      m_condition.wait(lk, [this] { return not m_queue.empty(); });

      auto request = m_queue.front();
      m_queue.pop();
      lk.unlock();

      m_handler.handle_request(request.connection_id, std::move(request.data));
   }
}

void RequestThreadPool::handle_request(ConnectionId id, container::Buffer request)
{
   {
      std::lock_guard lk{m_mutex};
      m_queue.emplace(Request{id, std::move(request)});
   }
   m_condition.notify_one();
}

}// namespace minecpp::service::storage
