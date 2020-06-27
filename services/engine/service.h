#pragma once
#include "entities.h"
#include "players.h"
#include "event_manager.h"
#include <game/difficulty.h>
#include <minepb/engine.grpc.pb.h>
#include <minepb/chunk_storage.grpc.pb.h>
#include <queue>

namespace Engine {

typedef std::shared_ptr<minecpp::chunk_storage::ChunkStorage::Stub>
    ChunkService;

class Service final : public minecpp::engine::PlayerService::Service {
   EntityManager &entities;
   PlayerManager &players;
   ChunkService chunk_storage;
   EventManager event_manager;

   int max_players = 10;
   Game::Difficulty difficulty = Game::Difficulty::Normal;
   int view_distance = 16;

 public:
   Service(EntityManager &entities, PlayerManager &players, std::string &chunk_store);
   ~Service() override;

   grpc::Status
   AcceptPlayer(grpc::ServerContext *context,
                const minecpp::engine::AcceptPlayerRequest *request,
                minecpp::engine::AcceptPlayerResponse *response) override;

   grpc::Status
   SetPlayerPosition(grpc::ServerContext *context,
                     const minecpp::engine::SetPlayerPositionRequest *request,
                     minecpp::engine::EmptyResponse *response) override;
   grpc::Status
   SetPlayerRotation(grpc::ServerContext *context,
                     const minecpp::engine::SetPlayerRotationRequest *request,
                     minecpp::engine::EmptyResponse *response) override;

   grpc::Status ChatMessage(grpc::ServerContext *context,
                            const minecpp::engine::ChatMessageRequest *request,
                            minecpp::engine::EmptyResponse *response) override;

   grpc::Status
   ListPlayers(grpc::ServerContext *context,
               const minecpp::engine::EmptyRequest *request,
               minecpp::engine::ListPlayersResponse *response) override;

   grpc::Status ListPlayerEntities(
       grpc::ServerContext *context,
       const minecpp::engine::EmptyRequest *request,
       minecpp::engine::ListPlayerEntitiesResponse *response) override;

   grpc::Status
   RemovePlayer(grpc::ServerContext *context,
                const minecpp::engine::RemovePlayerRequest *request,
                minecpp::engine::EmptyResponse *response) override;

   grpc::Status
   DestroyBlock(grpc::ServerContext *context,
                const minecpp::engine::DestroyBlockRequest *request,
                minecpp::engine::EmptyResponse *response) override;

   grpc::Status UpdatePing(grpc::ServerContext *context,
                           const minecpp::engine::UpdatePingRequest *request,
                           minecpp::engine::EmptyResponse *response) override;

   grpc::Status
   FetchEvents(grpc::ServerContext *context,
               const minecpp::engine::FetchEventsRequest *request,
               grpc::ServerWriter<::minecpp::engine::Event> *writer) override;

   grpc::Status
   AnimateHand(grpc::ServerContext *context,
               const minecpp::engine::AnimateHandRequest *request,
               minecpp::engine::EmptyResponse *response) override;
};

} // namespace Engine
