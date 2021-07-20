#include <fmt/core.h>
#include <minecpp/chat/chat.h>

namespace minecpp::chat {

std::string format_system_info(std::string_view message) {
   return fmt::format(
           R"({"extra":[{"color": "red", "bold": true, "text": "Server"}, {"color":"white", "text": " {}"}], "text": ""})",
           message);
}

std::string format_chat_message(std::string_view player_name, std::string_view message) {
   return fmt::format(
           R"({"extra":[{"color": "gray", "text": "<{}>"}, {"color":"white", "text": " {}"}], "text": ""})",
           player_name, message);
}

std::string format_left_message(std::string_view player_name) {
   return fmt::format(
           R"({"extra":[{"color": "yellow", "text": "{} left the game"}], "text": ""})",
           player_name);
}

std::string format_join_message(std::string_view player_name) {
   return fmt::format(
           R"({"extra":[{"color": "yellow", "text": "{} joined the game"}], "text": ""})",
           player_name);
}

}// namespace minecpp::chat