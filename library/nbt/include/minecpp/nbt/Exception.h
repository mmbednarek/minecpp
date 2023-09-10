#pragma once

#include "Tag.h"

#include <stdexcept>

namespace minecpp::nbt {

class InvalidTag : public std::runtime_error
{
 public:
   InvalidTag(std::string_view structure, std::string_view key, TagId expected, TagId actual);
};

void verify_tag(std::string_view structure, std::string_view key, TagId expected, TagId actual);


}// namespace minecpp::nbt
