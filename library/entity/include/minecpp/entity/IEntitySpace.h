#pragma once
#include <minecpp/game/Game.h>
#include <minecpp/math/Vector3.h>
#include <optional>

namespace minecpp::entity {

class IEntitySpace
{
 public:
   virtual ~IEntitySpace() = default;

   virtual void register_entity(game::EntityId entity_id, math::Vector3 position, math::Vector3 extent) = 0;
   virtual void update_position(game::EntityId entity_id, math::Vector3 old_position,
                                math::Vector3 new_position, math::Vector3 extent)                       = 0;
   virtual std::vector<game::EntityId> list_entities_in(math::Vector3 min, math::Vector3 max)           = 0;
   [[nodiscard]] virtual std::optional<game::EntityId> find_nearest(math::Vector3 position)             = 0;
};
}// namespace minecpp::entity