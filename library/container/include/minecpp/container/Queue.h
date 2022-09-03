#pragma once
#include <mutex>
#include <queue>

namespace minecpp::container {

template<typename TValue>
class Queue
{
 public:
   template<typename TPushItem>
   void push(TPushItem &&item)
   {
      std::unique_lock lock{m_mutex};
      m_queue.push(std::forward<TPushItem>(item));
   }

   template<typename... TArgs>
   void emplace(TArgs &&...args)
   {
      std::unique_lock lock{m_mutex};
      m_queue.template emplace(std::forward<TArgs>(args)...);
   }

   [[nodiscard]] TValue pop()
   {
      std::unique_lock lock{m_mutex};
      auto result = std::move(m_queue.front());
      m_queue.pop();
      return result;
   }

   [[nodiscard]] bool is_empty() const
   {
      std::unique_lock lock{m_mutex};
      return m_queue.empty();
   }

 private:
   std::queue<TValue> m_queue;
   mutable std::mutex m_mutex;
};

}// namespace minecpp::container