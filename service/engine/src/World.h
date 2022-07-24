#pragma once
#include "Dispatcher.h"
#include "Entities.h"
#include "Players.h"
#include <boost/uuid/uuid.hpp>
#include <mb/result.h>
#include <minecpp/controller/BlockManager.h>
#include <minecpp/game/World.h>
#include <minecpp/proto/service/chunk_storage/v1/ChunkStorage.grpc.pb.h>

namespace minecpp::service::engine {

using ChunkService = minecpp::proto::service::chunk_storage::v1::ChunkStorage::Stub;

using boost::uuids::uuid;
using minecpp::game::ChunkPosition;

class World : public minecpp::game::World
{
   ChunkService &service;
   Dispatcher &m_dispatcher;
   PlayerManager &m_player_manager;
   EntityManager &m_entity_manager;
   controller::BlockManager &m_block_controller;
   uuid engine_id;

 public:
   World(uuid engine_id, ChunkService &service, Dispatcher &dispatcher, PlayerManager &player_manager,
         EntityManager &entity_manager, controller::BlockManager &block_controller);

   game::player::Provider &players() override;
   EntityManager &entities() override;
   minecpp::game::Notifier &notifier() override;
   mb::result<mb::empty> add_refs(game::PlayerId player, std::vector<game::ChunkPosition> refs) override;
   mb::result<mb::empty> free_refs(game::PlayerId player, std::vector<game::ChunkPosition> refs) override;
   mb::result<int> height_at(int x, int z) override;
   mb::result<mb::empty> set_block_no_notify(const game::BlockPosition &pos, game::BlockStateId state);
   mb::result<mb::empty> set_block(const game::BlockPosition &pos, game::BlockStateId state) override;
   mb::result<game::BlockStateId> get_block(const game::BlockPosition &pos) override;
   mb::emptyres recalculate_light(game::LightType light_type, const game::BlockPosition &pos) override;
   mb::result<game::LightLevel> get_light(game::LightType light_type, const game::BlockPosition &pos) override;
   mb::emptyres set_light(game::LightType light_type, const game::BlockPosition &pos, game::LightLevel level) override;

 private:
   void notify_neighbours(game::BlockPosition position, game::BlockStateId state);
};

}// namespace minecpp::service::engine
