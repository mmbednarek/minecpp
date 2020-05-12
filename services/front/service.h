#pragma once
#include "connection.h"
#include "players.h"
#include <grpcpp/channel.h>
#include <minepb/engine.grpc.pb.h>
#include <minepb/engine.pb.h>

namespace Front {

class Service {
 public:
   explicit Service(PlayerManager &players,
                    std::shared_ptr<grpc::Channel> &engine_chan);

   struct LoginResponse {
      bool accepted;
      std::string_view refusal_reason;
      std::string_view user_name;
      boost::uuids::uuid uuid;
   };
   LoginResponse login_player(std::string &user_name);

   void init_player(Connection &conn, boost::uuids::uuid id);

 private:
   PlayerManager &players;
   std::shared_ptr<minecpp::engine::PlayerService::Stub> player_service;
};

} // namespace Front
