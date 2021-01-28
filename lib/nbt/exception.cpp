#include <minecpp/nbt/exception.h>

namespace minecpp::nbt {

Exception::Exception(const char *c) : std::runtime_error(c) {
}

Exception::Exception(const std::string& msg) : std::runtime_error(msg) {
}

}
