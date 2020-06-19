#pragma once
#include <minenet/msg/reader.h>

namespace Front {

class Connection;

namespace Protocol {

class Handler {
 public:
   virtual void handle(Connection &conn, MineNet::Message::Reader &r) = 0;
   virtual void handle_disconnect(Connection &conn) = 0;
};

} // namespace Protocol

} // namespace Front
