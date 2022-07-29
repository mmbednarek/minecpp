#ifndef MINECPP_INVENTORY_H
#define MINECPP_INVENTORY_H
#include <array>
#include <minecpp/game/Game.h>
#include <minecpp/game/Notifier.h>

namespace minecpp::game::player {

struct ItemSlot
{
   game::ItemId item_id{};
   std::size_t count{};
};

class Inventory
{
   std::array<ItemSlot, 9 * 4> m_slots{};
   std::size_t m_hot_bar_slot{};
   PlayerId m_player_id;
   game::Notifier &m_notifier;

 public:
   explicit Inventory(PlayerId player_id, game::Notifier &notifier);

   Inventory(Inventory &&other) noexcept;
   Inventory &operator=(Inventory &&other) noexcept;

   [[nodiscard]] bool add_item(game::ItemId item, std::size_t count);
   [[maybe_unused]] [[nodiscard]] std::size_t take_item(game::ItemId item, std::size_t count);
   [[nodiscard]] bool take_from_slot(game::SlotId id, std::size_t count);
   [[nodiscard]] bool take_from_active_slot(std::size_t count);
   [[nodiscard]] ItemSlot item_at(game::SlotId id) const;
   void set_slot(game::SlotId id, const ItemSlot &slot);
   void set_hot_bar_slot(std::size_t slot);
   [[nodiscard]] ItemSlot active_item() const;
};

}// namespace minecpp::game::player

#endif//MINECPP_INVENTORY_H
