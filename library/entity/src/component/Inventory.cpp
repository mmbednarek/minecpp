#include <minecpp/entity/component/Inventory.h>
#include <minecpp/entity/component/Location.h>
#include <minecpp/entity/component/Player.h>
#include <minecpp/entity/factory/Item.h>

namespace minecpp::entity::component {

constexpr auto g_min_inventory_index = 9;
constexpr auto g_min_hotbar_index    = 36;

namespace {

constexpr game::SlotId index_to_slot_id(int64_t index)
{
   return static_cast<game::SlotId>(g_min_inventory_index + index);
}

constexpr std::size_t slot_id_to_index(game::SlotId slot_id)
{
   return static_cast<std::size_t>(slot_id - g_min_inventory_index);
}

constexpr std::size_t hotbar_index_to_array_index(int hotbar_index)
{
   return static_cast<std::size_t>(hotbar_index + g_min_hotbar_index - g_min_inventory_index);
}

constexpr game::SlotId hotbar_index_to_slot_id(int hotbar_index)
{
   return static_cast<game::SlotId>(hotbar_index + g_min_hotbar_index);
}

}// namespace

void Inventory::on_attached(game::Entity &entity)
{
   m_entity_id = entity.id();
   if (entity.has_component<Player>()) {
      m_player_id = entity.component<Player>().id();
   }
}

bool Inventory::add_item(game::IDispatcher &notifier, game::ItemId item, int count)
{
   const auto does_slot_has_space = [item, count](const game::ItemSlot &slot) {
      if (slot.count == 0) {
         return true;
      }
      return slot.item_id == item && (slot.count + count) <= 64;
   };

   // First check for active hot bar slow
   auto it = std::find_if(m_slots.begin() + (g_min_hotbar_index - g_min_inventory_index), m_slots.end(),
                          does_slot_has_space);

   if (it == m_slots.end()) {
      it = std::find_if(m_slots.begin(), m_slots.end() - 9, does_slot_has_space);
      if (it == m_slots.end()) {
         return false;
      }
   }

   it->item_id = item;
   it->count += count;

   notifier.set_inventory_slot(m_player_id, item, index_to_slot_id(it - m_slots.begin()), it->count);
   return true;
}

int Inventory::take_item(game::IDispatcher &notifier, game::ItemId item, int count)
{
   auto it           = m_slots.begin();
   auto left_to_take = count;

   while (left_to_take > 0 && it != m_slots.end()) {
      it = std::find_if(it, m_slots.end(), [item](const game::ItemSlot &slot) {
         if (slot.count == 0) {
            return false;
         }
         return slot.item_id == item;
      });

      auto taken = std::min(it->count, left_to_take);
      it->count -= taken;
      if (it->count == 0) {
         it->item_id = 0;
      }

      notifier.set_inventory_slot(m_player_id, it->item_id, index_to_slot_id(it - m_slots.begin()),
                                  it->count);
      left_to_take -= taken;
   }

   return count - left_to_take;
}

game::ItemSlot Inventory::item_at(game::SlotId id) const
{
   return m_slots[slot_id_to_index(id)];
}

void Inventory::set_slot(game::IDispatcher &notifier, game::SlotId id, const game::ItemSlot &slot)
{
   auto index = slot_id_to_index(id);
   if (index > 9 * 4)
      return;

   m_slots[slot_id_to_index(id)] = slot;
   notifier.set_inventory_slot(m_player_id, slot.item_id, id, slot.count);

   if (hotbar_index_to_slot_id(m_active_item) == id) {
      notifier.set_player_equipment(m_player_id, m_entity_id, game::EquipmentSlot::MainHand, slot);
   }
}

void Inventory::set_active_item(game::IDispatcher &notifier, int slot)
{
   if (slot < 0 || slot > 8)
      return;

   m_active_item = slot;
   notifier.set_player_equipment(m_player_id, m_entity_id, game::EquipmentSlot::MainHand,
                                 this->active_item());
}

game::ItemSlot Inventory::active_item() const
{
   return m_slots[hotbar_index_to_array_index(m_active_item)];
}

bool Inventory::take_from_slot(game::IDispatcher &notifier, game::SlotId id, int count)
{
   auto index = slot_id_to_index(id);

   auto &slot = m_slots[index];
   if (slot.count < count) {
      return false;
   }

   slot.count -= count;

   notifier.set_inventory_slot(m_player_id, slot.item_id, id, slot.count);
   return true;
}

bool Inventory::take_from_active_slot(game::IDispatcher &notifier, int count)
{
   return take_from_slot(notifier, hotbar_index_to_slot_id(m_active_item), count);
}

void Inventory::synchronize_inventory(game::IDispatcher &notifier) const
{
   for (game::SlotId id{9}; id < 5 * 9; ++id) {
      auto slot = this->item_at(id);
      notifier.set_inventory_slot(m_player_id, slot.item_id, id, slot.count);
   }
}

void Inventory::drop_active_item(game::IWorld &world, bool whole_stack)
{
   auto active_item = this->active_item();
   if (active_item.count == 0)
      return;

   if (not whole_stack) {
      active_item.count = 1;
      this->take_from_slot(world.dispatcher(), hotbar_index_to_slot_id(m_active_item), 1);
   } else {
      this->take_from_slot(world.dispatcher(), hotbar_index_to_slot_id(m_active_item), active_item.count);
   }

   drop_stack(world, active_item);
}

void Inventory::drop_stack(game::IWorld &world, const game::ItemSlot &active_item) const
{
   auto entity = world.entity_system().entity(m_entity_id);
   if (not entity.has_component<Rotation>())
      return;

   auto velocity = math::Vector3::from_yaw_and_pitch(entity.component<Rotation>().yaw(),
                                                     entity.component<Rotation>().pitch());
   velocity.set_y(1.0);

   const math::Vector3 offset{velocity.x(), 0.75, velocity.z()};
   world.spawn<factory::Item>(entity.component<Location>().position() + offset, active_item, velocity * 0.2);
}

void Inventory::set_carried_item(const game::ItemSlot &slot)
{
   m_carried_item = slot;
}

void Inventory::drop_carried_item(game::IWorld &world, bool whole_stack)
{
   if (m_carried_item.count == 0)
      return;

   if (whole_stack) {
      this->drop_stack(world, m_carried_item);
      m_carried_item.item_id = 0;
      m_carried_item.count   = 0;
      return;
   }

   this->drop_stack(world, {m_carried_item.item_id, 1});
   --m_carried_item.count;
}

}// namespace minecpp::entity::component
