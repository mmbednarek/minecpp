#pragma once
#include "Config.h"
#include "Connection.h"
#include "protocol/PlayHandler.h"

#include "minecpp/game/player/Id.h"
#include "minecpp/net/play/Serverbound.schema.h"
#include "minecpp/service/engine/Api.h"

#include <boost/random.hpp>

namespace minecpp::service::front {

class Server;
using boost::uuids::uuid;


constexpr boost::uuids::uuid g_player_uuid_namespace{
        .data{0xe3, 0x35, 0xd4, 0xb4, 0x8d, 0x91, 0x4c, 0x5b, 0x8a, 0x7c, 0x23, 0x08, 0xf3, 0x0e, 0x29, 0x52},
};

class Service
{
 public:
   explicit Service(Config &conf);

   struct LoginResponse
   {
      bool accepted;
      std::string_view refusal_reason;
      std::string_view user_name;
      uuid id;
   };

   static LoginResponse login_player(std::string &user_name);

   void init_player(Connection &connection, uuid id, std::string_view name);
   void on_player_disconnect(uuid engine_id, game::PlayerId player_id);
   void set_client(engine::Client *stream);
   void send(container::BufferView message, game::PlayerId id);

 private:
   engine::Client *m_client{};
};

}// namespace minecpp::service::front
