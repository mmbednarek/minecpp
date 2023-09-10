#pragma once
#include "minecpp/network/message/Reader.h"
#include "minecpp/network/message/Writer.h"
#include <cstdint>
#include <optional>
#include <string>

namespace minecpp::example2 {

class Properties
{
 public:
   std::string name{};
   double position{};
   std::int16_t count{};
   std::map<std::string, std::string> meta{};
   void serialize(::minecpp::network::message::Writer &writer) const;
   static Properties deserialize(::minecpp::network::message::Reader &reader);
};

}// namespace minecpp::example2
