#pragma once
#include <array>
#include <atomic>
#include <mb/int.h>
#include <mutex>

namespace minecpp::util {

template<typename T, mb::size N>
class StaticQueue {
   std::array<T, N> m_data{};
   std::mutex m_mutex{};
   mb::size m_front{};
   mb::size m_back{};

 public:
   void push(T &&el) {
      m_mutex.lock();
      auto next_front = (m_front + 1) % N;
      while (next_front == m_back) {
         m_mutex.unlock();
         m_mutex.lock();
         next_front = (m_front + 1) % N;
      }

      m_data[m_front] = std::forward<T>(el);
      m_front = next_front;
      m_mutex.unlock();
   }

   [[nodiscard]] T pop() {
      m_mutex.lock();
      while (m_back == m_front) {
         m_mutex.unlock();
         m_mutex.lock();
      }

      auto out = std::forward<T>(m_data[m_back]);
      m_data[m_back] = T();
      m_back = (m_back + 1) % N;
      m_mutex.unlock();
      return out;
   }

   [[nodiscard]] mb::size size() {
      mb::size out_size;
      m_mutex.lock();
      if (m_front >= m_back) {
         out_size = m_front - m_back;
      } else {
         out_size = m_front - m_back + N;
      }
      m_mutex.unlock();
      return out_size;
   }

   [[nodiscard]] bool empty() {
      bool out_empty;
      m_mutex.lock();
      out_empty = m_front == m_back;
      m_mutex.unlock();
      return out_empty;
   }
};

}// namespace minecpp::util