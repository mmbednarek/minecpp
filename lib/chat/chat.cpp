#include <fmt/core.h>
#include <minecpp/chat/chat.h>
#include <minecpp/format/format.h>

namespace minecpp::chat {

std::string format_system_info(std::string_view message)
{
   using format::Color;
   return format::Builder().bold(Color::Red, fmt::format("Server ")).text(Color::White, message).build();
}

std::string format_chat_message(std::string_view player_name, std::string_view message)
{
   using format::Color;
   return format::Builder().text(Color::Gray, fmt::format("<{}> ", player_name)).text(Color::White, message).build();
}

std::string format_left_message(std::string_view player_name)
{
   using format::Color;
   return format::Builder().text(Color::Yellow, fmt::format("{} left the game", player_name)).build();
}

std::string format_join_message(std::string_view player_name)
{
   using format::Color;
   return format::Builder().text(Color::Yellow, fmt::format("{} joined the game", player_name)).build();
}

}// namespace minecpp::chat