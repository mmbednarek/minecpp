#pragma once
#include <array>
#include <minecpp/game/Entity.h>
#include <minecpp/game/Game.h>
#include <minecpp/game/IDispatcher.hpp>
#include <minecpp/game/IWorld.hpp>

namespace minecpp::entity::component {

class Inventory
{
 public:
   void on_attached(game::Entity &entity);

   [[nodiscard]] bool add_item(game::IDispatcher &notifier, game::ItemId item, int count);
   [[nodiscard]] mb::emptyres add_item_by_tag(game::IDispatcher &dispatcher, const std::string &name,
                                              int count);
   [[nodiscard]] int take_item(game::IDispatcher &notifier, game::ItemId item, int count);
   bool take_from_slot(game::IDispatcher &notifier, game::SlotId id, int count);
   bool take_from_active_slot(game::IDispatcher &notifier, int count);
   [[nodiscard]] game::ItemSlot item_at(game::SlotId id) const;
   [[nodiscard]] game::ItemSlot active_item() const;
   void synchronize_inventory(game::IDispatcher &notifier) const;
   void drop_active_item(game::IWorld &world, bool whole_stack);
   void drop_carried_item(game::IWorld &world, bool whole_stack);
   void set_carried_item(const game::ItemSlot &slot);
   [[nodiscard]] int count_item(game::ItemId item) const;

   void set_slot(game::IDispatcher &notifier, game::SlotId id, const game::ItemSlot &slot);
   void set_active_item(game::IDispatcher &notifier, int slot);

 private:
   void drop_stack(game::IWorld &world, const game::ItemSlot &active_item) const;

   std::array<game::ItemSlot, 9 * 4> m_slots{};
   game::PlayerId m_player_id{};
   game::EntityId m_entity_id{};
   int m_active_item{};
   game::ItemSlot m_carried_item{};
};

}// namespace minecpp::entity::component