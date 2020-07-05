#include "packed.h"

namespace Utils {

uint32_t log2(const uint32_t x) {
   uint32_t y;
   asm("\tbsr %1, %0\n" : "=r"(y) : "r"(x));
   return y;
}

void for_each_packed(const std::vector<long long> &data, uint8_t bits, uint32_t array_size,
                     std::function<void(uint32_t)> callback) {
   uint32_t i = 0;
   uint32_t parts = 64 / bits;
   uint32_t mask = (1u << bits) - 1u;

   for (uint64_t pack : data) {
      for (uint32_t part = 0; part < parts; ++part) {
         callback(pack & mask);
         pack >>= bits;
         ++i;
         if (i >= array_size) {
            return;
         }
      }
   }
}

void set_packed(std::vector<long long> &data, uint8_t bits, uint32_t index, uint32_t value) {
   uint32_t parts = 64 / bits;
   auto pack = index / parts;
   uint32_t offset = (index % parts) * bits;
   uint64_t mask = ((1u << bits) - 1u);

   uint64_t full_pack = data[pack];
   full_pack &= ~(mask << offset);
   full_pack |= (value & mask) << offset;
   data[pack] = full_pack;
}

uint32_t get_packed(std::vector<long long> &data, uint8_t bits, uint32_t index) {
   uint32_t parts = 64 / bits;
   auto pack = index / parts;
   uint32_t offset = (index % parts) * bits;
   uint64_t mask = ((1u << bits) - 1u);
   uint64_t full_pack = data[pack];
   return (full_pack >> offset) & mask;
}

void resize_pack(std::vector<long long> &data, uint8_t old_bits, uint8_t new_bits) {
   std::vector<long long> resized(data.size() / old_bits * new_bits);

   uint32_t index = 0;
   for_each_packed(data, old_bits, 4096, [&resized, &index, new_bits](uint32_t value) {
      set_packed(resized, new_bits, index, value);
      ++index;
   });

   data = resized;
}

} // namespace Utils
