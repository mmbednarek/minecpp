#pragma once
#include "../../api/pbcpp/engine.grpc.pb.h"
#include "../../common/packet/writer.h"
#include "../players.h"
#include "handler.h"
#include <grpcpp/channel.h>
#include <memory>

namespace Front::Protocol {

class PlayHandler : public Handler {
 public:
   PlayHandler();

   virtual void handle(Connection &conn, Packet::Reader &r) override;
};

} // namespace Front::Protocol
