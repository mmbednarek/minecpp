#include "service.h"
#include <boost/uuid/uuid.hpp>
#include <game/blocks/position.h>
#include <game/dimension.h>
#include <grpcpp/create_channel.h>
#include <minenet/chat.h>
#include <minepb/events.pb.h>
#include <mineutils/uuid.h>
#include <spdlog/spdlog.h>

namespace Engine {

Service::~Service() = default;

Service::Service(EntityManager &entities, PlayerManager &players,
                 std::string &chunk_store)
    : entities(entities), players(players) {
   auto channel =
       grpc::CreateChannel(chunk_store, grpc::InsecureChannelCredentials());
   chunk_storage = minecpp::chunk_storage::ChunkStorage::NewStub(channel);
}

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
   response->set_area_id(0); // TODO: Put actual node id

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

   minecpp::events::AddPlayer add_player;
   add_player.set_uuid(player_id.data, player_id.size());
   add_player.set_name(request->name());
   add_player.set_ping(player.get_ping());
   event_manager.post(add_player);

   minecpp::events::SpawnPlayer spawn_player;
   spawn_player.set_uuid(player_id.data, player_id.size());
   spawn_player.set_id(player.get_entity_id());
   spawn_player.set_x(player_pos.x);
   spawn_player.set_y(player_pos.y);
   spawn_player.set_z(player_pos.z);
   spawn_player.set_yaw(player_entity.get_yaw());
   spawn_player.set_z(player_entity.get_pitch());
   event_manager.post(spawn_player);

   minecpp::events::Chat chat;
   chat.set_type(1);
   chat.set_message(MineNet::format_join_message(request->name()));
   event_manager.post(chat);

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
         minecpp::events::EntityMove event;
         event.set_id(e.get_id());
         event.set_uuid(player_id.data, player_id.size());
         event.set_x(movement.x);
         event.set_y(movement.y);
         event.set_z(movement.z);
         event.set_yaw(e.get_yaw());
         event.set_pitch(e.get_pitch());
         event_manager.post(event);
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
      event_manager.post(event);
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
   event_manager.post(chat);

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
      data.set_ping(p.get_ping());
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

grpc::Status
Service::RemovePlayer(grpc::ServerContext *context,
                      const minecpp::engine::RemovePlayerRequest *request,
                      minecpp::engine::EmptyResponse *response) {
   boost::uuids::uuid id{};
   Utils::decode_uuid(id, request->uuid().data());

   auto player = players.get_player(id);

   minecpp::events::Chat chat;
   chat.set_type(1);
   chat.set_message(MineNet::format_left_message(player.get_player_name()));
   event_manager.post(chat);

   minecpp::events::RemovePlayer remove_player;
   remove_player.set_uuid(request->uuid());
   remove_player.set_entity_id(player.get_entity_id());
   event_manager.post(remove_player);

   players.remove_player(id);
   return grpc::Status();
}
grpc::Status
Service::DestroyBlock(grpc::ServerContext *context,
                      const minecpp::engine::DestroyBlockRequest *request,
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

   Game::Block::Position pos(request->x(), request->y(), request->z());
   auto chunk_pos = pos.chunk_pos();

   minecpp::events::UpdateBlock update_block;
   update_block.set_chunk_x(chunk_pos.x);
   update_block.set_chunk_z(chunk_pos.z);
   update_block.set_offset(pos.offset());
   update_block.set_state(0);
   event_manager.post(update_block);

   return grpc::Status();
}
grpc::Status
Service::UpdatePing(grpc::ServerContext *context,
                    const minecpp::engine::UpdatePingRequest *request,
                    minecpp::engine::EmptyResponse *response) {
   boost::uuids::uuid id{};
   Utils::decode_uuid(id, request->uuid().data());
   auto player = players.get_player(id);
   player.set_ping(request->ping());
   return grpc::Status();
}

grpc::Status
Service::AnimateHand(grpc::ServerContext *context,
                     const minecpp::engine::AnimateHandRequest *request,
                     minecpp::engine::EmptyResponse *response) {
   boost::uuids::uuid id{};
   Utils::decode_uuid(id, request->uuid().data());
   auto player = players.get_player(id);

   minecpp::events::AnimateHand animate;
   animate.set_uuid(request->uuid());
   animate.set_entity_id(player.get_entity_id());
   animate.set_hand(request->hand());
   event_manager.post(animate);

   return grpc::Status();
}

grpc::Status
Service::FetchEvents(grpc::ServerContext *context,
                     const minecpp::engine::FetchEventsRequest *request,
                     grpc::ServerWriter<minecpp::engine::Event> *writer) {
   auto &queue = event_manager.create_queue(request->front_id());
   while (!context->IsCancelled()) {
      while (!queue.empty()) {
         writer->Write(queue.front());
         queue.pop();
      }
   }
   return grpc::Status();
}

} // namespace Engine
