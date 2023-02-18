#ifndef MINECPP_IENTITYSYSTEM_HPP
#define MINECPP_IENTITYSYSTEM_HPP
#include "Entity.h"
#include "Game.h"
#include <optional>
#include <vector>

namespace minecpp::game {

class IEntitySystem
{
 public:
   virtual ~IEntitySystem() noexcept = default;

   [[nodiscard]] virtual Entity create_spatial_entity(math::Vector3 position, math::Vector3 extent) = 0;
   [[nodiscard]] virtual Entity entity(EntityId id)                                                 = 0;
   [[nodiscard]] virtual void destroy_entity(EntityId id)                                           = 0;
   [[nodiscard]] virtual std::vector<game::EntityId> list_entities_in(math::Vector3 min,
                                                                      math::Vector3 max)            = 0;
   [[nodiscard]] virtual std::vector<game::EntityId>
   list_entities_in_view_distance(math::Vector3 position)                                      = 0;
   [[nodiscard]] virtual std::optional<game::EntityId> find_nearest_to(math::Vector3 position) = 0;
};

}// namespace minecpp::game

#endif//MINECPP_IENTITYSYSTEM_HPP
