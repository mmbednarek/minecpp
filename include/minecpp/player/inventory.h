#ifndef MINECPP_INVENTORY_H
#define MINECPP_INVENTORY_H
#include <array>
#include <minecpp/game/item/item.h>
#include <minecpp/game/notifier.h>

namespace minecpp::player {

struct ItemSlot
{
   game::item::ItemId item_id{};
   std::size_t count{};
};

class Inventory
{
   std::array<ItemSlot, 9 * 4> m_slots{};
   std::size_t m_hot_bar_slot{};
   Id m_player_id;
   game::Notifier& m_notifier;

 public:
   explicit Inventory(Id player_id, game::Notifier &notifier);

   Inventory(Inventory&& other) noexcept;
   Inventory& operator=(Inventory&& other) noexcept;

   [[nodiscard]] bool add_item(game::item::ItemId item, std::size_t count);
   [[nodiscard]] ItemSlot item_at(game::SlotId id) const;
   void set_slot(game::SlotId id, const ItemSlot &slot);
   void set_hot_bar_slot(std::size_t slot);
   ItemSlot active_item();
};

}// namespace minecpp::player

#endif//MINECPP_INVENTORY_H
