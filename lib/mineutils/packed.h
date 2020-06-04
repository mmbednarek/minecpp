#pragma once
#include <cstdint>
#include <functional>

namespace Utils {

void for_each_packed(const long *data, std::size_t size, std::size_t out_size,
                     std::function<void(uint32_t value)> callback);

}
