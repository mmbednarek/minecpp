#include <minecpp/game/IItemController.hpp>

namespace minecpp::controller::item {

class Bow : public game::IItemController
{
 public:
   void on_item_use(game::IWorld &world, game::PlayerId player_id, game::EntityId player_entity_id,
                    game::ItemId item_id) override;
};

}// namespace minecpp::controller::item