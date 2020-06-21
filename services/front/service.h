#pragma once
#include "config.h"
#include "connection.h"
#include "players.h"
#include "protocol/play_handler.h"
#include <boost/random.hpp>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <minenet/msg/serverbound.h>
#include <minepb/chunk.pb.h>
#include <minepb/chunk_storage.grpc.pb.h>
#include <minepb/engine.grpc.pb.h>
#include <minepb/engine.pb.h>

namespace Front {

typedef std::shared_ptr<minecpp::engine::PlayerService::Stub>
    EnginePlayerService;
typedef std::shared_ptr<grpc::Channel> EngineChannel;
typedef std::shared_ptr<minecpp::chunk_storage::ChunkStorage::Stub>
    ChunkService;

class Server;

class Service {
   PlayerManager players;

   boost::random::mt19937 rand;

   EnginePlayerService player_service;
   ChunkService chunk_service;

   char *cached_recipes = nullptr;
   std::size_t cached_recipes_size;
   char *cached_tags = nullptr;
   std::size_t cached_tags_size;
 public:
   explicit Service(Config &conf);
   ~Service();

   struct LoginResponse {
      bool accepted;
      std::string_view refusal_reason;
      std::string_view user_name;
      boost::uuids::uuid uuid;
   };
   LoginResponse login_player(std::string &user_name);

   void init_player(Connection &conn, boost::uuids::uuid id);
   EnginePlayerService &get_player_service();

   void on_player_disconnect(boost::uuids::uuid player_id);

   void on_message(boost::uuids::uuid player_id, MineNet::Message::ClientSettings msg);
   void on_message(boost::uuids::uuid player_id, MineNet::Message::PlayerPosition msg);
   void on_message(boost::uuids::uuid player_id, MineNet::Message::PlayerPositionRotation msg);
   void on_message(boost::uuids::uuid player_id, MineNet::Message::PlayerRotation msg);
   void on_message(boost::uuids::uuid player_id, MineNet::Message::ChatMessage msg);
   void on_message(boost::uuids::uuid player_id, MineNet::Message::PlayerDigging msg);

 private:
   void load_chunk(Connection &conn, int x, int z);
};

} // namespace Front
