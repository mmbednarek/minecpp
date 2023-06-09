#include "World.h"
#include "ChunkSystem.h"
#include "job/ChangeBlock.h"
#include "job/ChunkIsComplete.h"
#include "JobSystem.h"
#include <minecpp/entity/Aliases.hpp>
#include <minecpp/entity/component/Health.h>
#include <minecpp/entity/component/Player.h>
#include <minecpp/entity/EntitySystem.h>
#include <minecpp/entity/factory/Item.h>
#include <minecpp/repository/Item.h>
#include <minecpp/util/Uuid.h>
#include <minecpp/world/BlockState.h>
#include <minecpp/world/SectionSlice.h>
#include <utility>

using minecpp::game::Face;
using minecpp::service::engine::job::ChangeBlock;
using minecpp::service::engine::job::ChunkIsComplete;

namespace minecpp::service::engine {

using ItemFactory = entity::factory::Item;

template<typename TFunction>
void when_chunk_is_complete(ChunkSystem &chunk_system, JobSystem &job_system,
                            const game::ChunkPosition &position, TFunction &&function)
{
   if (chunk_system.chunk_state_at(position) == world::ChunkState::COMPLETE) {
      function(chunk_system.chunk_at(position));
   } else {
      job_system.when<job::ChunkIsComplete>(chunk_system, position).run([&chunk_system, position, function] {
         auto *chunk = chunk_system.chunk_at(position);
         assert(chunk);
         function(chunk);
      });
   }
}

#define ACCESS_CHUNK_AT(position, ...) \
   when_chunk_is_complete(m_chunk_system, m_job_system, position, __VA_ARGS__)

World::World(ChunkSystem &chunk_system, JobSystem &job_system, Dispatcher &dispatcher,
             PlayerManager &player_manager, entity::EntitySystem &entity_system,
             controller::BlockManager &block_controller) :
    m_chunk_system(chunk_system),
    m_job_system(job_system),
    m_dispatcher(dispatcher),
    m_player_manager(player_manager),
    m_entity_system(entity_system),
    m_block_controller(block_controller),
    m_light_system(*this),
    m_general_purpose_random(2356)
{
}

minecpp::game::IDispatcher &World::dispatcher()
{
   return m_dispatcher;
}

mb::result<mb::empty> World::add_refs(game::PlayerId player_id, std::vector<game::ChunkPosition> refs)
{
   for (auto const &position : refs) {
      ACCESS_CHUNK_AT(position,
                      [player_id](world::Chunk *chunk) { chunk->add_player_reference(player_id); });

      // TODO: Send reference to storage
   }
   return mb::ok;
}

mb::result<mb::empty> World::free_refs(game::PlayerId player_id, std::vector<game::ChunkPosition> refs)
{
   for (auto const &position : refs) {
      ACCESS_CHUNK_AT(position,
                      [player_id](world::Chunk *chunk) { chunk->remove_player_reference(player_id); });

      // TODO: Send reference removal to storage
   }
   return mb::ok;
}

mb::result<int> World::height_at(int x, int z)
{
   auto *chunk = m_chunk_system.chunk_at({x, z});
   if (chunk == nullptr) {
      return mb::error("chunk is not loaded");
   }
   return chunk->height_at(game::HeightType::WorldSurface, {x, 0, z});
}

mb::result<mb::empty> World::set_block_no_notify(const game::BlockPosition &pos, game::BlockStateId state)
{
   m_job_system.when<ChunkIsComplete>(m_chunk_system, pos.chunk_position())
           .run_job<ChangeBlock>(*this, m_chunk_system, pos, state);
   m_dispatcher.update_block(pos, state);
   return mb::ok;
}

mb::result<mb::empty> World::set_block_at(const game::BlockPosition &pos, game::BlockStateId state)
{
   if (auto res = set_block_no_notify(pos, state); res.has_failed()) {
      return std::move(res.err());
   }

   notify_neighbours(pos, state);
   return mb::ok;
}

mb::result<game::BlockStateId> World::block_at(const game::BlockPosition &pos)
{
   auto *chunk = m_chunk_system.chunk_at(pos.chunk_position());
   if (chunk == nullptr) {
      return mb::error("chunk is not loaded");
   }
   return chunk->block_at(pos);
}

game::player::Provider &World::players()
{
   return m_player_manager;
}

game::IEntitySystem &World::entity_system()
{
   return m_entity_system;
}

void World::notify_neighbours(game::BlockPosition position, game::BlockStateId state)
{
   for (Face face : game::Face::Values) {
      auto neighbour_pos = position.neighbour_at(face);

      auto old_neighbour_state = block_at(neighbour_pos);
      if (old_neighbour_state.has_failed())
         continue;

      auto new_neighbour_state = m_block_controller.on_neighbour_change(*this, *old_neighbour_state, state,
                                                                        neighbour_pos, face.opposite_face());
      if (not new_neighbour_state.has_value())
         continue;

      if (*new_neighbour_state != *old_neighbour_state) {
         set_block_no_notify(neighbour_pos, *new_neighbour_state);
      }
   }
}

mb::result<game::LightValue> World::light_value_at(game::LightType light_type, const game::BlockPosition &pos)
{
   auto *chunk = m_chunk_system.chunk_at(pos.chunk_position());
   if (chunk == nullptr) {
      return mb::error("chunk is not loaded");
   }
   return chunk->light_value_at(light_type, pos);
}

mb::emptyres World::set_light_value_at(game::LightType light_type, const game::BlockPosition &pos,
                                       game::LightValue level)
{
   ACCESS_CHUNK_AT(pos.chunk_position(), [light_type, pos, level](world::Chunk *chunk) {
      chunk->set_light_value_at(light_type, pos, level);
   });
   return mb::ok;
}

mb::result<std::unique_ptr<game::ISectionSlice>> World::get_slice(game::SectionRange /*range*/)
{
   return mb::error("not implemented");
}

mb::emptyres World::apply_slice(game::ISectionSlice & /*slice*/)
{
   return mb::error("not implemented");
}

game::ILightSystem &World::light_system()
{
   return m_light_system;
}

mb::emptyres World::recalculate_light(game::LightType /*light_type*/, const game::BlockPosition & /*pos*/)
{
   return mb::error("not implemented");
}

mb::emptyres World::send_chunk_to_player(game::PlayerId player_id, const game::ChunkPosition &position,
                                         bool is_initial)
{
   ACCESS_CHUNK_AT(position, [this, player_id, is_initial](world::Chunk *chunk) {
      m_dispatcher.send_chunk(player_id, chunk, is_initial);
   });
   return mb::ok;
}

void World::tick(double delta_time)
{
   m_entity_system.tick_entities(*this, delta_time);
}

bool World::is_movement_blocked_at(const math::Vector3 &position)
{
   auto block_position = game::BlockPosition::from_vector3(position);

   auto block_state_id = this->block_at(block_position);
   if (block_state_id.has_failed())
      return false;

   auto block_state = world::BlockState(*block_state_id);

   return block_state.does_block_movement() && block_state.solid_faces() == game::FaceMask::All;
}

void World::kill_entity(game::EntityId id)
{
   m_dispatcher.remove_entity(id);

   auto entity = m_entity_system.entity(id);
   entity.on_killed(*this);

   if (entity.has_component<PlayerComponent>()) {
      // Don't actually remove the entity just detach from the world
      m_player_manager.mark_player_as_dead(entity.component<PlayerComponent>().id());
      m_entity_system.detach_entity(id);
   } else {
      m_entity_system.destroy_entity(id);
   }
}

void World::destroy_block(const game::BlockPosition &position)
{
   auto block_state_id = this->block_at(position);
   if (block_state_id.has_failed())
      return;
   if (*block_state_id == DEFAULT_BLOCK_STATE(Air))
      return;

   this->set_block_at(position, DEFAULT_BLOCK_STATE(Air));

   world::BlockState block_state{*block_state_id};
   auto item_id = repository::Item::the().find_id_by_tag(block_state.block_tag());
   if (not item_id.ok())
      return;

   auto item_position = position.to_vector3() + math::Vector3{0.5, 0.75, 0.5};
   this->spawn<ItemFactory>(item_position, game::ItemSlot{*item_id, 1}, m_general_purpose_random);
}

void World::apply_damage_or_kill_entity(game::EntityId id, const game::Damage &damage)
{
   auto entity = m_entity_system.entity(id);
   if (not entity.has_component<HealthComponent>()) {
      this->kill_entity(id);
      return;
   }

   entity.component<HealthComponent>().apply_damage(*this, damage);
}

}// namespace minecpp::service::engine
