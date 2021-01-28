#pragma once
#include <array>
#include <string>

namespace Utils {

std::array<char, 2> char_hex(char c);
std::string data_to_hex(const char *data, std::size_t size);

}