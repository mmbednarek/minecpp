#pragma once
#include "Buffer.h"
#include "Fdb.h"
#include "Future.h"
#include <string_view>

namespace minecpp::service::storage::fdb {

class Transaction
{
 public:
   explicit Transaction(FDBTransaction *transaction);

   Transaction(Transaction &&other) noexcept;
   Transaction &operator=(Transaction &&other) noexcept;

   Transaction(const Transaction &)            = delete;
   Transaction &operator=(const Transaction &) = delete;

   ~Transaction();

   void set(std::string_view key, Buffer buffer);
   Future get(std::string_view key);

   [[nodiscard]] constexpr FDBTransaction *raw() const
   {
      return m_transaction;
   }

   [[nodiscard]] Future commit();

 private:
   FDBTransaction *m_transaction;
};

}// namespace minecpp::service::storage::fdb
