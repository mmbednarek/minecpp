#include <string>
#include <string_view>

namespace Utils {

int hash_string(std::string_view s);
std::string repeat_string(std::string_view s, std::size_t n);

}// namespace Utils
