#ifndef MINECPP_CHAT_H
#define MINECPP_CHAT_H
#include <minecpp/format/format.h>
#include <ostream>
#include <string>
#include <string_view>

namespace minecpp::chat {

enum class MessageType : int
{
   PlayerMessage = 0,
   SystemMessage = 1,
};

enum class ChatVisibility : uint8_t
{
   Full,
   System,
   Hidden
};

struct ChatMessage
{
   std::string translate;
   std::vector<format::Node> with;

   void write(std::ostream &stream) const;
   std::string to_string() const;
};

std::string format_system_warning(std::string_view message);

std::string format_warning_unknown_op_code(int code);

std::string format_chat_message(std::string_view player_name, std::string_view message);

std::string format_left_message(std::string_view player_name);

std::string format_join_message(std::string_view player_name);

}// namespace minecpp::chat

#endif//MINECPP_CHAT_H
