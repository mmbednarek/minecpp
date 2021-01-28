#include <minecpp/mineutils/string.h>

namespace Utils {

static int64_t pow(int64_t base, int64_t pow) {
   int64_t result = 1;
   for (int64_t i = 0; i < pow; ++i) {
      result *= base;
   }
   return result;
}

int hash_string(std::string_view s) {
   uint32_t result = 0;
   auto n = s.size();
   for (const auto &c : s) {
      --n;
      result += static_cast<int>(c * pow(31, n));
   }
   return result /* ^ (result >> 16)*/;
}

std::string repeat_string(std::string_view s, std::size_t n) {
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

}// namespace Utils