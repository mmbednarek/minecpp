#include <minecpp/command/core/Sync.h>
#include <minecpp/command/RuntimeContext.h>
#include <minecpp/entity/component/Inventory.h>
#include <minecpp/entity/component/Player.h>
#include <minecpp/entity/component/Streamer.h>

namespace minecpp::command::core {

bool Sync::is_flag(std::string_view /*name*/) const
{
   return false;
}

ObjectType Sync::return_type(RuntimeContext & /*ctx*/) const
{
   return command_return_type;
}

Object::Ptr Sync::run(RuntimeContext &ctx, CommandInput & /*input*/) const
{
   auto *world = ctx.world();
   if (world == nullptr)
      return make_error(command_name, "command is not invoked within a world");

   auto entity = ctx.entity();
   if (not entity.has_value())
      return make_error(command_name, "could not obtain entity");

   if (entity->has_component<minecpp::entity::component::Inventory>())
      return make_error(command_name, "entity doesn't have inventory");

   entity->component<minecpp::entity::component::Inventory>().synchronize_inventory(world->dispatcher());

   if (entity->has_component<minecpp::entity::component::Player>())
      return make_error(command_name, "entity is not a player");

   if (entity->has_component<minecpp::entity::component::Streamer>())
      return make_error(command_name, "entity doesn't stream chunks");

   auto player_id = entity->component<minecpp::entity::component::Player>().id();
   entity->component<minecpp::entity::component::Streamer>().send_all_visible_chunks(*world,
                                                                                               player_id);

   auto info = std::make_shared<FormattedString>();
   info->bold(format::Color::Green, "INFO ");
   info->text(format::Color::White, "synchronized chunks and inventory");
   return info;
}
}// namespace minecpp::command::core
