#pragma once
#include <string_view>

namespace Front::Protocol {

enum State : char { Handshake = -1, Play = 0, Status = 1, Login = 2 };

std::string_view state_to_str(State s);

} // namespace Front::Protocol
