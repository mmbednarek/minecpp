#include "service.h"
#include <boost/uuid/uuid.hpp>
#include <game/dimension.h>
#include <minenet/chat.h>
#include <minepb/events.pb.h>
#include <mineutils/uuid.h>
#include <spdlog/spdlog.h>

namespace Engine {

Service::~Service() = default;

Service::Service(EntityManager &entities, PlayerManager &players,
                 Producer &producer)
    : entities(entities), players(players), producer(producer) {}

grpc::Status
Service::AcceptPlayer(grpc::ServerContext *context,
                      const minecpp::engine::AcceptPlayerRequest *request,
                      minecpp::engine::AcceptPlayerResponse *response) {
   if (request->uuid().size() != 16) {
      return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT,
                          "invalid uuid length");
   }

   boost::uuids::uuid player_id{};
   Utils::decode_uuid(player_id, request->uuid().data());

   try {
      players.join_player(request->name(), player_id);
   } catch (std::runtime_error &e) {
      spdlog::error("could not join player: {}", e.what());
      return grpc::Status(grpc::StatusCode::INTERNAL, e.what());
   }

   auto &player = players.get_player(player_id);
   auto &player_entity = entities.get_entity(player.get_entity_id());

   response->set_state(
       minecpp::engine::AcceptPlayerResponse_PlayerAcceptState_ACCEPTED);
   response->set_node_id(0); // TODO: Put actual node id

   response->mutable_game_info()->set_max_players(max_players);
   response->mutable_game_info()->set_difficulty(
       static_cast<minecpp::game::Difficulty>(difficulty));
   response->mutable_game_info()->set_view_distance(view_distance);
   response->mutable_game_info()->set_world(minecpp::game::WorldType::Default);
   response->mutable_game_info()->set_seed(0);
   response->mutable_game_info()->set_dimension(
       Game::dimension_to_proto(player_entity.get_dimension()));
   response->mutable_game_info()->set_mode(
       static_cast<minecpp::game::GameMode>(player.get_game_mode()));

   response->mutable_player_data()->set_entity_id(player.get_entity_id());
   response->mutable_player_data()->set_game_mode(
       static_cast<minecpp::game::GameMode>(player.get_game_mode()));
   auto player_pos = player_entity.get_pos();
   response->mutable_player_data()->set_x(player_pos.x);
   response->mutable_player_data()->set_y(player_pos.y);
   response->mutable_player_data()->set_z(player_pos.z);
   response->mutable_player_data()->set_name(request->name());
   response->mutable_player_data()->set_yaw(player_entity.get_yaw());
   response->mutable_player_data()->set_pitch(player_entity.get_pitch());
   player.get_abilities().as_proto(
       response->mutable_player_data()->mutable_abilities());
   player.get_recipe_book().as_proto(
       response->mutable_player_data()->mutable_recipe_book());

   return grpc::Status();
}

grpc::Status Service::SetPlayerPosition(
    grpc::ServerContext *context,
    const minecpp::engine::SetPlayerPositionRequest *request,
    minecpp::engine::EmptyResponse *response) {
   boost::uuids::uuid player_id{};
   Utils::decode_uuid(player_id, request->uuid().data());

   try {
      auto &e = players.get_entity(player_id);
      e.set_pos(Utils::Vec3(request->x(), request->y(), request->z()));

      auto movement = e.process_movement();
      if (movement.x != 0 || movement.y != 0 || movement.z != 0) {
         spdlog::error(
             "sending movement package entity: {}, movement: {} {} {}",
             e.get_id(), movement.x, movement.y, movement.z);
         minecpp::events::EntityMove event;
         event.set_id(e.get_id());
         event.set_uuid(player_id.data, player_id.size());
         event.set_x(movement.x);
         event.set_y(movement.y);
         event.set_z(movement.z);
         event.set_yaw(e.get_yaw());
         event.set_pitch(e.get_pitch());
         producer.post(event);
      }
   } catch (std::runtime_error &e) {
      spdlog::error("error setting player pos: {}", e.what());
      return grpc::Status(grpc::StatusCode::NOT_FOUND, "player not found");
   }

   return grpc::Status();
}

grpc::Status Service::SetPlayerRotation(
    grpc::ServerContext *context,
    const minecpp::engine::SetPlayerRotationRequest *request,
    minecpp::engine::EmptyResponse *response) {
   boost::uuids::uuid player_id{};
   Utils::decode_uuid(player_id, request->uuid().data());

   try {
      auto &e = players.get_entity(player_id);
      e.set_rot(request->yaw(), request->pitch());

      minecpp::events::EntityLook event;
      event.set_id(e.get_id());
      event.set_uuid(player_id.data, player_id.size());
      event.set_yaw(e.get_yaw());
      event.set_pitch(e.get_pitch());
      producer.post(event);
   } catch (std::runtime_error &e) {
      spdlog::error("error setting player pos: {}", e.what());
      return grpc::Status(grpc::StatusCode::NOT_FOUND, "player not found");
   }

   return grpc::Status();
}

grpc::Status
Service::ChatMessage(grpc::ServerContext *context,
                     const minecpp::engine::ChatMessageRequest *request,
                     minecpp::engine::EmptyResponse *response) {
   boost::uuids::uuid player_id{};
   Utils::decode_uuid(player_id, request->uuid().data());
   auto &p = players.get_player(player_id);

   minecpp::events::Chat chat;
   chat.set_type(0);
   chat.set_message(
       MineNet::format_chat_message(p.get_player_name(), request->message()));
   producer.post(chat);

   return grpc::Status();
}

grpc::Status
Service::ListPlayers(grpc::ServerContext *context,
                     const minecpp::engine::EmptyRequest *request,
                     minecpp::engine::ListPlayersResponse *response) {
   players.for_each_player([response](Game::Player &p) {
      minecpp::engine::PlayerData data;
      auto id = p.get_id();
      data.set_uuid(id.data, id.size());
      auto name = p.get_player_name();
      data.set_name(name.data(), name.size());
      data.set_game_mode(
          static_cast<minecpp::game::GameMode>(data.game_mode()));
      response->mutable_list()->Add(
          std::forward<minecpp::engine::PlayerData>(data));
   });
   return grpc::Status();
}

grpc::Status Service::ListPlayerEntities(
    grpc::ServerContext *context, const minecpp::engine::EmptyRequest *request,
    minecpp::engine::ListPlayerEntitiesResponse *response) {
   players.for_each_player([this, response](Game::Player &p) {
      auto &e = entities.get_entity(p.get_entity_id());

      minecpp::engine::PlayerEntityData data;

      auto id = p.get_id();
      data.set_uuid(id.data, id.size());

      data.set_entity_id(p.get_entity_id());

      auto entity_pos = e.get_pos();
      data.set_x(entity_pos.x);
      data.set_y(entity_pos.y);
      data.set_z(entity_pos.z);

      data.set_yaw(e.get_yaw());
      data.set_pitch(e.get_pitch());

      response->mutable_list()->Add(
          std::forward<minecpp::engine::PlayerEntityData>(data));
   });
   return grpc::Status();
}

} // namespace Engine
