#pragma once
#include "Handler.h"
#include <minecpp/network/message/File.h>

namespace minecpp::service::front::protocol {

class StatusHandler : public Handler
{
 public:
   StatusHandler();
   void handle(const std::shared_ptr<Connection> &conn, minecpp::network::message::Reader &r) override;
   void handle_disconnect(Connection &conn) override;

 private:
   void handle_info(const std::shared_ptr<Connection> &conn);
   static void handle_ping(const std::shared_ptr<Connection> &conn, minecpp::network::message::Reader &r);
};

}// namespace minecpp::service::front::protocol
