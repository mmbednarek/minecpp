#pragma once
#include <cstdint>
#include <functional>

namespace Utils {

void for_each_packed(const std::vector<long long> &data,
                     std::function<void(uint32_t)> callback);

void set_packed(std::vector<long long> &data, uint8_t bits, uint32_t index,
                uint32_t value);

void resize_pack(std::vector<long long> &data, uint8_t old_bits,
                 uint8_t new_bits);

}
