#include <minecpp/mineutils/hex.h>

namespace Utils {

std::array<char, 2> char_hex(char c) {
   std::array<char, 2> result;

   auto most = c / 16;
   if (most > 9) {
      result[0] = most - 10 + 'a';
   } else {
      result[0] = most + '0';
   }

   auto least = c % 16;
   if (least > 9) {
      result[1] = least - 10 + 'a';
   } else {
      result[1] = least + '0';
   }

   return result;
}

std::string data_to_hex(const char *data, std::size_t size) {
   std::string result;
   result.resize(size * 2);

   for (std::size_t i = 0; i < 2 * size; i += 2) {
      auto hex = char_hex(data[i]);
      result[i] = hex[0];
      result[i + 1] = hex[1];
   }

   return result;
}

} // namespace Utils
