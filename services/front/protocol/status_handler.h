#pragma once
#include "handler.h"
#include <minenet/msg/reader.h>

namespace Front::Protocol {

class StatusHandler : public Handler {
 public:
   StatusHandler();
   virtual void handle(Connection &conn, MineNet::Message::Reader &r) override;

 private:
   void handle_info(Connection &conn);
   void handle_ping(Connection &conn, MineNet::Message::Reader &r);
};

} // namespace Front::Protocol
