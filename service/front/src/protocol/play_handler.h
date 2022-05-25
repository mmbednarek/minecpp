#pragma once
#include "handler.h"
#include <grpcpp/channel.h>
#include <memory>
#include <minecpp/network/message/io.h>

namespace minecpp::service::front {
class Service;
}

namespace minecpp::service::front::Protocol {

using minecpp::network::message::Reader;

class PlayHandler : public Handler
{
   Service &service;

 public:
   explicit PlayHandler(Service &service);

   void handle(const std::shared_ptr<Connection> &conn, Reader &r) override;
   void handle_disconnect(Connection &conn) override;
};

}// namespace minecpp::service::front::Protocol
