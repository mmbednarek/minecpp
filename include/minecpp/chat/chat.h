#ifndef MINECPP_CHAT_H
#define MINECPP_CHAT_H
#include <string>
#include <string_view>

namespace minecpp::chat {

enum class MessageType : int
{
   PlayerMessage = 0,
   SystemMessage = 1,
};

std::string format_system_info(std::string_view message);

std::string format_chat_message(std::string_view player_name, std::string_view message);

std::string format_left_message(std::string_view player_name);

std::string format_join_message(std::string_view player_name);

}// namespace minecpp::chat

#endif//MINECPP_CHAT_H
