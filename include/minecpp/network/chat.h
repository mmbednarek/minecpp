#pragma once
#include <cstdint>
#include <string>

namespace minecpp::network {

enum class ChatType : uint8_t { Chat, System, GameInfo };

enum class ChatVisibility : uint8_t  {Full, System, Hidden};

std::string format_system_info(std::string_view message);
std::string format_chat_message(std::string_view player_name, std::string_view message);
std::string format_left_message(std::string_view player_name);
std::string format_join_message(std::string_view player_name);

}
