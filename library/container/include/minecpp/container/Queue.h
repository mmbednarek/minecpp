#pragma once
#include <mutex>
#include <optional>
#include <queue>
#include <shared_mutex>

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
      TValue result;
      {
         std::unique_lock lock{m_mutex};
         result = std::move(m_queue.front());
         m_queue.pop();
      }
      return result;
   }

   [[nodiscard]] std::optional<TValue> try_pop()
   {
      std::unique_lock lock{m_mutex};
      if (m_queue.empty()) {
         return std::nullopt;
      }

      auto result = std::move(m_queue.front());
      m_queue.pop();
      return result;
   }

   [[nodiscard]] bool is_empty() const
   {
      std::shared_lock lock{m_mutex};
      return m_queue.empty();
   }

 private:
   std::queue<TValue> m_queue;
   mutable std::shared_mutex m_mutex;
};

}// namespace minecpp::container