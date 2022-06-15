#ifndef MINECPP_POOL_H
#define MINECPP_POOL_H
#include <boost/pool/object_pool.hpp>
#include <mutex>

namespace minecpp::util {

template<typename T>
class AtomicPool
{
   boost::object_pool<T> m_pool;
   std::mutex m_mutex;

 public:
   template<typename... TArgs>
   [[nodiscard]] T *construct(TArgs... args)
   {
      std::lock_guard lock(m_mutex);
      return m_pool.construct(args...);
   }

   void free(T *ptr)
   {
      std::lock_guard lock(m_mutex);
      m_pool.free(ptr);
   }
};

}// namespace minecpp::util

#endif//MINECPP_POOL_H
