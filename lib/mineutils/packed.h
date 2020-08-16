#pragma once
#include <cstdint>
#include <functional>

namespace Utils {

uint32_t log2(uint32_t x);

void for_each_packed(const std::vector<int64_t> &data, uint8_t bits, uint32_t array_size,
                     std::function<void(uint32_t)> callback);

void set_packed(std::vector<int64_t> &data, uint8_t bits, uint32_t index, uint32_t value);

std::vector<int64_t> generate_packed(uint8_t bits, uint32_t array_size, const std::function<uint32_t()> &generator);

uint32_t get_packed(std::vector<int64_t> &data, uint8_t bits, uint32_t index);

template <std::size_t size> uint32_t get_packed(std::array<uint64_t, size> &data, uint8_t bits, uint32_t index) {
   uint32_t parts = 64 / bits;
   auto pack = index / parts;
   uint32_t offset = (index % parts) * bits;
   uint64_t mask = ((1u << bits) - 1u);
   uint64_t full_pack = data[pack];
   return (full_pack >> offset) & mask;
}

void resize_pack(std::vector<int64_t> &data, uint8_t old_bits, uint8_t new_bits);

} // namespace Utils
