#pragma once
#include <mutex>
#include <queue>
#include <optional>

namespace minecpp::container {

template<typename TValue>
class Queue
{
 public:
   template<typename TPushItem>
   void push(TPushItem &&item)
   {
      std::lock_guard lock{m_mutex};
      m_queue.push(std::forward<TPushItem>(item));
   }

   template<typename... TArgs>
   void emplace(TArgs &&...args)
   {
      std::lock_guard lock{m_mutex};
      m_queue.template emplace(std::forward<TArgs>(args)...);
   }

   [[nodiscard]] TValue pop()
   {
      TValue result;
      {
         std::lock_guard lock{m_mutex};
         result = std::move(m_queue.front());
         m_queue.pop();
      }
      return result;
   }

   [[nodiscard]] std::optional<TValue> try_pop()
   {
      std::lock_guard lock{m_mutex};
      if (m_queue.empty()) {
         return std::nullopt;
      }

      auto result = std::move(m_queue.front());
      m_queue.pop();
      return result;
   }

   [[nodiscard]] bool is_empty() const
   {
      bool empty;
      {
         std::lock_guard lock{m_mutex};
         empty = m_queue.empty();
      }
      return empty;
   }

 private:
   std::queue<TValue> m_queue;
   mutable std::mutex m_mutex;
};

}// namespace minecpp::container