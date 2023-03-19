#include <minecpp/util/String.h>

namespace minecpp::util {

std::string repeat_string(std::string_view s, std::size_t n)
{
   if (n == 1) {
      return std::string(s);
   }
   std::string result;
   auto full_size = s.size() * n;
   result.reserve(full_size);

   for (std::size_t i = 0; i < full_size; i++) {
      result.push_back(s.at(i % s.size()));
   }

   return result;
}

}// namespace minecpp::util