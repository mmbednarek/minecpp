#pragma once
#include <array>
#include <minecpp/game/Entity.h>
#include <minecpp/game/Game.h>
#include <minecpp/game/IDispatcher.hpp>

namespace minecpp::entity::component {

class Inventory
{
 public:
   void on_attached(game::Entity &entity);

   [[nodiscard]] bool add_item(game::IDispatcher &notifier, game::ItemId item, int count);
   [[nodiscard]] int take_item(game::IDispatcher &notifier, game::ItemId item, int count);
   [[nodiscard]] bool take_from_slot(game::IDispatcher &notifier, game::SlotId id, int count);
   [[nodiscard]] bool take_from_active_slot(game::IDispatcher &notifier, int count);
   [[nodiscard]] game::ItemSlot item_at(game::SlotId id) const;
   [[nodiscard]] game::ItemSlot active_item() const;
   [[nodiscard]] void synchronize_inventory(game::IDispatcher &notifier) const;

   void set_slot(game::IDispatcher &notifier, game::SlotId id, const game::ItemSlot &slot);
   void set_active_item(game::IDispatcher &notifier, int slot);

 private:
   std::array<game::ItemSlot, 9 * 4> m_slots{};
   game::PlayerId m_player_id{};
   game::EntityId m_entity_id{};
   int m_active_item{};
};

}// namespace minecpp::entity::component