#include <minecpp/command/core/Give.h>
#include <minecpp/command/RuntimeContext.h>
#include <minecpp/player/Provider.hpp>
#include <minecpp/repository/Item.h>

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

   auto item_name_obj = input.arguments.front();
   auto item_name = item_name_obj->to_string();
   auto item_id   = repository::Item::the().find_id_by_tag(item_name);
   if (item_id.has_failed()) {
      auto err = std::make_shared<RuntimeError>("give");
      err->text("invalid item tag ").text(format::Color::Yellow, item_name);
      return err;
   }

   auto *player_id = cast<UUIDObject>(ctx.variable("player_id"));
   if (player_id == nullptr) {
      auto err = std::make_shared<RuntimeError>("give");
      err->text("player id not specified");
      return err;
   }

   auto player = m_provider.get_player(player_id->value);
   if (player.has_failed()) {
      auto err = std::make_shared<RuntimeError>("give");
      err->text("could not get player with id ").text(format::Color::Yellow, boost::uuids::to_string(player_id->value));
      return err;
   }

   if (!player->inventory().add_item(static_cast<game::item::ItemId>(item_id.get()), 64)) {
      auto err = std::make_shared<RuntimeError>("give");
      err->text("player inventory is full");
      return err;
   }

   auto info = std::make_shared<FormattedString>();
   info->bold(format::Color::Green, "INFO ");
   info->text(format::Color::White, "giving ");
   info->text(format::Color::Yellow, item_name);
   info->text(format::Color::White, " to player ");
   info->text(format::Color::Yellow, player->name());
   return info;
}

ObjectType Give::return_type(RuntimeContext &ctx) const
{
   return command_return_type;
}


}// namespace minecpp::command::core