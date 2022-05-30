#include <algorithm>
#include <minecpp/player/inventory.h>

namespace minecpp::player {

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

   return true;
}

constexpr std::size_t slot_id_to_index(SlotId id)
{
   if (id < 4 * 9) {
      return id;
   }
   return id - 4 * 9;
}

ItemSlot Inventory::item_at(SlotId id) const
{
   return m_slots[slot_id_to_index(id)];
}

void Inventory::set_slot(SlotId id, const ItemSlot &slot)
{
   m_slots[slot_id_to_index(id)] = slot;
}

void Inventory::set_hot_bar_slot(std::size_t slot)
{
   if (slot < 0 || slot > 8)
      return;
   m_hot_bar_slot = slot;
}

ItemSlot Inventory::active_item()
{
   return m_slots[m_hot_bar_slot];
}

}// namespace minecpp::player