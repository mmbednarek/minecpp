#include "string.h"

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
   return result/* ^ (result >> 16)*/;
}

} // namespace Utils