#pragma once
#include <packet/reader.h>

namespace Front {

class Connection;

namespace Protocol {

class Handler {
 public:
   virtual void handle(Connection &conn, Packet::Reader &r) = 0;
};

} // namespace Protocol

} // namespace Front
