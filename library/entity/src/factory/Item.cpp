#include <minecpp/entity/component/ItemSlot.h>
#include <minecpp/entity/component/Ticker.h>
#include <minecpp/entity/component/UniqueId.h>
#include <minecpp/entity/component/Velocity.h>
#include <minecpp/entity/factory/Item.h>

namespace minecpp::entity::factory {

Item::Item(const game::ItemSlot &slot, random::IRandom &random) :
    m_slot(slot),
    m_init_velocity{(random.next_double() - 0.5) / 25.0, 00.12, (random.next_double() - 0.5) / 25.0}
{
}

Item::Item(const game::ItemSlot &slot, const math::Vector3 &init_velocity) :
    m_slot(slot),
    m_init_velocity(init_velocity)
{
}

game::Entity Item::create_entity(const math::Vector3 &position, game::IEntitySystem &entity_system)
{
   auto item_entity = entity_system.create_spatial_entity(position, {0.5, 0.25, 0.5});

   item_entity.add_component<component::UniqueId>();
   item_entity.add_component<component::Ticker>();
   item_entity.add_component<component::Velocity>(m_init_velocity);
   item_entity.add_component<component::ItemSlot>(m_slot);
   return item_entity;
}

}// namespace minecpp::entity::factory
