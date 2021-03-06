#pragma once
#include <minecpp/nbt/reader.h>
#include <minepb/player.pb.h>

namespace minecpp::game {

struct RecipeBook {
   bool filtering_craftable = false;
   bool furnace_filtering_craftable = false;
   bool furnace_gui_open = false;
   bool gui_open = false;

   RecipeBook() = default;
   explicit RecipeBook(nbt::Reader &r);

   void as_proto(minecpp::player::RecipeBook *book) const;
};

}