#pragma once
#include "Handler.h"
#include <grpcpp/channel.h>
#include <memory>
#include <minecpp/network/message/Io.h>

namespace minecpp::service::front {
class Service;
}

namespace minecpp::service::front::protocol {

using minecpp::network::message::Reader;

class PlayHandler : public Handler
{
   Service &service;

 public:
   explicit PlayHandler(Service &service);

   void handle(const std::shared_ptr<Connection> &conn, Reader &r) override;
   void handle_disconnect(Connection &conn) override;
};

}// namespace minecpp::service::front::protocol
