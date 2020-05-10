#pragma once

namespace Front {

class Connection;

namespace Packet {
   class Writer;
   class Reader;
}

namespace Protocol {

class Handler {
 public:
   virtual void handle(Packet::Writer &w, Packet::Reader &r) = 0;
};

} // namespace Protocol

} // namespace Front
