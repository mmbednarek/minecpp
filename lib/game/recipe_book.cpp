#include "recipe_book.h"

namespace Game {

using NBT::TagID;

RecipeBook::RecipeBook(NBT::Reader &r) {
   r.read_compound(
       [this](NBT::Reader &r, NBT::TagID tagid, const std::string &name) {
          if (tagid == TagID::Byte) {
             if (name == "isFilteringCraftable") {
                filtering_craftable = r.read_payload<NBT::Byte>();
                return;
             }
             if (name == "isFurnaceFilteringCraftable") {
                furnace_filtering_craftable = r.read_payload<NBT::Byte>();
                return;
             }
             if (name == "isFurnaceGuiOpen") {
                furnace_gui_open = r.read_payload<NBT::Byte>();
                return;
             }
             if (name == "isGuiOpen") {
                gui_open = r.read_payload<NBT::Byte>();
                return;
             }
          }
          r.skip_payload(tagid);
       });
}

void RecipeBook::as_proto(minecpp::player::RecipeBook *book) const {
   book->set_filtering_craftable(filtering_craftable);
   book->set_furnace_filtering_craftable(furnace_filtering_craftable);
   book->set_gui_open(gui_open);
   book->set_furnace_gui_open(furnace_gui_open);
}

} // namespace Game
