#pragma once
#include "Buffer.h"
#include "Error.h"
#include "Fdb.h"
#include <string_view>

namespace minecpp::service::storage::fdb {

class Future
{
 public:
   explicit Future(FDBFuture *future);
   ~Future();

   Future(Future &)            = delete;
   Future &operator=(Future &) = delete;

   Future(Future &&) noexcept;
   Future &operator=(Future &&) noexcept;

   [[nodiscard]] Error await() const;

   Result<Buffer> get_value();

 private:
   FDBFuture *m_future;
};

}// namespace minecpp::service::storage::fdb
