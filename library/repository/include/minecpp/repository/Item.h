#ifndef MINECPP_ITEM_H
#define MINECPP_ITEM_H
#include "Repository.h"
#include <minecpp/game/Game.h>
#include <minecpp/game/item/Item.h>

namespace minecpp::repository {

class Item : public Repository<game::item::Item, game::ItemId>
{
   static Item g_instance;

 public:
   constexpr static Item &the()
   {
      return g_instance;
   }
};

}// namespace minecpp::repository

#endif//MINECPP_ITEM_H
