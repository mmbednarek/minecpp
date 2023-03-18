#include "ChangeBlock.h"

#include <minecpp/entity/Aliases.hpp>
#include <minecpp/entity/component/Location.h>
#include <minecpp/game/IEntitySystem.hpp>
#include <minecpp/world/BlockState.h>

namespace minecpp::service::engine::job {

ChangeBlock::ChangeBlock(game::IWorld &world, world::IChunkSystem &chunk_system,
                         const game::BlockPosition &position, game::BlockStateId target_state_id) :
    m_world(world),
    m_chunk_system(chunk_system),
    m_position(position),
    m_target_state_id(target_state_id)
{
}

void ChangeBlock::run()
{
   auto chunk = m_chunk_system.chunk_at(m_position.chunk_position());
   assert(chunk);// job-system guarantees the chunk is present.

   auto source_state_id = chunk->get_block(m_position);
   assert(source_state_id.ok());

   if (*source_state_id == m_target_state_id)
      return;// no changes

   world::BlockState source_state{*source_state_id};
   world::BlockState target_state{m_target_state_id};

   /*
    Before we set a new block we need to decide if we need reset the previous light
    value of that block. We calculate the difference of solid faces. We there are some
    new solid faces, we need reset the previous light value there, also if the luminance
    of the target block is lower than the source block we should first reset the previous
    luminance and then apply new one (but that's just for the block light).
    */
   auto reset_light = (target_state.solid_faces() - source_state.solid_faces()) != game::FaceMask::None;
   if (reset_light) {
      m_world.light_system().reset_light(game::LightType::Block, m_position);
      m_world.light_system().reset_light(game::LightType::Sky, m_position);
   } else if (target_state.luminance() < source_state.luminance()) {
      m_world.light_system().reset_light(game::LightType::Block, m_position);
   }

   chunk->set_block(m_position, m_target_state_id);

   /*
    The reverse situation here. If there are some new opaque faces recalculate light.
    If the luminance is greater add a light source.

    FIXME: What if light is passed from other source is greater than the luminance light?
    TODO: Handle edge case.
    */
   auto new_opaque_faces = (source_state.solid_faces() - target_state.solid_faces()) != game::FaceMask::None;
   auto recalculate_light =
           new_opaque_faces or (reset_light and target_state.solid_faces() != game::FaceMask::All);

   if (target_state.luminance() > source_state.luminance()) {
      m_world.light_system().add_light_source(m_position, target_state.luminance());
   } else if (recalculate_light) {
      m_world.light_system().recalculate_light(game::LightType::Block, m_position,
                                               target_state.solid_faces());
   }

   if (recalculate_light) {
      m_world.light_system().recalculate_light(game::LightType::Sky, m_position, target_state.solid_faces());
   }

   if (not target_state.does_block_movement()) {
      const auto real_position = m_position.to_vec3();
      auto entities_above      = m_world.entity_system().list_entities_intersecting_with(
              real_position - math::Vector3{0.5, 0.5, 0.5}, real_position + math::Vector3{1.5, 1.5, 1.5});

      for (auto entity_id : entities_above) {
         auto entity = m_world.entity_system().entity(entity_id);
         if (not entity.has_component<LocationComponent>())
            continue;

         auto &location = entity.component<LocationComponent>();
         location.set_is_on_ground(m_world, entity, false);
      }
   }

   m_chunk_system.save_chunk_at(m_position.chunk_position());
}

}// namespace minecpp::service::engine::job
