#pragma once
#include <fmt/core.h>
#include <mb/result.h>
#include <utility>

namespace minecpp::command {

struct Error
{
   int line, column;
   std::string message;

   template<typename... TArgs>
   Error(int line, int column, fmt::format_string<TArgs...> &&message, TArgs &&...args) :
       line(line),
       column(column),
       message(fmt::format(message, std::forward<TArgs>(args)...))
   {
   }
};

template<typename T>
using Result = mb::result<T, Error>;

}// namespace minecpp::command