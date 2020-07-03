#pragma once
#include <cstdint>
#include <functional>

namespace Utils {

uint32_t log2(uint32_t x);

void for_each_packed(const std::vector<long long> &data, uint8_t bits,
                     uint32_t array_size,
                     std::function<void(uint32_t)> callback);

void set_packed(std::vector<long long> &data, uint8_t bits, uint32_t index,
                uint32_t value);

void resize_pack(std::vector<long long> &data, uint8_t old_bits,
                 uint8_t new_bits);

}
