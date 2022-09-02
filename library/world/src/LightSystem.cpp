#include <minecpp/repository/State.h>
#include <minecpp/world/LightSystem.h>
#include <queue>
#include <spdlog/spdlog.h>

namespace minecpp::world {

using game::Face;
using game::LightType;

LightSystem::LightSystem(game::World &world, game::Notifier &notifier) :
    m_world(world),
    m_notifier(notifier)
{
}

mb::emptyres LightSystem::regenerate_from_position(game::BlockPosition position, int strength)
{
   auto range = find_sections_affected_by_light_source(position, strength);
   auto area  = range.grow(1);
   auto slice = m_world.get_slice(area);
   if (slice.has_failed()) {
      return std::move(slice.err());
   }

   regenerate_block_light(*slice->get(), range);
   regenerate_sky_light(*slice->get(), range, position, strength);
   m_notifier.update_block_light(*slice->get(), range);
   m_world.apply_slice(*slice->get());
   return mb::ok;
}

void LightSystem::regenerate_block_light(game::ISectionSlice &slice, game::SectionRange range)
{
   std::queue<game::LightSource> queue;

   for (auto section_position : range) {
      auto &section = slice[section_position];

      for (const auto &light_source : section.light_sources()) {
         queue.emplace(light_source);
      }

      section.reset_light(LightType::Block);
   }

   update_light_internal(game::LightType::Block, slice, range, queue);
}


void LightSystem::regenerate_sky_light(game::ISectionSlice& slice, game::SectionRange range, game::BlockPosition position, int strength) {
   std::queue<game::LightSource> queue;
   queue.emplace(position, strength);
   update_light_internal(game::LightType::Sky, slice, range, queue);
}

void LightSystem::update_light_internal(game::LightType type, game::IBlockContainer &container,
                                        const game::SectionRange &range, std::queue<game::LightSource> &queue)
{
   while (not queue.empty()) {
      auto light = queue.front();
      queue.pop();

      if (not range.is_in_range(light.position.chunk_section_position()))
         continue;

      auto source_block = container.get_light(type, light.position);
      if (source_block.has_failed())
         continue;

      if (*source_block >= light.strength)
         continue;

      container.set_light(type, light.position, static_cast<mb::u8>(light.strength));

      auto passed_value = light.strength - 1;

      for (auto face : Face::Values) {
         auto position = light.position.neighbour_at(face);
         if (not range.is_in_range(position.chunk_section_position()))
            continue;

         auto block_state_id = container.get_block(position);
         if (block_state_id.has_failed())
            continue;

         if (repository::StateManager::the().is_solid((*block_state_id)))
            continue;

         auto neighbour_value = container.get_light(type, position);
         if (neighbour_value.has_failed())
            continue;

         if (*neighbour_value >= passed_value)
            continue;

         queue.emplace(position, passed_value);
      }
   }
}

game::SectionRange
LightSystem::find_sections_affected_by_light_source(game::BlockPosition light_source_position, int strength)
{
   game::BlockPosition min_pos{
           light_source_position.x - strength,
           light_source_position.y - strength,
           light_source_position.z - strength,
   };
   game::BlockPosition max_pos{
           light_source_position.x + strength,
           light_source_position.y + strength,
           light_source_position.z + strength,
   };

   return {min_pos.chunk_section_position(), max_pos.chunk_section_position()};
}

mb::emptyres LightSystem::add_light_source(game::BlockPosition position, int strength)
{
   auto range = find_sections_affected_by_light_source(position, strength);
   auto area  = range.grow(1);
   auto slice = m_world.get_slice(area);
   if (slice.has_failed()) {
      return std::move(slice.err());
   }

   spdlog::info("adding a light source");

   slice->get()
           ->
           operator[](position.chunk_section_position())
           .light_sources()
           .emplace_back(position, strength);

  regenerate_block_light(*slice->get(), range);
   m_notifier.update_block_light(*slice->get(), range);
   auto res = m_world.apply_slice(*slice->get());
   if (res.has_failed()) {
      spdlog::error("applying slice failed: {}", res.err()->msg());
   }

   return mb::ok;
}

mb::emptyres LightSystem::recalculate_light_for_chunk(game::LightType type, Chunk &chunk)
{
   auto &stateManager = repository::StateManager::the();

   std::queue<game::LightSource> sources;
   for (int y{chunk.minimum_y()}; y < chunk.maximum_y(); ++y) {
      for (int x{0}; x < game::g_chunk_width; ++x) {
         for (int z{0}; z < game::g_chunk_depth; ++z) {
            game::BlockPosition pos{x, y, z};
            if (stateManager.is_solid(chunk.get_block(pos).unwrap(0))) {
               continue;
            }

            auto target = chunk.get_light(type, pos);
            if (target.has_failed())
               continue;

            auto max_value = 0;

            for (auto face : game::Face::Values) {
               auto neighbour = pos.neighbour_at(face);

               if (stateManager.is_solid(chunk.get_block(neighbour).unwrap(0)))
                  continue;

               auto neighbour_value = chunk.get_light(type, neighbour);
               if (neighbour_value.has_failed())
                  continue;

               if (max_value < *neighbour_value)
                  max_value = *neighbour_value;
            }

            if ((max_value - 1) > *target) {
               sources.emplace(chunk.pos().block_at(pos.x, pos.y, pos.z), max_value - 1);
            }
         }
      }
   }

   update_light_internal(type, chunk,
                         {
                                 {chunk.pos(),  0},
                                 {chunk.pos(), 15}
   },
                         sources);

   return mb::ok;
}

}// namespace minecpp::world