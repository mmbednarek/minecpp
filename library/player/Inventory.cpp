#include <algorithm>
#include <minecpp/player/Inventory.h>

namespace minecpp::player {

constexpr std::size_t slot_id_to_index(game::SlotId id)
{
   if (id < 4 * 9) {
      return id;
   }
   return id - 4 * 9;
}

constexpr game::SlotId index_to_slot_id(std::size_t index)
{
   if (index < 10) {
      return static_cast<game::SlotId>(4 * 9 + index);
   }
   return static_cast<game::SlotId>(index);
}

Inventory::Inventory(Id player_id, game::Notifier &notifier) :
    m_player_id(player_id),
    m_notifier(notifier)
{
}

Inventory::Inventory(Inventory &&other) noexcept :
    m_slots(std::exchange(other.m_slots, {})),
    m_hot_bar_slot(std::exchange(other.m_hot_bar_slot, 0)),
    m_player_id(std::exchange(other.m_player_id, {})),
    m_notifier(other.m_notifier)
{
}

Inventory &Inventory::operator=(Inventory &&other) noexcept
{
   m_slots        = std::exchange(other.m_slots, {});
   m_hot_bar_slot = std::exchange(other.m_hot_bar_slot, 0);
   m_player_id    = std::exchange(other.m_player_id, {});
   m_notifier     = other.m_notifier;
   return *this;
}

bool Inventory::add_item(game::item::ItemId item, std::size_t count)
{
   auto it = std::find_if(m_slots.begin(), m_slots.end(), [item, count](const ItemSlot &slot) {
      if (slot.count == 0) {
         return true;
      }
      return slot.item_id == item && (slot.count + count) < 64;
   });

   if (it == m_slots.end()) {
      return false;
   }

   it->item_id = item;
   it->count += count;

   m_notifier.set_inventory_slot(m_player_id, item,
                                 index_to_slot_id(static_cast<size_t>(it - m_slots.begin())), it->count);

   return true;
}

std::size_t Inventory::take_item(game::item::ItemId item, std::size_t count)
{
   auto it           = m_slots.begin();
   auto left_to_take = count;

   while (left_to_take > 0 && it != m_slots.end()) {
      it = std::find_if(it, m_slots.end(), [item](const ItemSlot &slot) {
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
      m_notifier.set_inventory_slot(m_player_id, it->item_id,
                                    index_to_slot_id(static_cast<std::size_t>(it - m_slots.begin())),
                                    it->count);
      left_to_take -= taken;
   }

   return count - left_to_take;
}

ItemSlot Inventory::item_at(game::SlotId id) const
{
   return m_slots[slot_id_to_index(id)];
}

void Inventory::set_slot(game::SlotId id, const ItemSlot &slot)
{
   m_slots[slot_id_to_index(id)] = slot;
   m_notifier.set_inventory_slot(m_player_id, slot.item_id, id, slot.count);
}

void Inventory::set_hot_bar_slot(std::size_t slot)
{
   if (slot < 0 || slot > 8)
      return;
   m_hot_bar_slot = slot;
}

ItemSlot Inventory::active_item() const
{
   return m_slots[m_hot_bar_slot];
}

bool Inventory::take_from_slot(game::SlotId id, std::size_t count)
{
   auto index = slot_id_to_index(id);

   auto &slot = m_slots[index];
   if (slot.count < count) {
      return false;
   }

   slot.count -= count;

   m_notifier.set_inventory_slot(m_player_id, slot.item_id, id, slot.count);
   return true;
}

bool Inventory::take_from_active_slot(std::size_t count)
{
   return take_from_slot(index_to_slot_id(m_hot_bar_slot), count);
}

}// namespace minecpp::player