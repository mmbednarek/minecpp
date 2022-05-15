#pragma once
#include <cstdint>
#include <vector>

namespace minecpp::game {

int calculate_ref_count(const std::vector<std::int64_t> &data, const std::vector<std::uint32_t> &palette);

}
