#pragma once
#include <cstdint>

namespace minecpp::service::storage::fdb {

struct Buffer
{
   const char *data{};
   std::size_t size{};
};

}// namespace minecpp::service::storage::fdb
