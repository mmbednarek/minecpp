#pragma once
#include <functional>

namespace minecpp::util {

void around(int x, int y, std::function<void(int, int)> f);

}
