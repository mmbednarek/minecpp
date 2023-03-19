#pragma once
#include <cstdint>
#include <vector>

namespace minecpp::world {

int calculate_ref_count(const std::vector<std::uint64_t> &data, const std::vector<std::uint32_t> &palette);

}
