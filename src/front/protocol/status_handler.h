#pragma once
#include "handler.h"
#include "../packet/reader.h"
#include "../packet/writer.h"

namespace Front::Protocol {

class StatusHandler : public Handler {
 public:
   StatusHandler();
   virtual void handle(Connection &conn, Packet::Reader &r) override;

 private:
   void handle_info(Packet::Writer &w);
   void handle_ping(Packet::Writer &w, Packet::Reader &r);
};

} // namespace Front::Protocol
