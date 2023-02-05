#include "World.h"
#include "ChunkSystem.h"
#include "job/ChangeBlock.h"
#include "job/ChunkIsComplete.h"
#include "JobSystem.h"
#include <minecpp/util/Uuid.h>
#include <minecpp/world/SectionSlice.h>
#include <utility>

using minecpp::game::Face;

namespace minecpp::service::engine {

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

World::World(uuid engine_id, ChunkSystem &chunk_system, JobSystem &job_system, Dispatcher &dispatcher,
             PlayerManager &player_manager, EntityManager &entity_manager,
             controller::BlockManager &block_controller) :
    m_chunk_system(chunk_system),
    m_job_system(job_system),
    m_dispatcher(dispatcher),
    m_player_manager(player_manager),
    m_entity_manager(entity_manager),
    m_block_controller(block_controller),
    m_engine_id(engine_id),
    m_light_system(*this)
{
}

minecpp::game::Notifier &World::notifier()
{
   return m_dispatcher;
}

mb::result<mb::empty> World::add_refs(game::PlayerId player_id, std::vector<game::ChunkPosition> refs)
{
   for (auto const &position : refs) {
      ACCESS_CHUNK_AT(position,
                      [this, player_id](world::Chunk *chunk) { chunk->add_ref(m_engine_id, player_id); });

      // TODO: Send reference to storage
   }
   return mb::ok;
}

mb::result<mb::empty> World::free_refs(game::PlayerId player_id, std::vector<game::ChunkPosition> refs)
{
   for (auto const &position : refs) {
      ACCESS_CHUNK_AT(position, [player_id](world::Chunk *chunk) { chunk->free_ref(player_id); });

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
   m_job_system.when<job::ChunkIsComplete>(m_chunk_system, pos.chunk_position())
           .run_job<job::ChangeBlock>(m_light_system, m_chunk_system, pos, state);
   m_dispatcher.update_block(pos, state);
   return mb::ok;
}

mb::result<mb::empty> World::set_block(const game::BlockPosition &pos, game::BlockStateId state)
{
   if (auto res = set_block_no_notify(pos, state); res.has_failed()) {
      return std::move(res.err());
   }

   notify_neighbours(pos, state);
   return mb::ok;
}

mb::result<game::BlockStateId> World::get_block(const game::BlockPosition &pos)
{
   auto *chunk = m_chunk_system.chunk_at(pos.chunk_position());
   if (chunk == nullptr) {
      return mb::error("chunk is not loaded");
   }
   return chunk->get_block(pos);
}

game::player::Provider &World::players()
{
   return m_player_manager;
}

EntityManager &World::entities()
{
   return m_entity_manager;
}

void World::notify_neighbours(game::BlockPosition position, game::BlockStateId state)
{
   for (Face face : game::Face::Values) {
      auto neighbour_pos = position.neighbour_at(face);

      auto old_neighbour_state = get_block(neighbour_pos);
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

mb::result<game::LightValue> World::get_light(game::LightType light_type, const game::BlockPosition &pos)
{
   auto *chunk = m_chunk_system.chunk_at(pos.chunk_position());
   if (chunk == nullptr) {
      return mb::error("chunk is not loaded");
   }
   return chunk->get_light(light_type, pos);
}

mb::emptyres World::set_light(game::LightType light_type, const game::BlockPosition &pos,
                              game::LightValue level)
{
   ACCESS_CHUNK_AT(pos.chunk_position(), [light_type, pos, level](world::Chunk *chunk) {
      chunk->set_light(light_type, pos, level);
   });
   return mb::ok;
}

mb::result<std::unique_ptr<game::ISectionSlice>> World::get_slice(game::SectionRange range)
{
   return mb::error("not implemented");
}

mb::emptyres World::apply_slice(game::ISectionSlice &slice)
{
   return mb::error("not implemented");
}

game::ILightSystem &World::light_system()
{
   return m_light_system;
}

mb::emptyres World::recalculate_light(game::LightType light_type, const game::BlockPosition &pos)
{
   return mb::error("not implemented");
}

mb::emptyres World::send_chunk_to_player(game::PlayerId player_id, const game::ChunkPosition &position)
{
   ACCESS_CHUNK_AT(position,
                   [this, player_id](world::Chunk *chunk) { m_dispatcher.send_chunk(player_id, chunk); });
   return mb::ok;
}

}// namespace minecpp::service::engine
