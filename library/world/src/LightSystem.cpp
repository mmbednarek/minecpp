#include <minecpp/repository/State.h>
#include <minecpp/world/BlockState.h>
#include <minecpp/world/LightSystem.h>
#include <queue>
#include <spdlog/spdlog.h>

namespace minecpp::world {

using game::Face;
using game::LightType;

LightSystem::LightSystem(game::IBlockContainer &container) :
    m_container{container}
{
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

mb::emptyres LightSystem::add_light_source(game::BlockPosition position, game::LightValue value)
{
   std::queue<LightSpreadNode> queue;
   queue.push(LightSpreadNode{position, value, LightSpreadNodeType::Source});

   spdlog::debug("light-system: calculating light initial value is {}", value);
   this->flood_light(game::LightType::Block, queue);

   return mb::ok;
}

mb::emptyres LightSystem::recalculate_light(game::LightType light_type, game::BlockPosition position,
                                            game::FaceMask solid_faces)
{
   game::LightValue max_light_value{0};
   for (auto face_value : game::Face::Values) {
      game::Face face{face_value};
      if (solid_faces & face)
         continue;// don't accept light where the face is solid

      auto neighbour_pos = position.neighbour_at(face);

      auto light_value = m_container.get_light(light_type, neighbour_pos);
      if (light_value.has_failed())
         continue;

      if (*light_value > max_light_value)
         max_light_value = *light_value;
   }

   if (max_light_value == 0)
      return mb::ok;

   std::queue<LightSpreadNode> queue;
   queue.push(LightSpreadNode{position, static_cast<game::LightValue>(max_light_value - 1),
                              LightSpreadNodeType::Lighten});

   spdlog::debug("light-system: calculating light initial value is {}", max_light_value - 1);
   this->flood_light(light_type, queue);

   return mb::ok;
}

mb::emptyres LightSystem::reset_light(game::LightType light_type, game::BlockPosition position)
{
   auto light_value = m_container.get_light(light_type, position);
   if (light_value.has_failed())
      return std::move(light_value.err());

   if (*light_value == 0)
      return mb::ok;

   spdlog::debug("light-system: resetting light from value {}", *light_value);

   std::queue<LightSpreadNode> queue;
   queue.push(LightSpreadNode{position, *light_value, LightSpreadNodeType::Darken});
   this->flood_light(light_type, queue);

   return mb::ok;
}

mb::emptyres LightSystem::flood_light(game::LightType light_type, std::queue<LightSpreadNode> &queue)
{
   /*
    There are 2 modes of flooding the light:

      1. Lighten - A light source is forwarded by decreasing
                   the light value by one through opaque blocks.

      2. Darken  - When a light is obstructed by a non-opaque block,
                   the areas need to darken. We pass the original light
                   value just like in lighten, if the actual light value matches
                   the passed one we can darken it. If it doesn't, we re-propagate
                   that light value that doesn't match, because it comes from
                   a different light source.
    */

   while (not queue.empty()) {
      auto node = queue.front();
      queue.pop();

      auto source_value = m_container.get_light(light_type, node.position);
      if (source_value.has_failed())
         continue;

      if (node.type == LightSpreadNodeType::Darken) {
         if (node.value != *source_value)
            continue;
         m_container.set_light(light_type, node.position, 0);
      } else if (node.value > *source_value) {
         m_container.set_light(light_type, node.position, node.value);
      } else {
         continue;
      }

      spdlog::debug("light-system: queue-size = {}, strength = {}", queue.size(), node.value);
      this->propagate_value(light_type, node.position, node.value, node.type, queue);
   }

   return mb::ok;
}

game::LightValue LightSystem::get_propagated_value(game::BlockPosition source, game::Face direction,
                                                   game::LightValue source_value)
{
   auto destination        = source.neighbour_at(direction);
   auto dst_block_state_id = m_container.get_block(destination);
   if (dst_block_state_id.has_failed()) {
      spdlog::debug("light-system: cannot get destination block");
      return 0;
   }

   BlockState dst_block_state(*dst_block_state_id);
   if (dst_block_state.solid_faces() & direction.opposite_face()) {
      spdlog::debug("light-system: the face is solid");
      return 0;
   }

   return static_cast<game::LightValue>(std::max(0, source_value - 1));
}

void LightSystem::propagate_value(game::LightType light_type, game::BlockPosition source,
                                  game::LightValue source_value, LightSpreadNodeType type,
                                  std::queue<LightSpreadNode> &queue)
{
   auto source_block_state_id = m_container.get_block(source);
   if (source_block_state_id.has_failed())
      return;

   // source light should be spread through solid faces.
   auto solid_faces = game::FaceMask::None;
   if (type != LightSpreadNodeType::Source) {
      BlockState source_block_state(*source_block_state_id);
      solid_faces = source_block_state.solid_faces();
   }

   for (auto face_value : game::Face::Values) {
      game::Face face{face_value};

      // Skip solid faces
      if (solid_faces & face)
         continue;

      auto neighbour      = source.neighbour_at(face);
      auto original_value = m_container.get_light(light_type, neighbour);
      if (original_value.has_failed())
         continue;

      auto target_value = this->get_propagated_value(source, face, source_value);
      if (target_value < 1)
         continue;

      //      spdlog::debug("light-system: spreading value {} to {}: original={}, darken={}", target_value,
      //                    face.to_string(), *original_value, type);

      if (type == LightSpreadNodeType::Darken) {
         if (target_value != *original_value) {
            // re-propagate the original value
            queue.push(LightSpreadNode{neighbour, *original_value, LightSpreadNodeType::Lighten});
            continue;
         }

         queue.push(LightSpreadNode{neighbour, target_value, LightSpreadNodeType::Darken});
         continue;
      }

      // Lighten
      if (target_value > *original_value) {
         queue.push(LightSpreadNode{neighbour, target_value, LightSpreadNodeType::Lighten});
      }
   }
}

}// namespace minecpp::world