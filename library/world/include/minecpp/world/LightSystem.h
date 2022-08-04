#pragma once
#include <vector>
#include <minecpp/game/Game.h>
#include <minecpp/game/World.h>

namespace minecpp::world {

class LightSystem final : public game::ILightSystem {
 public:
   LightSystem(game::World &mWorld, game::Notifier &mNotifier);
   static void regenerate_block_light(game::ISectionSlice& slice, game::SectionRange range);
   mb::emptyres regenerate_from_position(game::BlockPosition position, int strength);
   mb::emptyres add_light_source(game::BlockPosition position, int strength) override;

 private:
   static game::SectionRange find_sections_affected_by_light_source(game::BlockPosition light_source_position, int strength);

   game::World &m_world;
   game::Notifier &m_notifier;
};

}