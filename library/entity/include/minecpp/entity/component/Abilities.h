#pragma once
#include <minecpp/game/Abilities.hpp>
#include <minecpp/game/Entity.h>
#include <minecpp/game/IWorld.hpp>

namespace minecpp::entity::component {

class Abilities
{
 public:
   void on_attached(game::Entity &entity);

   void set_is_flying_enabled(game::IWorld &world, bool enabled);
   void set_can_instantly_destroy_blocks(game::IWorld &world, bool enabled);

   [[nodiscard]] const game::Abilities &abilities() const;

 private:
   game::Abilities m_abilities;
   game::EntityId m_entity_id{};
};

}// namespace minecpp::entity::component
