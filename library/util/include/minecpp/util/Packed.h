#pragma once
#include <cstdint>
#include <functional>

namespace minecpp::util {

std::uint32_t log2(std::uint32_t x);

void for_each_packed(const std::vector<std::uint64_t> &data, std::uint8_t bits, std::uint32_t array_size,
                     const std::function<void(uint32_t)> &callback);

void set_packed(std::vector<std::uint64_t> &data, std::uint8_t bits, std::uint32_t index,
                std::uint32_t value);

std::vector<std::uint64_t> generate_packed(uint8_t bits, std::uint32_t array_size,
                                           const std::function<std::uint32_t()> &generator);

uint32_t get_packed(std::vector<std::uint64_t> &data, std::uint8_t bits, std::uint32_t index);

template<std::size_t size>
uint32_t get_packed(std::array<std::uint64_t, size> &data, std::uint8_t bits, std::uint32_t index)
{
   std::uint32_t parts     = 64 / bits;
   auto pack               = index / parts;
   std::uint32_t offset    = (index % parts) * bits;
   std::uint64_t mask      = ((1u << bits) - 1u);
   std::uint64_t full_pack = data[pack];
   return static_cast<std::uint32_t>((full_pack >> offset) & mask);
}

void resize_pack(std::vector<int64_t> &data, std::uint8_t old_bits, std::uint8_t new_bits);

}// namespace minecpp::util
