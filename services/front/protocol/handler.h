#pragma once
#include <minecpp/network/message/reader.h>

namespace Front {

class Connection;

namespace Protocol {

class Handler {
 public:
   virtual void handle(const std::shared_ptr<Connection> &conn, minecpp::network::message::Reader &r) = 0;
   virtual void handle_disconnect(Connection &conn) = 0;
};

} // namespace Protocol

} // namespace Front
