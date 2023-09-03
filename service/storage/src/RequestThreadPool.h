#pragma once

#include "IHandler.h"

#include "minecpp/container/BasicBuffer.hpp"

#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace minecpp::service::storage {

class RequestThreadPool : public IHandler
{
 public:
   struct Request
   {
      ConnectionId connection_id;
      container::Buffer data;
   };

   explicit RequestThreadPool(IHandler &handler, std::size_t thread_count);
   ~RequestThreadPool() override;

   void loop();
   void handle_request(ConnectionId id, container::Buffer request) override;

 private:
   IHandler &m_handler;
   std::vector<std::thread> m_threads;
   std::queue<Request> m_queue;
   std::mutex m_mutex;
   std::condition_variable m_condition;
   bool m_is_running{true};
};

}// namespace minecpp::service::storage