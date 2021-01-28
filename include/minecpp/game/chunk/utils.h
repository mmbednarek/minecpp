#pragma once
#include <cstdint>
#include <vector>

namespace Game {

int calculate_ref_count(const std::vector<std::int64_t> &data,
                        const std::vector<std::uint32_t> &palette);

}
