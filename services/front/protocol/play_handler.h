#pragma once
#include "../players.h"
#include "handler.h"
#include <grpcpp/channel.h>
#include <memory>
#include <minepb/engine.pb.h>
#include <packet/writer.h>

namespace Front::Protocol {

class PlayHandler : public Handler {
 public:
   PlayHandler();

   virtual void handle(Connection &conn, Packet::Reader &r) override;
};

} // namespace Front::Protocol
