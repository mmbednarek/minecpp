#include "play_handler.h"
#include "../connection.h"

namespace Front::Protocol {

PlayHandler::PlayHandler(std::shared_ptr<grpc::Channel> &engine_chan) : player_service(minecpp::engine::PlayerService::NewStub(engine_chan)) {}

void PlayHandler::init_player(Front::Packet::Writer &w, Front::Player &p) {
   w.connection().set_state(State::Play);

   grpc::ClientContext ctx;

   minecpp::engine::AcceptPlayerRequest req;
   minecpp::engine::AcceptPlayerResponse res;

   req.set_name(p.name());
   req.set_uuid(p.user_id());
   player_service->AcceptPlayer(&ctx, req, &res);

   res.game_info();
}

void PlayHandler::handle(Connection &conn, Packet::Reader &r) {}

} // namespace Front::Protocol
