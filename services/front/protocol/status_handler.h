#pragma once
#include "handler.h"
#include <packet/packet.h>

namespace Front::Protocol {

class StatusHandler : public Handler {
 public:
   StatusHandler();
   virtual void handle(Connection &conn, Packet::Reader &r) override;

 private:
   void handle_info(Connection &conn);
   void handle_ping(Connection &conn, Packet::Reader &r);
};

} // namespace Front::Protocol
