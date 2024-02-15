#pragma once

#include "Dispatcher.h"
#include "PlayerManager.h"

#include "minecpp/controller/BlockManager.h"
#include "minecpp/game/IWorld.hpp"
#include "minecpp/random/JavaRandom.h"
#include "minecpp/signal/Delegate.hpp"
#include "minecpp/world/LightSystem.h"

#include <boost/uuid/uuid.hpp>
#include <mb/result.h>

namespace minecpp::entity {
class EntitySystem;
}

namespace minecpp::service::engine {

using boost::uuids::uuid;
using minecpp::game::ChunkPosition;

class ChunkSystem;
class JobSystem;

class World : public minecpp::game::IWorld
{
 public:
   World(ChunkSystem &chunk_system, JobSystem &job_system, Dispatcher &dispatcher,
         PlayerManager &player_manager, entity::EntitySystem &entity_system,
         controller::BlockManager &block_controller);
   void destroy_block(const game::BlockPosition &position) override;

   game::player::Provider &players() override;
   game::IEntitySystem &entity_system() override;
   game::IDispatcher &dispatcher() override;

   mb::result<mb::empty> add_refs(game::PlayerId player, std::vector<game::ChunkPosition> refs) override;
   mb::result<mb::empty> free_refs(game::PlayerId player, std::vector<game::ChunkPosition> refs) override;
   mb::result<int> height_at(int x, int z) override;
   mb::result<mb::empty> set_block_no_notify(const game::BlockPosition &block_position,
                                             game::BlockStateId state);
   mb::result<mb::empty> set_block_at(const game::BlockPosition &pos, game::BlockStateId state) override;
   mb::result<game::BlockStateId> block_at(const game::BlockPosition &pos) override;
   mb::result<game::LightValue> light_value_at(game::LightType light_type,
                                               const game::BlockPosition &pos) override;
   mb::emptyres set_light_value_at(game::LightType light_type, const game::BlockPosition &pos,
                                   game::LightValue level) override;
   mb::result<std::unique_ptr<game::ISectionSlice>> get_slice(game::SectionRange range) override;
   mb::emptyres apply_slice(game::ISectionSlice &slice) override;
   game::ILightSystem &light_system() override;
   mb::emptyres recalculate_light(game::LightType light_type, const game::BlockPosition &pos) override;
   mb::emptyres send_chunk_to_player(game::PlayerId player_id, const game::ChunkPosition &position,
                                     bool is_initial) override;
   void tick(double delta_time);
   bool is_movement_blocked_at(const math::Vector3 &position) override;
   void kill_entity(game::EntityId id) override;
   void apply_damage_or_kill_entity(game::EntityId id, const game::Damage &damage) override;
   mb::result<game::Entity> player_entity(game::PlayerId player_id) override;

 private:
   void notify_neighbours(game::BlockPosition position, game::BlockStateId state);

   ChunkSystem &m_chunk_system;
   JobSystem &m_job_system;
   Dispatcher &m_dispatcher;
   PlayerManager &m_player_manager;
   entity::EntitySystem &m_entity_system;
   controller::BlockManager &m_block_controller;
   world::LightSystem m_light_system;
   random::JavaRandom m_general_purpose_random;
};

}// namespace minecpp::service::engine
