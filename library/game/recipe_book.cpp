#include <minecpp/game/recipe_book.h>

namespace minecpp::game {

using nbt::TagId;

RecipeBook::RecipeBook(nbt::Reader &r)
{
   r.read_compound([this](nbt::Reader &r, nbt::TagId tagid, const std::string &name) {
      if (tagid == TagId::Byte) {
         if (name == "isFilteringCraftable") {
            filtering_craftable = r.read_byte();
            return;
         }
         if (name == "isFurnaceFilteringCraftable") {
            furnace_filtering_craftable = r.read_byte();
            return;
         }
         if (name == "isFurnaceGuiOpen") {
            furnace_gui_open = r.read_byte();
            return;
         }
         if (name == "isGuiOpen") {
            gui_open = r.read_byte();
            return;
         }
      }
      r.skip_payload(tagid);
   });
}

void RecipeBook::as_proto(proto::player::v1::RecipeBook *book) const
{
   book->set_filtering_craftable(filtering_craftable);
   book->set_furnace_filtering_craftable(furnace_filtering_craftable);
   book->set_gui_open(gui_open);
   book->set_furnace_gui_open(furnace_gui_open);
}

}// namespace minecpp::game
