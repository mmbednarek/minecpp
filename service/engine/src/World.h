#pragma once
#include "Dispatcher.h"
#include "Entities.h"
#include "Players.h"
#include <boost/uuid/uuid.hpp>
#include <mb/result.h>
#include <minecpp/controller/BlockManager.h>
#include <minecpp/game/World.h>
#include <minecpp/proto/service/chunk_storage/v1/ChunkStorage.grpc.pb.h>
#include <minecpp/world/LightSystem.h>

namespace minecpp::service::engine {

using boost::uuids::uuid;
using minecpp::game::ChunkPosition;

class ChunkSystem;
class JobSystem;

class World : public minecpp::game::World
{

 public:
   World(uuid engine_id, ChunkSystem &chunk_system, JobSystem &job_system, Dispatcher &dispatcher,
         PlayerManager &player_manager, EntityManager &entity_manager,
         controller::BlockManager &block_controller);

   game::player::Provider &players() override;
   EntityManager &entities() override;
   minecpp::game::Notifier &notifier() override;
   mb::result<mb::empty> add_refs(game::PlayerId player, std::vector<game::ChunkPosition> refs) override;
   mb::result<mb::empty> free_refs(game::PlayerId player, std::vector<game::ChunkPosition> refs) override;
   mb::result<int> height_at(int x, int z) override;
   mb::result<mb::empty> set_block_no_notify(const game::BlockPosition &pos, game::BlockStateId state);
   mb::result<mb::empty> set_block(const game::BlockPosition &pos, game::BlockStateId state) override;
   mb::result<game::BlockStateId> get_block(const game::BlockPosition &pos) override;
   mb::result<game::LightValue> get_light(game::LightType light_type,
                                          const game::BlockPosition &pos) override;
   mb::emptyres set_light(game::LightType light_type, const game::BlockPosition &pos,
                          game::LightValue level) override;
   mb::result<std::unique_ptr<game::ISectionSlice>> get_slice(game::SectionRange range) override;
   mb::emptyres apply_slice(game::ISectionSlice &slice) override;
   game::ILightSystem &light_system() override;
   mb::emptyres recalculate_light(game::LightType light_type, const game::BlockPosition &pos) override;
   mb::emptyres send_chunk_to_player(game::PlayerId player_id, const game::ChunkPosition &position) override;

 private:
   void notify_neighbours(game::BlockPosition position, game::BlockStateId state);

   ChunkSystem &m_chunk_system;
   JobSystem &m_job_system;
   Dispatcher &m_dispatcher;
   PlayerManager &m_player_manager;
   EntityManager &m_entity_manager;
   controller::BlockManager &m_block_controller;
   uuid m_engine_id;
   world::LightSystem m_light_system;
};

}// namespace minecpp::service::engine
