#pragma once
#include <cstdint>
#include <string>

namespace minecpp::network {

enum class ChatType : uint8_t
{
   Chat,
   System,
   GameInfo
};

enum class ChatVisibility : uint8_t
{
   Full,
   System,
   Hidden
};

}// namespace minecpp::network
