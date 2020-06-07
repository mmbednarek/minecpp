#pragma once
#include <cstdint>
#include <vector>

namespace Game {

int calculate_ref_count(const std::vector<long long> &data,
                        const std::vector<int> &palette);

}
