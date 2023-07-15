#pragma once
#include "Handler.h"

#include "minecpp/network/message/Io.h"

#include <memory>

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

   void handle(Connection &connection, Reader &r) override;
   void handle_disconnect(Connection &connection) override;
};

}// namespace minecpp::service::front::protocol
