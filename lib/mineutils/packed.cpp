#include "packed.h"
#include <numeric>

namespace Utils {

void for_each_packed(const std::vector<long long> &data,
                     std::function<void(uint32_t)> callback) {
   auto bits = data.size() * 64 / 4096;
   uint8_t parts = bits / std::gcd(0x40, bits);
   auto cycles = data.size() / parts;

   size_t dat_i = 0;
   for (uint32_t cycle = 0u; cycle < cycles; ++cycle) {
      uint16_t trail = 0u;
      uint8_t trail_size = 0u;
      for (uint8_t part = 0u; part < parts; ++part) {
         auto values = (0x40 + trail_size) / bits;
         uint64_t packet = data[dat_i++];
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

void set_packed(std::vector<long long> &data, uint8_t bits, uint32_t index,
                uint32_t value) {
   int pack = bits * index / 64;
   int offset = bits * index % 64;

   uint64_t mask = ((1u << bits) - 1u);

   uint64_t full_pack = data[pack];
   full_pack &= ~(mask << offset);
   full_pack |= (value & mask) << offset;
   data[pack] = full_pack;

   if ((64 - offset) < bits) {
      auto trailing_bits = bits + offset - 64;
      full_pack = data[pack + 1];
      mask = ((1u << trailing_bits)) - 1u;
      full_pack &= ~mask;
      full_pack |= (value >> (64 - offset)) & mask;
      data[pack + 1] = full_pack;
   }
}

void resize_pack(std::vector<long long> &data, uint8_t old_bits,
                 uint8_t new_bits) {
   std::vector<long long> resized(data.size() / old_bits * new_bits);

   uint32_t index = 0;
   for_each_packed(data, [&resized, &index, new_bits](uint32_t value) {
      set_packed(resized, new_bits, index, value);
      ++index;
   });

   data = resized;
}

} // namespace Utils
