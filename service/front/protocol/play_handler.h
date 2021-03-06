#pragma once
#include "handler.h"
#include <grpcpp/channel.h>
#include <memory>
#include <minecpp/network/message/io.h>
#include <minepb/engine.pb.h>

namespace Front {
class Service;
}

namespace Front::Protocol {

using minecpp::network::message::Reader;

class PlayHandler : public Handler {
   Service &service;

 public:
   PlayHandler(Service &service);

   void handle(const std::shared_ptr<Connection> &conn, Reader &r) override;
   void handle_disconnect(Connection &conn) override;
};

} // namespace Front::Protocol
