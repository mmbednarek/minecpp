#pragma once
#include "../../api/pbcpp/engine.grpc.pb.h"
#include "../packet/writer.h"
#include "../players.h"
#include "handler.h"
#include <grpcpp/channel.h>
#include <memory>

namespace Front::Protocol {

class PlayHandler : public Handler {
 public:
   PlayHandler(std::shared_ptr<grpc::Channel> &engine_chan);
   void init_player(Packet::Writer &w, Player &p);

   virtual void handle(Connection &conn, Packet::Reader &r) override;

 private:
   std::shared_ptr<minecpp::engine::PlayerService::Stub> player_service;
};

} // namespace Front::Protocol
