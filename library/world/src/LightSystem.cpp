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

      if (not range.is_in_range(light.position.chunk_section_position()))
         continue;

      auto source_block = slice.get_light(LightType::Block, light.position);
      if (source_block.has_failed())
         continue;

      if (*source_block >= light.strength)
         continue;

      slice.set_light(LightType::Block, light.position, static_cast<std::uint8_t>(light.strength));

      auto passed_value = light.strength - 1;

      for (auto face : Face::Values) {
         auto position = light.position.neighbour_at(face);
         if (not range.is_in_range(position.chunk_section_position()))
            continue;

         auto neighbour_value = slice.get_light(LightType::Block, position);
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

}// namespace minecpp::world