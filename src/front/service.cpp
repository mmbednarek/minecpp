#include "service.h"
#include "protocol/play_client.h"
#include "protocol/protocol.h"
#include <boost/algorithm/string.hpp>
#include <grpcpp/client_context.h>

namespace Front {

Service::Service(PlayerManager &players,
                 std::shared_ptr<grpc::Channel> &engine_chan)
    : players(players),
      player_service(minecpp::engine::PlayerService::NewStub(engine_chan)) {}

Service::LoginResponse Service::login_player(std::string &user_name) {
   auto player = new Player(user_name);

   try {
      players.add_player(player);
   } catch (PlayerException &e) {
      return Service::LoginResponse{
          .accepted = false,
          .refusal_reason = "invalid player data",
      };
   }

   // TODO: Encryption authentication etc.

   return Service::LoginResponse{.accepted = true,
                                 .user_name = player->name(),
                                 .uuid = player->user_id()};
}

void Service::init_player(Front::Connection &conn, boost::uuids::uuid id) {
   conn.set_state(Protocol::State::Play);
   auto player = players.get_player(id);

   grpc::ClientContext ctx;

   minecpp::engine::AcceptPlayerResponse res;
   minecpp::engine::AcceptPlayerRequest req;
   req.set_name(player.name());
   req.set_uuid(player.user_id_str());
   player_service->AcceptPlayer(&ctx, req, &res);

   Protocol::PlayClient cli(conn);

   auto wld_type = minecpp::engine::WorldType_Name(res.game_info().world());
   boost::algorithm::to_lower(wld_type);

   cli.join_game(Protocol::Message::JoinGame{
       .player_id = res.player_id(),
       .game_mode = static_cast<uint8_t>(res.game_info().mode()),
       .dimension = static_cast<uint32_t>(res.game_info().dimension()),
       .seed = res.game_info().seed(),
       .max_players = static_cast<uint8_t>(res.game_info().max_players()),
       .world_type = wld_type,
       .view_distance = static_cast<uint32_t>(res.game_info().view_distance()),
       .reduced_debug_info = res.game_info().reduced_debug_info(),
       .immediate_respawn = res.game_info().do_immediate_respawn(),
   });
   cli.server_brand("minecraft:brand.minecpp");
   cli.difficulty(res.game_info().difficulty(), false);
   cli.player_abilities(Protocol::Message::PlayerAbilities{
       .flags = 0,
       .fly_speed = 0.5f,
       .walk_speed = 0.1f, // TODO: Load actual abilities
   });
}

} // namespace Front
