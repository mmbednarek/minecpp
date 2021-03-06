#include "service.h"
#include "protocol/protocol.h"
#include "server.h"
#include <boost/algorithm/string.hpp>
#include <boost/uuid/name_generator.hpp>
#include <fstream>
#include <grpcpp/grpcpp.h>
#include <minecpp/game/block/position.h>
#include <minecpp/game/dimension.h>
#include <minecpp/game/player.h>
#include <minecpp/util/time.h>
#include <minecpp/util/uuid.h>
#include <spdlog/spdlog.h>

namespace Front {

const char *internal_reason =
        R"({"extra":[{"color": "red", "bold": true, "text": "Disconnected"}, {"color":"gray", "text": " INTERNAL ERROR"}], "text": ""})";

Service::Service(Config &conf, Engine::Client::Provider &engine_provider, ChunkService chunk_service)
    : engine_provider(engine_provider), chunk_service(std::move(chunk_service)) {
   std::ifstream recipe_st;
   recipe_st.open(conf.recipe_path);
   if (!recipe_st.is_open()) {
      throw std::runtime_error("could not open recipe file");
   }
   recipe_st.seekg(0, std::ios::end);
   cached_recipes_size = recipe_st.tellg();
   recipe_st.seekg(0, std::ios::beg);
   cached_recipes = new char[cached_recipes_size];
   recipe_st.read(cached_recipes, cached_recipes_size);

   std::ifstream tags_st;
   tags_st.open(conf.tags_path);
   if (!tags_st.is_open()) {
      throw std::runtime_error("could not open recipe file");
   }
   tags_st.seekg(0, std::ios::end);
   cached_tags_size = tags_st.tellg();
   tags_st.seekg(0, std::ios::beg);
   cached_tags = new char[cached_tags_size];
   tags_st.read(cached_tags, cached_tags_size);
}

Service::~Service() { delete[] cached_recipes; }

Service::LoginResponse Service::login_player(std::string &user_name) {
   // TODO: Encryption authentication etc.
   boost::uuids::name_generator gen(player_uuid_namespace);

   return Service::LoginResponse{.accepted = true, .user_name = user_name, .id = gen(user_name)};
}

minecpp::network::message::Raw get_command_list();

void Service::init_player(const std::shared_ptr<Connection> &conn, uuid id, std::string_view name) {
   using namespace minecpp::network::message;

   conn->set_state(Protocol::State::Play);

   grpc::ClientContext ctx;
   minecpp::engine::AcceptPlayerResponse res;
   minecpp::engine::AcceptPlayerRequest req;
   req.set_name(std::string(name));
   req.set_uuid(id.data, id.size());

   auto &engine = engine_provider.get_random_service();
   conn->set_service_id(engine.id);
   conn->set_uuid(id);

   auto status = engine.service->AcceptPlayer(&ctx, req, &res);
   if (!status.ok()) {
      spdlog::error("could not join player {}.", status.error_message());
      send_and_disconnect(conn, Disconnect{
                                        .reason = internal_reason,
                                });
      return;
   }

   std::stringstream dimension_codec;
   minecpp::nbt::Writer dimension_codec_writer(dimension_codec);
   minecpp::game::write_dimension_codec(dimension_codec_writer);

   std::stringstream current_dimension;
   minecpp::nbt::Writer current_dimension_writer(current_dimension);
   minecpp::game::write_dimension_type(current_dimension_writer);

   send(conn, JoinGame{
                      .player_id = static_cast<uint32_t>(res.player_data().entity_id()),
                      .game_mode = static_cast<uint8_t>(res.game_info().mode()),
                      .available_dimensions{"overworld", "the_nether", "the_end"},
                      .dimension_codec = dimension_codec.str(),
                      .dimension_type = current_dimension.str(),
                      .world_name = "some_world",
                      .seed = res.game_info().seed(),
                      .max_players = static_cast<uint8_t>(res.game_info().max_players()),
                      .view_distance = static_cast<uint32_t>(res.game_info().view_distance()),
                      .reduced_debug_info = res.game_info().reduced_debug_info(),
                      .immediate_respawn = res.game_info().do_immediate_respawn(),
              });

   send(conn, ServerBrand{"minecpp"});

   send(conn, Difficulty{.difficulty = static_cast<uint8_t>(res.game_info().difficulty()), .locked = false});

   minecpp::game::Player::Abilities abilities;
   abilities.from_proto(res.player_data().abilities());

   send(conn, PlayerAbilities{
                      .flags = static_cast<uint8_t>(abilities.flags()),
                      .fly_speed = abilities.fly_speed,
                      .walk_speed = abilities.walk_speed,
              });

   /*
   send(conn, Raw{
                  .size = cached_recipes_size,
                  .data = cached_recipes,
              });

   send(conn, Raw{
                  .size = cached_tags_size,
                  .data = cached_tags,
              });
              */

   send(conn, EntityStatus{
                      .entity_id = static_cast<uint32_t>(res.player_data().entity_id()),
                      .opcode = 0x18,
              });

   //   send(conn, get_command_list());

   send(conn, RecipeBook{
                      .state = Init,
                      .gui_open = res.player_data().recipe_book().gui_open(),
                      .filtering_craftable = res.player_data().recipe_book().filtering_craftable(),
                      .furnace_gui_open = res.player_data().recipe_book().furnace_gui_open(),
                      .furnace_filtering_craftable = res.player_data().recipe_book().furnace_filtering_craftable(),
              });

   send(conn, PlayerPositionLook{
                      .x = res.player_data().x(),
                      .y = res.player_data().y(),
                      .z = res.player_data().z(),
                      .yaw = res.player_data().yaw(),
                      .pitch = res.player_data().pitch(),
                      .flags = 0,
                      .tp_id = 0,
              });

   grpc::ClientContext ctx2;
   minecpp::engine::EmptyRequest empty;
   minecpp::engine::ListPlayersResponse player_list;
   status = engine.service->ListPlayers(&ctx2, empty, &player_list);
   if (!status.ok()) {
      spdlog::error("could not list players {}.", status.error_message());
      send_and_disconnect(conn, Disconnect{
                                        .reason = internal_reason,
                                });
      return;
   }

   for (auto const &p : player_list.list()) {
      uuid p_id{};
      minecpp::util::decode_uuid(p_id, p.uuid().data());
      send(conn, AddPlayer{
                         .id = p_id,
                         .name = p.name(),
                         .game_mode = static_cast<uint8_t>(p.game_mode()),
                         .ping = 0x00,
                 });
   }

   spdlog::info("{} has joined the game", name);

   grpc::ClientContext ctx3;
   minecpp::engine::ListPlayerEntitiesResponse player_entities;
   status = engine.service->ListPlayerEntities(&ctx3, empty, &player_entities);
   if (!status.ok()) {
      spdlog::error("could not list players {}.", status.error_message());
      send_and_disconnect(conn, Disconnect{
                                        .reason = internal_reason,
                                });
      return;
   }

   for (auto const &e : player_entities.list()) {
      uuid e_id{};
      minecpp::util::decode_uuid(e_id, e.uuid().data());
      if (e_id == id) {
         continue;
      }
      send(conn, SpawnPlayer{
                         .entity_id = e.entity_id(),
                         .id = e_id,
                         .x = e.x(),
                         .y = e.y(),
                         .z = e.z(),
                         .yaw = e.yaw(),
                         .pitch = e.pitch(),
                 });
   }

   grpc::ClientContext ctx4;
   minecpp::engine::LoadInitialChunksRequest load_chunks_req;
   minecpp::engine::EmptyResponse empty_res;
   load_chunks_req.set_uuid(id.data, id.size());
   engine.service->LoadInitialChunks(&ctx4, load_chunks_req, &empty_res);
}

void Service::on_player_disconnect(uuid engine_id, uuid player_id) {
   minecpp::engine::RemovePlayerRequest req;
   req.set_uuid(player_id.data, player_id.size());
   grpc::ClientContext ctx;
   minecpp::engine::EmptyResponse res;
   auto status = engine_provider.get_service_by_id(engine_id)->RemovePlayer(&ctx, req, &res);
   if (!status.ok()) {
      spdlog::error("could not remove player: {}", status.error_message());
      return;
   }
}

void Service::on_message(uuid engine_id, uuid player_id, minecpp::network::message::ClientSettings msg) {
   spdlog::info("client language: {}", msg.lang);
}

void Service::on_message(uuid engine_id, uuid player_id, minecpp::network::message::PlayerPosition msg) {
   char uuid[17];
   minecpp::util::encode_uuid(uuid, player_id);

   grpc::ClientContext ctx;
   minecpp::engine::SetPlayerPositionRequest pos;
   pos.set_uuid(uuid);
   pos.set_x(msg.x);
   pos.set_y(msg.y);
   pos.set_z(msg.z);

   minecpp::engine::EmptyResponse res;
   auto status = engine_provider.get_service_by_id(engine_id)->SetPlayerPosition(&ctx, pos, &res);
   if (!status.ok()) {
      spdlog::error("could not set player position: {}", status.error_message());
      return;
   }
}

void Service::on_message(uuid engine_id, uuid player_id, minecpp::network::message::PlayerPositionRotation msg) {
   char uuid[17];
   minecpp::util::encode_uuid(uuid, player_id);

   grpc::ClientContext ctx;
   minecpp::engine::SetPlayerPositionRequest pos;
   pos.set_uuid(uuid);
   pos.set_x(msg.x);
   pos.set_y(msg.y);
   pos.set_z(msg.z);

   minecpp::engine::EmptyResponse res;
   auto status = engine_provider.get_service_by_id(engine_id)->SetPlayerPosition(&ctx, pos, &res);
   if (!status.ok()) {
      spdlog::error("could not set player position: {}", status.error_message());
      return;
   }

   grpc::ClientContext ctx_rot;
   minecpp::engine::SetPlayerRotationRequest rot;
   rot.set_uuid(uuid);
   rot.set_yaw(msg.yaw);
   rot.set_pitch(msg.pitch);

   status = engine_provider.get_service_by_id(engine_id)->SetPlayerRotation(&ctx_rot, rot, &res);
   if (!status.ok()) {
      spdlog::error("could not set player rotation: {}", status.error_message());
      return;
   }
}

void Service::on_message(uuid engine_id, uuid player_id, minecpp::network::message::PlayerRotation msg) {
   char uuid[17];
   minecpp::util::encode_uuid(uuid, player_id);
   grpc::ClientContext ctx_rot;
   minecpp::engine::SetPlayerRotationRequest rot;
   rot.set_uuid(uuid);
   rot.set_yaw(msg.yaw);
   rot.set_pitch(msg.pitch);

   minecpp::engine::EmptyResponse res;
   auto status = engine_provider.get_service_by_id(engine_id)->SetPlayerRotation(&ctx_rot, rot, &res);
   if (!status.ok()) {
      spdlog::error("could not set player rotation: {}", status.error_message());
      return;
   }
}
void Service::on_message(uuid engine_id, uuid player_id, minecpp::network::message::ChatMessage msg) {
   char uuid[17];
   minecpp::util::encode_uuid(uuid, player_id);
   grpc::ClientContext ctx_rot;
   minecpp::engine::ChatMessageRequest chat;
   chat.set_uuid(uuid);
   chat.set_message(msg.message);

   minecpp::engine::EmptyResponse res;
   auto status = engine_provider.get_service_by_id(engine_id)->ChatMessage(&ctx_rot, chat, &res);
   if (!status.ok()) {
      spdlog::error("could not send chat message: {}", status.error_message());
      return;
   }
}

void Service::on_message(uuid engine_id, uuid player_id, minecpp::network::message::PlayerDigging msg) {
   minecpp::game::block::Position pos(msg.position);

   if (msg.action == minecpp::network::message::DiggingAction::StartDestroyBlock) {
      minecpp::engine::DestroyBlockRequest req;
      req.set_uuid(player_id.data, player_id.size());
      req.set_x(pos.x);
      req.set_y(pos.y);
      req.set_z(pos.z);
      grpc::ClientContext ctx;
      minecpp::engine::EmptyResponse res;
      auto status = engine_provider.get_service_by_id(engine_id)->DestroyBlock(&ctx, req, &res);
      if (!status.ok()) {
         spdlog::error("could not destroy block: {}", status.error_message());
         return;
      }
   }
}
void Service::on_message(uuid engine_id, uuid player_id, minecpp::network::message::KeepAliveClient msg) {

   minecpp::engine::UpdatePingRequest req;
   req.set_uuid(player_id.data, player_id.size());
   req.set_ping(minecpp::util::now_milis() - msg.time);
   grpc::ClientContext ctx;
   minecpp::engine::EmptyResponse res;
   auto status = engine_provider.get_service_by_id(engine_id)->UpdatePing(&ctx, req, &res);
   if (!status.ok()) {
      spdlog::error("could not update ping: {}", status.error_message());
      return;
   }
}
void Service::on_message(uuid engine_id, uuid player_id, minecpp::network::message::AnimateHandClient msg) {
   minecpp::engine::AnimateHandRequest req;
   req.set_uuid(player_id.data, player_id.size());
   req.set_hand(static_cast<int>(msg.hand));
   grpc::ClientContext ctx;
   minecpp::engine::EmptyResponse res;
   auto status = engine_provider.get_service_by_id(engine_id)->AnimateHand(&ctx, req, &res);
   if (!status.ok()) {
      spdlog::error("could not animate hand: {}", status.error_message());
      return;
   }
}

const char command_list[]{
        0x11, 0x14, 0x00, 0x09, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x05, 0x01, 0x0a, 0x04, 0x68, 0x65,
        0x6c, 0x70, 0x05, 0x01, 0x0b, 0x04, 0x6c, 0x69, 0x73, 0x74, 0x01, 0x01, 0x0c, 0x02, 0x6d, 0x65, 0x01, 0x01, 0x0d,
        0x03, 0x6d, 0x73, 0x67, 0x01, 0x01, 0x0e, 0x07, 0x74, 0x65, 0x61, 0x6d, 0x6d, 0x73, 0x67, 0x09, 0x00, 0x04, 0x04,
        0x74, 0x65, 0x6c, 0x6c, 0x09, 0x00, 0x05, 0x02, 0x74, 0x6d, 0x01, 0x01, 0x0f, 0x07, 0x74, 0x72, 0x69, 0x67, 0x67,
        0x65, 0x72, 0x09, 0x00, 0x04, 0x01, 0x77, 0x06, 0x00, 0x07, 0x63, 0x6f, 0x6d, 0x6d, 0x61, 0x6e, 0x64, 0x10, 0x62,
        0x72, 0x69, 0x67, 0x61, 0x64, 0x69, 0x65, 0x72, 0x3a, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x02, 0x05, 0x00, 0x05,
        0x75, 0x75, 0x69, 0x64, 0x73, 0x06, 0x00, 0x06, 0x61, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x10, 0x62, 0x72, 0x69, 0x67,
        0x61, 0x64, 0x69, 0x65, 0x72, 0x3a, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x02, 0x02, 0x01, 0x10, 0x07, 0x74, 0x61,
        0x72, 0x67, 0x65, 0x74, 0x73, 0x10, 0x6d, 0x69, 0x6e, 0x65, 0x63, 0x72, 0x61, 0x66, 0x74, 0x3a, 0x65, 0x6e, 0x74,
        0x69, 0x74, 0x79, 0x02, 0x06, 0x00, 0x07, 0x6d, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65, 0x11, 0x6d, 0x69, 0x6e, 0x65,
        0x63, 0x72, 0x61, 0x66, 0x74, 0x3a, 0x6d, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65, 0x16, 0x02, 0x11, 0x12, 0x09, 0x6f,
        0x62, 0x6a, 0x65, 0x63, 0x74, 0x69, 0x76, 0x65, 0x13, 0x6d, 0x69, 0x6e, 0x65, 0x63, 0x72, 0x61, 0x66, 0x74, 0x3a,
        0x6f, 0x62, 0x6a, 0x65, 0x63, 0x74, 0x69, 0x76, 0x65, 0x14, 0x6d, 0x69, 0x6e, 0x65, 0x63, 0x72, 0x61, 0x66, 0x74,
        0x3a, 0x61, 0x73, 0x6b, 0x5f, 0x73, 0x65, 0x72, 0x76, 0x65, 0x72, 0x06, 0x00, 0x07, 0x6d, 0x65, 0x73, 0x73, 0x61,
        0x67, 0x65, 0x11, 0x6d, 0x69, 0x6e, 0x65, 0x63, 0x72, 0x61, 0x66, 0x74, 0x3a, 0x6d, 0x65, 0x73, 0x73, 0x61, 0x67,
        0x65, 0x01, 0x01, 0x13, 0x03, 0x61, 0x64, 0x64, 0x01, 0x01, 0x13, 0x03, 0x73, 0x65, 0x74, 0x06, 0x00, 0x05, 0x76,
        0x61, 0x6c, 0x75, 0x65, 0x11, 0x62, 0x72, 0x69, 0x67, 0x61, 0x64, 0x69, 0x65, 0x72, 0x3a, 0x69, 0x6e, 0x74, 0x65,
        0x67, 0x65, 0x72, 0x00, 0x00};

minecpp::network::message::Raw get_command_list() {
   return minecpp::network::message::Raw{
           .size = sizeof(command_list),
           .data = command_list,
   };
}

}// namespace Front
