#pragma once
#include <minecpp/network/message/Reader.h>

namespace minecpp::service::front {

class Connection;

namespace protocol {

class Handler
{
 public:
   virtual void handle(Connection &connection, minecpp::network::message::Reader &reader) = 0;
   virtual void handle_disconnect(Connection &connection)                                 = 0;
};

}// namespace protocol

}// namespace minecpp::service::front
