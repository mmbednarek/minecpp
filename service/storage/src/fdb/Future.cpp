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

Result<Buffer> Future::get_value()
{
   auto err = await();
   if (not err.ok())
      return err;

   fdb_bool_t present{};
   const uint8_t *data{};
   int size{};

   err = Error(fdb_future_get_value(m_future, &present, &data, &size));
   if (not err.ok()) {
      return err;
   }

   if (not present) {
      return Buffer{nullptr, 0};
   }

   return Buffer{reinterpret_cast<const char *>(data), static_cast<std::size_t>(size)};
}

Error Future::await() const
{
   return Error(fdb_future_block_until_ready(m_future));
}

}// namespace minecpp::service::storage::fdb
