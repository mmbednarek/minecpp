#include <minecpp/entity/component/ItemSlot.h>
#include <minecpp/entity/component/TickComponent.h>
#include <minecpp/entity/component/Velocity.h>
#include <minecpp/entity/factory/Item.h>

namespace minecpp::entity::factory {

Item::Item(const game::ItemSlot &slot) :
    m_slot(slot)
{
}

game::Entity Item::create_entity(const math::Vector3 &position, game::IEntitySystem &entity_system)
{
   auto item_entity = entity_system.create_spatial_entity(position, {0.5, 0.25, 0.5});

   auto rand_x = rand() % 20;
   auto rand_z = rand() % 20;

   item_entity.add_component<component::TickComponent>();
   item_entity.add_component<component::Velocity>(math::Vector3{
           (static_cast<double>(rand_x) - 10.0) / 250.0, 0.12, (static_cast<double>(rand_z) - 10.0) / 250.0});
   item_entity.add_component<component::ItemSlot>(m_slot);
   return item_entity;
}

}// namespace minecpp::entity::factory
