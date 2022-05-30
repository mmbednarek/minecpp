#ifndef MINECPP_ITEM_H
#define MINECPP_ITEM_H
#include "repository.h"
#include <minecpp/game/item/item.h>

namespace minecpp::repository {

class Item : public Repository<game::item::Item>
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
