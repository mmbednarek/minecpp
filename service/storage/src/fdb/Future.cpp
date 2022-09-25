#include "Future.h"
#include <cassert>
#include <utility>

namespace minecpp::service::storage::fdb {

Future::Future(FDBFuture *future) :
    m_future{future}
{
}

Future::Future(Future &&other) noexcept :
    m_future{std::exchange(other.m_future, nullptr)}
{
}

Future &Future::operator=(Future &&other) noexcept
{
   m_future = std::exchange(other.m_future, nullptr);
   return *this;
}

Future::~Future()
{
   if (m_future != nullptr) {
      fdb_future_destroy(m_future);
   }
}

Buffer Future::get_value()
{
   if (not await())
      return {};

   fdb_bool_t present{};
   const uint8_t *data{};
   int size{};

   if (fdb_future_get_value(m_future, &present, &data, &size) != 0) {
      return {};
   }

   if(not present)
   {
      return {};
   }

   return {reinterpret_cast<const char *>(data), static_cast<std::size_t>(size)};
}

bool Future::await() const
{
   return fdb_future_block_until_ready(m_future) == 0;
}

}// namespace minecpp::service::storage::fdb
