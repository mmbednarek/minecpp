#include <minecpp/nbt/Exception.h>
#include <fmt/core.h>

namespace minecpp::nbt {

InvalidTag::InvalidTag(std::string_view structure, std::string_view key, TagId expected, TagId actual) :
   std::runtime_error(fmt::format("nbt: error parsing field {} in structure {}: unexpected tag {} (expected {})", key, structure, actual, expected))
{}

void verify_tag(std::string_view structure, std::string_view key, TagId expected, TagId actual)
{
   if (expected != actual) {
      throw InvalidTag(structure, key, expected, actual);
   }
}

}// namespace minecpp::nbt
