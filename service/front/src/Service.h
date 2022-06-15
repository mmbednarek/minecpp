#pragma once
#include "Config.h"
#include "Connection.h"
#include "protocol/PlayHandler.h"
#include <boost/random.hpp>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <minecpp/network/message/Serverbound.h>
#include <minecpp/player/Id.h>
#include <minecpp/proto/chunk/v1/Chunk.pb.h>
#include <minecpp/proto/service/chunk_storage/v1/ChunkStorage.grpc.pb.h>
#include <minecpp/proto/service/engine/v1/Engine.grpc.pb.h>
#include <minecpp/service/engine/Api.h>

namespace minecpp::service::front {

typedef std::shared_ptr<minecpp::proto::service::chunk_storage::v1::ChunkStorage::Stub> ChunkService;

class Server;
using boost::uuids::uuid;


constexpr boost::uuids::uuid g_player_uuid_namespace{
        .data{0xe3, 0x35, 0xd4, 0xb4, 0x8d, 0x91, 0x4c, 0x5b, 0x8a, 0x7c, 0x23, 0x08, 0xf3, 0x0e, 0x29, 0x52},
};

class Service
{
   boost::random::mt19937 rand;
   engine::Stream *m_stream;

   ChunkService m_chunk_service;

   char *cached_recipes = nullptr;
   std::size_t cached_recipes_size;
   char *cached_tags = nullptr;
   std::size_t cached_tags_size;

 public:
   explicit Service(Config &conf, ChunkService chunk_service);
   ~Service();

   constexpr void set_stream(engine::Stream *stream)
   {
      m_stream = stream;
   }

   struct LoginResponse
   {
      bool accepted;
      std::string_view refusal_reason;
      std::string_view user_name;
      uuid id;
   };

   LoginResponse login_player(std::string &user_name);

   void init_player(const std::shared_ptr<Connection> &conn, uuid id, std::string_view name);

   void on_player_disconnect(uuid engine_id, player::Id player_id);

   void on_message(uuid engine_id, player::Id player_id, const minecpp::network::message::ChatCommand &msg);
   void on_message(uuid engine_id, player::Id player_id, minecpp::network::message::ChatMessage msg);
   void on_message(uuid engine_id, player::Id player_id, minecpp::network::message::ClientSettings msg);
   void on_message(uuid engine_id, player::Id player_id, minecpp::network::message::PlayerPosition msg);
   void on_message(uuid engine_id, player::Id player_id,
                   minecpp::network::message::PlayerPositionRotation msg);
   void on_message(uuid engine_id, player::Id player_id, minecpp::network::message::PlayerRotation msg);
   void on_message(uuid engine_id, player::Id player_id, minecpp::network::message::PlayerDigging msg);
   void on_message(uuid engine_id, player::Id player_id, minecpp::network::message::KeepAliveClient msg);
   void on_message(uuid engine_id, player::Id player_id, minecpp::network::message::AnimateHandClient msg);
   void on_message(uuid engine_id, player::Id player_id, minecpp::network::message::PlayerBlockPlacement msg);
   void on_message(uuid engine_id, player::Id player_id, minecpp::network::message::ClickWindow msg);
   void on_message(uuid engine_id, player::Id player_id, minecpp::network::message::HeldItemChange msg);
   void on_message(uuid engine_id, player::Id player_id, minecpp::network::message::PluginMessage msg);
};

}// namespace minecpp::service::front
