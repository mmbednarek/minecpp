#pragma once
#include "entities.h"
#include "players.h"
#include "producer.h"
#include <game/difficulty.h>
#include <minepb/engine.grpc.pb.h>

namespace Engine {

class Service final : public minecpp::engine::PlayerService::Service {
   EntityManager &entities;
   PlayerManager &players;
   Producer &producer;

   int max_players = 10;
   Game::Difficulty difficulty = Game::Difficulty::Normal;
   int view_distance = 16;

 public:
   Service(EntityManager &entities, PlayerManager &players, Producer &producer);
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
};

} // namespace Engine
