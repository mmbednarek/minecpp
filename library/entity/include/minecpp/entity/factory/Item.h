#pragma once
#include "../EntitySystem.h"

namespace minecpp::entity::factory {

class Item : public IEntityFactory
{
 public:
   Item(const game::ItemSlot &slot);
   game::Entity create_entity(const math::Vector3 &position, game::IEntitySystem &entity_system) override;

 private:
   game::ItemSlot m_slot;
};

}// namespace minecpp::entity::factory