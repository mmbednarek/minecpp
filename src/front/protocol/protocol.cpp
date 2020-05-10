#include "protocol.h"

namespace Front::Protocol {

std::string_view state_to_str(State s) {
   switch (s) {
   case Handshake:
      return "handshake";
   case Play:
      return "play";
   case Status:
      return "status";
   case Login:
      return "login";
   }
   return "unknown";
}

} // namespace Front::Protocol
