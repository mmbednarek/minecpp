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

std::string format_system_info(std::string_view message);

}// namespace minecpp::network
