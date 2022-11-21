#pragma once
#include <mb/result.h>
#include <minecpp/game/entity/Entity.h>
#include <minecpp/game/EntityManager.hpp>
#include <vector>

namespace minecpp::service::engine {

using minecpp::game::entity::Entity;

class EntityManager : public game::EntityManager
{
   std::vector<Entity> m_entities;

 public:
   game::EntityId spawn(Entity e) override;
   mb::result<Entity &> get_entity(game::EntityId id) override;

   [[nodiscard]] constexpr const std::vector<Entity> &entities() const
   {
      return m_entities;
   }
};

}// namespace minecpp::service::engine
