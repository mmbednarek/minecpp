#include <minecpp/command/core/Give.h>
#include <minecpp/command/RuntimeContext.h>
#include <minecpp/entity/component/Inventory.h>
#include <minecpp/entity/component/Player.h>
#include <minecpp/game/IEntitySystem.hpp>
#include <minecpp/game/player/Provider.hpp>
#include <minecpp/repository/Item.h>

namespace minecpp::command::core {

bool Give::is_flag(std::string_view name) const
{
   if (name == "n") {
      return true;
   }
   return true;
}

Object::Ptr Give::run(RuntimeContext &ctx, CommandInput &input) const
{
   if (input.arg_count() == 0)
      return make_error(command_name, "invalid argument count");

   const auto item_tag = input.string_arg(0);
   auto item_id        = repository::Item::the().lookup_id(item_tag);
   if (item_id.has_failed())
      return make_error(command_name, "item with tag {} not found: {}", item_tag, item_id.err()->msg());

   auto entity = ctx.entity();
   if (not entity.has_value())
      return make_error(command_name, "couldn't find target entity");

   if (not entity->has_component<entity::component::Inventory>())
      return make_error(command_name, "target entity (entity_id:{}) doesn't have inventory", entity->id());

   auto *world = ctx.world();
   if (world == nullptr)
      return make_error(command_name, "command is not invoked within a world");

   auto &inventory = entity->component<entity::component::Inventory>();
   if (not inventory.add_item(world->dispatcher(), static_cast<game::ItemId>(item_id.get()), 64))
      return make_error(command_name, "player inventory is full");

   auto info = std::make_shared<FormattedString>();
   info->bold(format::Color::Green, "INFO ");
   info->text(format::Color::White, "giving ");
   info->text(format::Color::Yellow, item_tag);

   if (entity->has_component<entity::component::Player>()) {
      info->text(format::Color::White, " to player ");
      info->text(format::Color::Yellow, entity->component<entity::component::Player>().name());
   } else {
      info->text(format::Color::White, " to entity ");
      info->text(format::Color::Yellow, std::to_string(entity->id()));
   }

   return info;
}

ObjectType Give::return_type(RuntimeContext & /*ctx*/) const
{
   return command_return_type;
}


}// namespace minecpp::command::core