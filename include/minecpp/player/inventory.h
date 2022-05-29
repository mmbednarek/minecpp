#ifndef MINECPP_INVENTORY_H
#define MINECPP_INVENTORY_H
#include <array>
#include <minecpp/game/item/item.h>

namespace minecpp::player {

struct ItemSlot {
   game::item::ItemId item_id{};
   std::size_t count{};
};

using SlotId = uint32_t;

class Inventory {
   std::array<ItemSlot, 9*4> m_slots{};
 public:

   [[nodiscard]] bool add_item(game::item::ItemId item, std::size_t count);
   [[nodiscard]] ItemSlot item_at(SlotId id) const;
};

}

#endif//MINECPP_INVENTORY_H
