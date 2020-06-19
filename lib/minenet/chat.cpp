#include "chat.h"
#include <mineutils/format.h>

namespace MineNet {

std::string format_system_info(std::string_view message) {
   return Utils::format(R"({"extra":[{"color": "red", "bold": true, "text": "Server"}, {"color":"white", "text": " {}"}], "text": ""})", message);
}

std::string format_chat_message(std::string_view player_name, std::string_view message) {
   return Utils::format(R"({"extra":[{"color": "yellow", "bold": true, "text": "{}"}, {"color":"gray", "text": " {}"}], "text": ""})", player_name, message);
}

std::string format_left_message(std::string_view player_name) {
   return Utils::format(R"({"extra":[{"color": "gold", "bold": true, "text": "Player {} left the server"}], "text": ""})", player_name);
}

std::string format_join_message(std::string_view player_name) {
   return Utils::format(R"({"extra":[{"color": "gold", "bold": true, "text": "Player {} joined the server"}], "text": ""})", player_name);
}

}
