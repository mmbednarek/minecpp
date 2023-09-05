#include <minecpp/entity/component/Inventory.h>
#include <minecpp/entity/component/ItemSlot.h>
#include <minecpp/entity/component/Location.h>
#include <spdlog/spdlog.h>

namespace minecpp::entity::component {

ItemSlot::ItemSlot(game::ItemSlot slot) :
    m_slot{slot}
{
}

void ItemSlot::on_attached(game::Entity &entity)
{
   assert(entity.has_component<Location>());

   auto &location = entity.component<Location>();
   location.on_begin_intersect.connect_to<&ItemSlot::on_begin_intersect>(m_begin_intersect_sink, this);
}

void ItemSlot::on_begin_intersect(game::IWorld &world, game::Entity &entity, game::Entity &other_entity) const
{
   if (not other_entity.has_component<Inventory>())
      return;

   if (not other_entity.has_component<Location>())
      return;

   auto &inventory = other_entity.component<Inventory>();
   if (not inventory.add_item(world.dispatcher(), m_slot.item_id, m_slot.count))
      return;

   world.dispatcher().collect_item(entity.id(), other_entity.id(),
                                   other_entity.component<Location>().position(), m_slot.count);
   world.kill_entity(entity.id());
}

void ItemSlot::serialize_to_proto(proto::entity::Entity *entity) const
{
   entity->set_entity_type(54);

   auto *metadata = entity->mutable_metadata()->Add();
   metadata->set_index(8);
   metadata->mutable_slot()->mutable_item_id()->set_id(static_cast<uint32_t>(m_slot.item_id));
   metadata->mutable_slot()->set_count(static_cast<uint32_t>(m_slot.count));
}

void ItemSlot::serialize_to_net(game::NetworkEntity *net_entity) const
{
   assert(net_entity);
   net_entity->entity_data.entity_type = 54;
   net_entity->metadata.data[8] = net::Slot{m_slot.item_id, static_cast<std::int8_t>(m_slot.count), {}};
}

}// namespace minecpp::entity::component
