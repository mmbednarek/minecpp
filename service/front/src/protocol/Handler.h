#pragma once
#include <minecpp/network/message/File.h>

namespace minecpp::service::front {

class Connection;

namespace protocol {

class Handler
{
 public:
   virtual void handle(const std::shared_ptr<Connection> &conn, minecpp::network::message::Reader &r) = 0;
   virtual void handle_disconnect(Connection &conn)                                                   = 0;
};

}// namespace protocol

}// namespace minecpp::service::front
