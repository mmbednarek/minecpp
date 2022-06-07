#include <algorithm>
#include <minecpp/player/inventory.h>

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

ItemSlot Inventory::active_item()
{
   return m_slots[m_hot_bar_slot];
}

}// namespace minecpp::player