#include "Protocol.h"

namespace minecpp::service::front::protocol {

std::string_view state_to_str(State s)
{
   switch (s) {
   case Handshake: return "Hand.hake";
   case Play: return "play";
   case Status: return "status";
   case Login: return "login";
   }
   return "unknown";
}

}// namespace minecpp::service::front::protocol
