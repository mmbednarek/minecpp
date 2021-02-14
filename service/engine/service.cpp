#include "service.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <grpcpp/create_channel.h>
#include <minecpp/chat/parser.h>
#include <minecpp/format/format.h>
#include <minecpp/game/block/position.h>
#include <minecpp/game/dimension.h>
#include <minecpp/network/chat.h>
#include <minecpp/util/grpc.h>
#include <minecpp/util/uuid.h>
#include <minepb/events.pb.h>
#include <spdlog/spdlog.h>
#include <utility>

namespace Engine {

Service::~Service() = default;

Service::Service(EntityManager &entities, PlayerManager &players, const ChunkService &chunk_store)
    : entities(entities), players(players), service_id(boost::uuids::random_generator()()), chunk_storage(chunk_store),
      dispatcher(event_manager), world(service_id, chunk_store, dispatcher) {}

grpc::Status Service::AcceptPlayer(grpc::ServerContext *context, const minecpp::engine::AcceptPlayerRequest *request,
                                   minecpp::engine::AcceptPlayerResponse *response) {
   auto player_id = MCPP_GRPC_TRY(minecpp::util::make_uuid(request->uuid()));

   MCPP_GRPC_TRY(players.join_player(world, request->name(), player_id));
   auto &player = MCPP_GRPC_TRY(players.get_player(player_id));
   auto &player_entity = MCPP_GRPC_TRY(entities.get_entity(player.get_entity_id()));
   auto player_pos = player_entity.get_pos();

   response->set_state(minecpp::engine::AcceptPlayerResponse_PlayerAcceptState_ACCEPTED);
   response->set_area_id(0);// TODO: Put actual node id

   response->mutable_game_info()->set_max_players(max_players);
   response->mutable_game_info()->set_difficulty(static_cast<minecpp::game::Difficulty>(difficulty));
   response->mutable_game_info()->set_view_distance(view_distance);
   response->mutable_game_info()->set_world(minecpp::game::WorldType::Default);
   response->mutable_game_info()->set_seed(0);
   response->mutable_game_info()->set_dimension(minecpp::game::dimension_to_proto(player_entity.get_dimension()));
   response->mutable_game_info()->set_mode(static_cast<minecpp::game::GameMode>(player.get_game_mode()));

   response->mutable_player_data()->set_entity_id(player.get_entity_id());
   response->mutable_player_data()->set_game_mode(static_cast<minecpp::game::GameMode>(player.get_game_mode()));
   response->mutable_player_data()->set_x(player_pos.x);
   response->mutable_player_data()->set_y(player_pos.y);
   response->mutable_player_data()->set_z(player_pos.z);
   response->mutable_player_data()->set_name(request->name());
   response->mutable_player_data()->set_yaw(player_entity.get_yaw());
   response->mutable_player_data()->set_pitch(player_entity.get_pitch());
   player.get_abilities().as_proto(response->mutable_player_data()->mutable_abilities());
   player.get_recipe_book().as_proto(response->mutable_player_data()->mutable_recipe_book());

   dispatcher.add_player(player_id, request->name(), player.get_ping());
   dispatcher.spawn_player(player_id, player.get_entity_id(), player_pos, player_entity.get_yaw(), player_entity.get_pitch());
   dispatcher.send_chat(1, minecpp::network::format_join_message(request->name()));

   return grpc::Status();
}

grpc::Status Service::SetPlayerPosition(grpc::ServerContext *context,
                                        const minecpp::engine::SetPlayerPositionRequest *request,
                                        minecpp::engine::EmptyResponse *response) {
   auto player_id = MCPP_GRPC_TRY(minecpp::util::make_uuid(request->uuid()));
   auto &player_entity = MCPP_GRPC_TRY(players.get_entity(player_id));
   auto player_pos = minecpp::util::Vec3(request->x(), request->y(), request->z());

   player_entity.set_pos(dispatcher, player_pos);
   MCPP_GRPC_TRY(players.get_player(player_id)).on_movement(world, player_pos);

   return grpc::Status();
}

grpc::Status Service::SetPlayerRotation(grpc::ServerContext *context,
                                        const minecpp::engine::SetPlayerRotationRequest *request,
                                        minecpp::engine::EmptyResponse *response) {
   auto player_id = MCPP_GRPC_TRY(minecpp::util::make_uuid(request->uuid()));

   auto &player_entity = MCPP_GRPC_TRY(players.get_entity(player_id));
   player_entity.set_rot(request->yaw(), request->pitch());
   dispatcher.entity_look(player_id, player_entity.get_id(), player_entity.get_yaw(), player_entity.get_pitch());

   return grpc::Status();
}

grpc::Status Service::ChatMessage(grpc::ServerContext *context, const minecpp::engine::ChatMessageRequest *request,
                                  minecpp::engine::EmptyResponse *response) {
   auto player_id = MCPP_GRPC_TRY(minecpp::util::make_uuid(request->uuid()));

   if (request->message().empty()) {
      return grpc::Status();
   }

   if (request->message()[0] == '/') {
      MCPP_GRPC_TRY(handle_command(player_id, request->message().substr(1)));
      return grpc::Status();
   }

   auto &p = MCPP_GRPC_TRY(players.get_player(player_id));
   spdlog::info("[{}] {}", p.get_player_name(), request->message());
   dispatcher.send_chat(0, minecpp::network::format_chat_message(p.get_player_name(), request->message()));
   return grpc::Status();
}

grpc::Status Service::ListPlayers(grpc::ServerContext *context, const minecpp::engine::EmptyRequest *request,
                                  minecpp::engine::ListPlayersResponse *response) {
   players.for_each_player([response](minecpp::game::Player &p) {
      minecpp::engine::PlayerData data;
      auto id = p.get_id();
      data.set_uuid(id.data, id.size());
      auto name = p.get_player_name();
      data.set_name(name.data(), name.size());
      data.set_ping(p.get_ping());
      data.set_game_mode(static_cast<minecpp::game::GameMode>(data.game_mode()));
      response->mutable_list()->Add(std::forward<minecpp::engine::PlayerData>(data));
   });
   return grpc::Status();
}

grpc::Status Service::ListPlayerEntities(grpc::ServerContext *context, const minecpp::engine::EmptyRequest *request,
                                         minecpp::engine::ListPlayerEntitiesResponse *response) {
   players.for_each_player([this, response](minecpp::game::Player &p) {
      auto id = p.get_id();

      auto player_entity_res = entities.get_entity(p.get_entity_id());
      if (!player_entity_res.ok()) {
         return;
      }
      auto &player_entity = player_entity_res.unwrap();
      auto entity_pos = player_entity.get_pos();

      minecpp::engine::PlayerEntityData data;
      data.set_uuid(id.data, id.size());
      data.set_entity_id(p.get_entity_id());
      data.set_x(entity_pos.x);
      data.set_y(entity_pos.y);
      data.set_z(entity_pos.z);
      data.set_yaw(player_entity.get_yaw());
      data.set_pitch(player_entity.get_pitch());

      response->mutable_list()->Add(std::forward<minecpp::engine::PlayerEntityData>(data));
   });
   return grpc::Status();
}

grpc::Status Service::RemovePlayer(grpc::ServerContext *context, const minecpp::engine::RemovePlayerRequest *request,
                                   minecpp::engine::EmptyResponse *response) {
   auto id = MCPP_GRPC_TRY(minecpp::util::make_uuid(request->uuid()));
   auto &player = MCPP_GRPC_TRY(players.get_player(id));

   dispatcher.send_chat(1, minecpp::network::format_left_message(player.get_player_name()));
   dispatcher.remove_player(id, player.get_entity_id());

   players.remove_player(id);

   return grpc::Status();
}
grpc::Status Service::DestroyBlock(grpc::ServerContext *context, const minecpp::engine::DestroyBlockRequest *request,
                                   minecpp::engine::EmptyResponse *response) {
   grpc::ClientContext ctx;
   minecpp::chunk_storage::SetBlockRequest set_block;
   set_block.set_x(request->x());
   set_block.set_y(request->y());
   set_block.set_z(request->z());
   set_block.set_state(0);
   minecpp::chunk_storage::EmptyResponse res;
   auto status = chunk_storage->SetBlock(&ctx, set_block, &res);
   if (!status.ok()) {
      spdlog::error("set block error: {}", status.error_message());
   }

   dispatcher.update_block(request->x(), request->y(), request->z(), 0);
   return grpc::Status();
}
grpc::Status Service::UpdatePing(grpc::ServerContext *context, const minecpp::engine::UpdatePingRequest *request,
                                 minecpp::engine::EmptyResponse *response) {
   boost::uuids::uuid id{};
   minecpp::util::decode_uuid(id, request->uuid().data());
   auto &player = MCPP_GRPC_TRY(players.get_player(id));
   player.set_ping(request->ping());
   return grpc::Status();
}

grpc::Status Service::AnimateHand(grpc::ServerContext *context, const minecpp::engine::AnimateHandRequest *request,
                                  minecpp::engine::EmptyResponse *response) {
   auto id = MCPP_GRPC_TRY(minecpp::util::make_uuid(request->uuid()));
   auto &player = MCPP_GRPC_TRY(players.get_player(id));
   dispatcher.animate_hand(id, player.get_entity_id(), request->hand());
   return grpc::Status();
}

grpc::Status Service::FetchEvents(grpc::ServerContext *context, const minecpp::engine::FetchEventsRequest *request,
                                  grpc::ServerWriter<minecpp::engine::Event> *writer) {
   auto &queue = event_manager.create_queue(request->front_id());
   while (!context->IsCancelled()) {
      writer->Write(queue.pop());
   }
   return grpc::Status();
}

grpc::Status Service::GetServiceId(grpc::ServerContext *context, const minecpp::engine::EmptyRequest *request,
                                   minecpp::engine::GetServiceIdResponse *response) {
   response->set_id(service_id.data, service_id.size());
   return grpc::Status();
}

grpc::Status Service::GetServiceStatus(grpc::ServerContext *context, const minecpp::engine::EmptyRequest *request,
                                       minecpp::engine::GetServiceStatusResponse *response) {
   response->set_players(players.player_count());
   return grpc::Status();
}

mb::result<mb::empty> Service::handle_command(uuid id, std::string cmd) {
   using minecpp::format::Color;

   auto tokens = minecpp::chat::lex(cmd);
   auto command = MB_TRY(minecpp::chat::parse(tokens));

   if (command.name == "info") {
      auto &player = MB_TRY(players.get_player(id));
      dispatcher.send_chat(0, minecpp::format::Builder()
                                      .text(Color::Yellow, player.get_player_name())
                                      .text(" (")
                                      .bold(Color::White, "id: ")
                                      .text(boost::uuids::to_string(id))
                                      .bold(Color::White, ", entity_id: ")
                                      .text(std::to_string(player.get_entity_id()))
                                      .bold(Color::White, ", engine: ")
                                      .text(boost::uuids::to_string(service_id))
                                      .text(")")
                                      .build());
   } else if (command.name == "height") {
      auto &entity = MB_TRY(players.get_entity(id));
      auto entity_pos = entity.get_pos();
      dispatcher.send_chat(0, minecpp::format::Builder()
                                      .bold(Color::White, "height: ")
                                      .text(std::to_string(world.height_at(entity_pos.x, entity_pos.z).unwrap(0)))
                                      .build());
   } else if (command.name == "setblock") {
      if (command.args.size() != 4) {
         dispatcher.send_chat(0, minecpp::format::Builder().text(Color::Red, "setblock requires 4 arguments").build());
         return mb::ok;
      }
      int x = std::get<int>(command.args[0]);
      int y = std::get<int>(command.args[1]);
      int z = std::get<int>(command.args[2]);
      int state = std::get<int>(command.args[3]);

      grpc::ClientContext ctx;
      minecpp::chunk_storage::SetBlockRequest set_block;
      set_block.set_x(x);
      set_block.set_y(y);
      set_block.set_z(z);
      set_block.set_state(state);
      minecpp::chunk_storage::EmptyResponse res;
      auto status = chunk_storage->SetBlock(&ctx, set_block, &res);
      if (!status.ok()) {
         return mb::error("could not set block");
      }

      dispatcher.update_block(x, y, z, state);
      dispatcher.send_chat(0, minecpp::format::Builder().text(Color::Blue, "updated block").build());
   } else {
      dispatcher.send_chat(0, minecpp::format::Builder().text(Color::Red, "invalid command").build());
   }

   return mb::ok;
}

grpc::Status Service::LoadInitialChunks(grpc::ServerContext *context,
                                        const minecpp::engine::LoadInitialChunksRequest *request,
                                        minecpp::engine::EmptyResponse *response) {
   auto id = MCPP_GRPC_TRY(minecpp::util::make_uuid(request->uuid()));
   auto &player = MCPP_GRPC_TRY(players.get_player(id));
   MCPP_GRPC_TRY(player.load_chunks(world));
   return grpc::Status();
}

}// namespace Engine
