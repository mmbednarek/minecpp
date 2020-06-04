#include "packed.h"
#include <numeric>

namespace Utils {

void for_each_packed(const long *data, std::size_t size, std::size_t out_size,
                     std::function<void(uint32_t value)> callback) {
   auto bits = size * 64 / 4096;
   uint8_t parts = bits / std::gcd(0x40, bits);
   auto cycles = size / parts;

   size_t dat_i = 0;
   for (uint32_t cycle = 0u; cycle < cycles; ++cycle) {
      uint16_t trail = 0u;
      uint8_t trail_size = 0u;
      for (uint8_t part = 0u; part < parts; ++part) {
         auto values = (0x40 + trail_size) / bits;
         auto packet = data[dat_i++];
         uint16_t beg_bits = bits - trail_size;
         callback(trail | ((packet & ((1u << beg_bits) - 1u)) << trail_size));
         packet >>= beg_bits;
         for (int n = 1u; n < values; ++n) {
            callback(packet & ((1u << bits) - 1u));
            packet >>= bits;
         }
         trail = packet;
         trail_size = (0x40 + trail_size) % bits;
      }
   }
}

}
