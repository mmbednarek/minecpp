#pragma once
#include "handler.h"
#include <minenet/msg/reader.h>

namespace Front::Protocol {

class StatusHandler : public Handler {
 public:
   StatusHandler();
   void handle(Connection &conn, MineNet::Message::Reader &r) override;
   void handle_disconnect(Connection &conn) override;

 private:
   void handle_info(Connection &conn);
   void handle_ping(Connection &conn, MineNet::Message::Reader &r);
};

} // namespace Front::Protocol
