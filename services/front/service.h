#pragma once
#include "../engine/client/provider.h"
#include "config.h"
#include "connection.h"
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

typedef std::shared_ptr<minecpp::chunk_storage::ChunkStorage::Stub>
    ChunkService;

class Server;
using boost::uuids::uuid;

class Service {
   boost::random::mt19937 rand;
   Engine::Client::Provider &engine_provider;

   ChunkService chunk_service;

   char *cached_recipes = nullptr;
   std::size_t cached_recipes_size;
   char *cached_tags = nullptr;
   std::size_t cached_tags_size;

   uuid player_uuid_namespace{
       .data{0xe3, 0x35, 0xd4, 0xb4, 0x8d, 0x91, 0x4c, 0x5b, 0x8a, 0x7c, 0x23,
             0x08, 0xf3, 0x0e, 0x29, 0x52},
   };

 public:
   explicit Service(Config &conf, Engine::Client::Provider &engine_provider,
                    ChunkService chunk_service);
   ~Service();

   struct LoginResponse {
      bool accepted;
      std::string_view refusal_reason;
      std::string_view user_name;
      uuid uuid;
   };
   LoginResponse login_player(std::string &user_name);

   void init_player(const std::shared_ptr<Connection> &conn, uuid id,
                    std::string_view name);

   void on_player_disconnect(uuid engine_id, uuid player_id);

   void on_message(uuid engine_id, uuid player_id,
                   MineNet::Message::ClientSettings msg);
   void on_message(uuid engine_id, uuid player_id,
                   MineNet::Message::PlayerPosition msg);
   void on_message(uuid engine_id, uuid player_id,
                   MineNet::Message::PlayerPositionRotation msg);
   void on_message(uuid engine_id, uuid player_id,
                   MineNet::Message::PlayerRotation msg);
   void on_message(uuid engine_id, uuid player_id,
                   MineNet::Message::ChatMessage msg);
   void on_message(uuid engine_id, uuid player_id,
                   MineNet::Message::PlayerDigging msg);
   void on_message(uuid engine_id, uuid player_id,
                   MineNet::Message::KeepAliveClient msg);
   void on_message(uuid engine_id, uuid player_id,
                   MineNet::Message::AnimateHandClient msg);
};

} // namespace Front
