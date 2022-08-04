#include <minecpp/world/LightSystem.h>
#include <queue>
#include <spdlog/spdlog.h>

namespace minecpp::world {

using game::Face;
using game::LightType;

LightSystem::LightSystem(game::World &mWorld, game::Notifier &mNotifier) :
    m_world(mWorld),
    m_notifier(mNotifier)
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

   while (not queue.empty()) {
      auto light = queue.front();
      queue.pop();

      std::array<mb::result<game::LightLevel>, 6> neighbour_light_levels_results{
              slice.get_light(LightType::Block, light.position.neighbour_at(Face::Bottom)),
              slice.get_light(LightType::Block, light.position.neighbour_at(Face::Top)),
              slice.get_light(LightType::Block, light.position.neighbour_at(Face::North)),
              slice.get_light(LightType::Block, light.position.neighbour_at(Face::South)),
              slice.get_light(LightType::Block, light.position.neighbour_at(Face::West)),
              slice.get_light(LightType::Block, light.position.neighbour_at(Face::East)),
      };

      std::array<game::LightLevel, 6> neighbour_light_levels{};
      auto res = mb::unpack(neighbour_light_levels_results.begin(), neighbour_light_levels_results.end(),
                            neighbour_light_levels.begin());
      if (res != nullptr) {
         continue;
      }

      slice.set_light(LightType::Block, light.position, static_cast<game::LightLevel>(light.strength));

      if (light.strength < 3)
         continue;

      for (auto face : game::Face::Values) {
         if (light.strength <= neighbour_light_levels[static_cast<std::size_t>(face)])
            continue;

         queue.emplace(light.position.neighbour_at(face), light.strength - 1);
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

}// namespace minecpp::world