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
   ~Transaction();

   void set(std::string_view key, Buffer buffer);
   Future get(std::string_view key);

   [[nodiscard]] Future commit();

 private:
   FDBTransaction *m_transaction;
};

}// namespace minecpp::service::storage::fdb
