#pragma once
#include "Fdb.h"
#include <mb/result.h>
#include <string>

namespace minecpp::service::storage::fdb {

class Error
{
 public:
   explicit Error(fdb_error_t error_code);

   [[nodiscard]] std::string to_string() const;
   [[nodiscard]] bool ok() const;

 private:
   fdb_error_t m_error_code;
};

template <typename TValue>
using Result = mb::result<TValue, Error>;

}// namespace minecpp::service::storage::fdb