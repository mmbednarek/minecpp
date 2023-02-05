#pragma once
#include "Chunk.h"
#include <minecpp/game/Game.h>
#include <minecpp/game/IBlockController.hpp>
#include <minecpp/game/World.h>
#include <queue>
#include <vector>

namespace minecpp::world {

enum class LightSpreadNodeType {
   Source,
   Lighten,
   Darken
};

struct LightSpreadNode
{
   game::BlockPosition position;
   game::LightValue value{};
   LightSpreadNodeType type{};
};

class LightSystem final : public game::ILightSystem
{
 public:
   explicit LightSystem(game::IBlockContainer &container);

   mb::emptyres add_light_source(game::BlockPosition position, game::LightValue value) override;
   mb::emptyres recalculate_light(game::LightType light_type, game::BlockPosition position) override;
   mb::emptyres reset_light(game::LightType light_type, game::BlockPosition position) override;


 private:
   game::LightValue get_propagated_value(game::BlockPosition source, game::Face direction, game::LightValue source_value);
   void propagate_value(game::LightType light_type, game::BlockPosition source, game::LightValue source_value,
                        LightSpreadNodeType type, std::queue<LightSpreadNode> &queue);

   mb::emptyres flood_light(game::LightType light_type, std::queue<LightSpreadNode> &queue);

   static game::SectionRange find_sections_affected_by_light_source(game::BlockPosition light_source_position,
                                                                    int strength);

   game::IBlockContainer &m_container;
};

}// namespace minecpp::world