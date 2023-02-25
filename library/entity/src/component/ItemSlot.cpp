#include <minecpp/entity/component/Inventory.h>
#include <minecpp/entity/component/ItemSlot.h>
#include <minecpp/entity/component/Location.h>
#include <spdlog/spdlog.h>

namespace minecpp::entity::component {

void ItemSlot::on_attached(game::Entity &entity)
{
   if (entity.has_component<Location>()) {
      auto &location = entity.component<Location>();
      entt::sink sink{location.on_begin_intersect};
      sink.connect<&ItemSlot::on_begin_intersect>(this);
   }
}

void ItemSlot::on_begin_intersect(game::IWorld &world, game::Entity &entity, game::Entity &other_entity)
{
   spdlog::info("entity {} intersecting with entity {}", entity.id(), other_entity.id());
   if (not other_entity.has_component<Inventory>())
      return;

   if (not other_entity.has_component<Location>())
      return;

   auto &inv = other_entity.component<Inventory>();
   if (not inv.add_item(world.dispatcher(), this->slot.item_id, this->slot.count))
      return;

   world.dispatcher().collect_item(entity.id(), other_entity.id(),
                                   other_entity.component<Location>().position(), this->slot.count);
   world.kill_entity(entity.id());
}

void ItemSlot::serialize_to_proto(proto::entity::v1::Entity *entity) const
{
   entity->set_entity_type(45);

   auto *metadata = entity->mutable_metadata()->Add();
   metadata->set_index(8);
   metadata->mutable_slot()->mutable_item_id()->set_id(static_cast<uint32_t>(this->slot.item_id));
   metadata->mutable_slot()->set_count(static_cast<uint32_t>(this->slot.count));
}

}// namespace minecpp::entity::component
