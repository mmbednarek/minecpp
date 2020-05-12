#pragma once
#include <sstream>
#include <string_view>

namespace Utils {

template <typename First, typename... Args>
static void _do_format(const std::string_view f, std::stringstream &ss,
                       First first, Args... a) {
   char last = 0;
   int i = 0;
   for (const auto &c : f) {
      if (last == '{' && c == '}') {
         ss << f.substr(0, i - 1);
         ss << first;
         if constexpr (sizeof...(Args) > 0) {
            auto sub = f.substr(i + 1, f.size());
            _do_format(sub, ss, a...);
         } else {
            ss << f.substr(i + 1, f.size());
         }
         return;
      }
      ++i;
      last = c;
   }
}

template <typename... Args> std::string format(std::string_view f, Args... a) {
   std::stringstream ss;
   _do_format(f, ss, a...);
   return ss.str();
}

std::string format(std::string_view f);

} // namespace Utils
