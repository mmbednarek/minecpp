#pragma once
#include "Chunk.h"
#include <minecpp/game/Game.h>
#include <minecpp/game/World.h>
#include <queue>
#include <vector>

namespace minecpp::world {

class LightSystem final : public game::ILightSystem
{
 public:
   LightSystem(game::World &world, game::Notifier &notifier);
   static void regenerate_block_light(game::ISectionSlice &slice, game::SectionRange range);
   static void regenerate_sky_light(game::ISectionSlice &slice, game::SectionRange range,
                                    game::BlockPosition position, int strength);
   mb::emptyres regenerate_from_position(game::BlockPosition position, int strength);
   mb::emptyres add_light_source(game::BlockPosition position, int strength) override;
   static mb::emptyres recalculate_light_for_chunk(game::LightType type, Chunk &chunk);

 private:
   static game::SectionRange find_sections_affected_by_light_source(game::BlockPosition light_source_position,
                                                                    int strength);

   game::World &m_world;
   game::Notifier &m_notifier;

   static void update_light_internal(game::LightType type, game::IBlockContainer &container,
                                     const game::SectionRange &range, std::queue<game::LightSource> &queue);
};

}// namespace minecpp::world