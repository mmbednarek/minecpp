#include <minecpp/command/core/give.h>
#include <minecpp/command/runtime_context.h>
#include <minecpp/player/provider.hpp>
#include <minecpp/repository/item.h>

namespace minecpp::command::core {

Give::Give(player::Provider &provider) :
    m_provider(provider)
{
}

bool Give::is_flag(std::string_view name) const
{
   if (name == "n") {
      return true;
   }
   return true;
}

Object::Ptr Give::run(RuntimeContext &ctx, CommandInput &input) const
{
   if(input.arguments.empty())
      return {};

   auto item_name = input.arguments.front();
   auto item_id   = repository::Item::the().find_id_by_tag(item_name->to_string());
   if (item_id.has_failed()) {
      return {};
   }

   auto *player_id = cast<UUIDObject>(ctx.variable("player_id"));
   if (player_id == nullptr)
      return {};

   auto player = m_provider.get_player(player_id->value);
   if (player.has_failed()) {
      return {};
   }

   if (!player->inventory().add_item(static_cast<game::item::ItemId>(item_id.get()), 64)) {
      return std::make_shared<StringObject>("player inventory is full");
   }
   return std::make_shared<StringObject>("successfully given item to a player");
}

ObjectType Give::return_type(RuntimeContext &ctx) const
{
   return command_return_type;
}


}// namespace minecpp::command::core