#include <minecpp/network/chat.h>
#include <minecpp/util/format.h>

namespace minecpp::network {

std::string format_system_info(std::string_view message)
{
   return minecpp::util::format(
           R"({"extra":[{"color": "red", "bold": true, "text": "Server"}, {"color":"white", "text": " {}"}], "text": ""})",
           message);
}

}// namespace minecpp::network
