#include <string>
#include <string_view>

namespace minecpp::util {

int hash_string(std::string_view s);
std::string repeat_string(std::string_view s, std::size_t n);

}// namespace minecpp::util
