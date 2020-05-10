#pragma once
#include "../packet/writer.h"
#include "handler.h"

namespace Front {

class PlayClient {
 private:
   Packet::Writer &writer;
};

} // namespace Front
