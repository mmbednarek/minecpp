#include <fmt/core.h>
#include <minecpp/chat/chat.h>
#include <minecpp/format/format.h>

namespace minecpp::chat {

std::string format_system_warning(std::string_view message)
{
   using format::Color;
   return format::Builder().bold(Color::Yellow, fmt::format("WARN ")).text(Color::White, message).to_string();
}

std::string format_chat_message(std::string_view player_name, std::string_view message)
{
   using format::Color;
   return ChatMessage{
           .translate = "chat.type.text",
           .with{format::Builder().text(Color::Blue, player_name).node(),
                 format::Builder().text(message).node()},
   }
           .to_string();
}

std::string format_left_message(std::string_view player_name)
{
   using format::Color;
   return format::Builder().text(Color::Yellow, fmt::format("{} left the game", player_name)).to_string();
}

std::string format_join_message(std::string_view player_name)
{
   using format::Color;
   return format::Builder().text(Color::Yellow, fmt::format("{} joined the game", player_name)).to_string();
}

std::string format_warning_unknown_op_code(int code)
{
   using format::Color;
   return format::Builder().text(Color::Yellow, "WARN ").text("unknown serverbound message with op code ").text(Color::Yellow, fmt::format("{:#02x}", code)).to_string();
}

void ChatMessage::write(std::ostream &stream) const
{
   stream << R"({"translate": ")" << translate << R"(", "with": [)";
   bool first = true;
   for (auto node : with) {
      if (first) {
         first = false;
      } else {
         stream << ", ";
      }

      node.write(stream);
   }
   stream << R"(]})";
}

std::string ChatMessage::to_string() const
{
   std::stringstream ss;
   write(ss);
   return ss.str();
}
}// namespace minecpp::chat