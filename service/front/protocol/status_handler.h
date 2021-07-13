#pragma once
#include "handler.h"
#include <minecpp/network/message/file.h>

namespace Front::Protocol {

class StatusHandler : public Handler {
 public:
   StatusHandler();
   void handle(const std::shared_ptr<Connection> &conn,
               minecpp::network::message::Reader &r) override;
   void handle_disconnect(Connection &conn) override;

 private:
   void handle_info(const std::shared_ptr<Connection> &conn);
   void handle_ping(const std::shared_ptr<Connection> &conn,
                    minecpp::network::message::Reader &r);
};

} // namespace Front::Protocol
