#include <minecpp/game/IItemController.hpp>

namespace minecpp::controller {

class RootItem : public game::IItemController
{
 public:
   void on_item_use(game::IWorld &world, game::PlayerId player_id, game::EntityId player_entity_id,
                    game::ItemId item_id) override;

   [[nodiscard]] game::IItemController &controller(game::ItemId block_id);
   [[nodiscard]] bool has_controller_for(game::ItemId block_id) const;

   template<typename TController, typename... TArgs>
   void register_controller(game::ItemId item_id, TArgs &&...args)
   {
      m_controllers[item_id] = std::make_unique<TController>(std::forward<TArgs>(args)...);
   }

 private:
   std::map<game::ItemId, std::unique_ptr<game::IItemController>> m_controllers;
};

}// namespace minecpp::controller