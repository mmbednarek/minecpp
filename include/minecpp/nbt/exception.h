#pragma once
#include <stdexcept>

namespace minecpp::nbt {

class Exception : public std::runtime_error
{
 public:
   explicit Exception(const char *c);
   explicit Exception(const std::string &msg);
};
}// namespace minecpp::nbt
