#pragma once
#include <functional>

namespace Utils {

void around(int x, int y, std::function<void(int, int)> f);

}
