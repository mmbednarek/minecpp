#include <minecpp/command/core/Give.h>
#include <minecpp/command/RuntimeContext.h>
#include <minecpp/entity/component/Inventory.h>
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
   if (input.arguments.empty())
      return {};

   auto item_name_obj = input.arguments.front();
   auto item_name     = item_name_obj->to_string();
   auto item_id       = repository::Item::the().find_id_by_tag(item_name);
   if (item_id.has_failed()) {
      // try to find the same item with a minecraft: prefix
      item_id = repository::Item::the().find_id_by_tag(fmt::format("minecraft:{}", item_name));
      if (item_id.has_failed()) {
         auto err = std::make_shared<RuntimeError>("give");
         err->text("invalid item tag ").text(format::Color::Yellow, item_name);
         return err;
      }
   }

   auto *world = ctx.world();
   if (world == nullptr) {
      auto err = std::make_shared<RuntimeError>("give");
      err->text("world is empty");
      return err;
   }

   auto *entity_id_obj = cast<IntObject>(ctx.variable("entity_id"));
   if (entity_id_obj == nullptr) {
      auto err = std::make_shared<RuntimeError>("give");
      err->text("entity id not specified");
      return err;
   }
   auto entity_id = static_cast<game::EntityId>(entity_id_obj->value);
   auto entity    = world->entity_system().entity(entity_id);

   if (not entity.has_component<entity::component::Inventory>()) {
      auto err = std::make_shared<RuntimeError>("give");
      err->text("entity ")
              .text(format::Color::Yellow, std::to_string(entity_id_obj->value)).text(" doesn't have inventory");
      return err;
   }

   auto &inventory = entity.component<entity::component::Inventory>();
   if (not inventory.add_item(world->notifier(), static_cast<game::ItemId>(item_id.get()), 64)) {
      auto err = std::make_shared<RuntimeError>("give");
      err->text("player inventory is full");
      return err;
   }

   auto info = std::make_shared<FormattedString>();
   info->bold(format::Color::Green, "INFO ");
   info->text(format::Color::White, "giving ");
   info->text(format::Color::Yellow, item_name);
   info->text(format::Color::White, " to entity ");
   info->text(format::Color::Yellow, std::to_string(entity_id));
   return info;
}

ObjectType Give::return_type(RuntimeContext & /*ctx*/) const
{
   return command_return_type;
}


}// namespace minecpp::command::core