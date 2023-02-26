#include <fmt/core.h>
#include <minecpp/repository/Item.h>

namespace minecpp::repository {

Item Item::g_instance;

mb::result<game::ItemId> Item::lookup_id(const std::string &tag)
{
   auto item_id = repository::Item::the().find_id_by_tag(tag);
   if (item_id.ok())
      return item_id;

   return repository::Item::the().find_id_by_tag(fmt::format("minecraft:{}", tag));
}

}// namespace minecpp::repository