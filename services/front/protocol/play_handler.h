#pragma once
#include "../players.h"
#include "handler.h"
#include <grpcpp/channel.h>
#include <memory>
#include <minepb/engine.pb.h>
#include <minenet/msg/io.h>

namespace Front::Protocol {

class PlayHandler : public Handler {
 public:
   PlayHandler();

   virtual void handle(Connection &conn, MineNet::Message::Reader &r) override;
};

} // namespace Front::Protocol
