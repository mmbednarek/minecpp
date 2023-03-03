#pragma once
#include "../EntitySystem.h"
#include <minecpp/random/IRandom.h>

namespace minecpp::entity::factory {

class Item : public IEntityFactory
{
 public:
   explicit Item(const game::ItemSlot &slot, random::IRandom &random);
   Item(const game::ItemSlot &slot, const math::Vector3 &init_velocity);
   game::Entity create_entity(const math::Vector3 &position, game::IEntitySystem &entity_system) override;

 private:
   game::ItemSlot m_slot;
   math::Vector3 m_init_velocity;
};

}// namespace minecpp::entity::factory