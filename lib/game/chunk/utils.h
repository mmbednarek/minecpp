#pragma once
#include <cstdint>
#include <vector>

namespace Game {

int calculate_ref_count(const std::vector<int64_t> &data,
                        const std::vector<int> &palette);

}
