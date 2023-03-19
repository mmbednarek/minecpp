#pragma once
#include <string>
#include <string_view>

namespace minecpp::util {

std::string repeat_string(std::string_view s, std::size_t n);

[[nodiscard]] constexpr std::string_view to_string(bool value)
{
   return value ? "true" : "false";
}

}// namespace minecpp::util
