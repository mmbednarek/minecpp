#include <minecpp/util/Packed.h>

namespace minecpp::util {

std::uint32_t log2(const std::uint32_t x)
{
   std::uint32_t y;
   asm("\tbsr %1, %0\n" : "=r"(y) : "r"(x));
   return y;
}

void for_each_packed(const std::vector<std::uint64_t> &data, std::uint8_t bits, std::uint32_t array_size,
                     const std::function<void(uint32_t)> &callback)
{
   std::uint32_t i     = 0;
   std::uint32_t parts = 64 / bits;
   std::uint32_t mask  = (1u << bits) - 1u;

   for (auto pack : data) {
      for (std::uint32_t part = 0; part < parts; ++part) {
         callback(static_cast<std::uint32_t>(pack & mask));
         pack >>= bits;
         ++i;
         if (i >= array_size) {
            return;
         }
      }
   }
}

void set_packed(std::vector<uint64_t> &data, std::uint8_t bits, std::uint32_t index, std::uint32_t value)
{
   std::uint32_t parts  = 64 / bits;
   auto pack            = index / parts;
   std::uint32_t offset = (index % parts) * bits;
   std::uint64_t mask   = ((1u << bits) - 1u);

   auto full_pack = data[pack];
   full_pack &= ~(mask << offset);
   full_pack |= (value & mask) << offset;
   data[pack] = full_pack;
}

std::vector<uint64_t> generate_packed(std::uint8_t bits, std::uint32_t array_size,
                                      const std::function<std::uint32_t()> &generator)
{
   auto packs = bits * array_size / 64;
   if (64 % bits != 0) {
      ++packs;
   }
   int per_pack       = 64 / bits;
   std::uint32_t mask = (1u << bits) - 1u;
   std::vector<std::uint64_t> result(packs);

   std::uint32_t i = 0;
   for (auto &out : result) {
      std::uint64_t pack  = 0;
      std::uint32_t shift = 0;
      for (int j = 1; j < per_pack; ++j) {
         pack |= static_cast<uint64_t>(generator() & mask) << shift;
         ++i;
         if (i >= array_size) {
            out = pack;
            return result;
         }
         shift += bits;
      }
      pack |= static_cast<uint64_t>(generator() & mask) << shift;
      out = pack;
   }

   return result;
}

std::uint32_t get_packed(std::vector<uint64_t> &data, std::uint8_t bits, std::uint32_t index)
{
   std::uint32_t parts     = 64 / bits;
   auto pack               = index / parts;
   std::uint32_t offset    = (index % parts) * bits;
   std::uint64_t mask      = ((1u << bits) - 1u);
   std::uint64_t full_pack = data[pack];
   return static_cast<std::uint32_t>((full_pack >> offset) & mask);
}

void resize_pack(std::vector<uint64_t> &data, std::uint8_t old_bits, std::uint8_t new_bits)
{
   std::vector<uint64_t> resized(data.size() / old_bits * new_bits);

   std::uint32_t index = 0;
   for_each_packed(data, old_bits, 4096, [&resized, &index, new_bits](uint32_t value) {
      set_packed(resized, new_bits, index, value);
      ++index;
   });

   data = std::move(resized);
}

}// namespace minecpp::util
