#include "core/DecimateBlocks.h"
#include "RuntimeContext.h"

#include "minecpp/entity/Aliases.hpp"
#include "minecpp/entity/component/Abilities.h"

namespace minecpp::command::core {

bool DecimateBlocks::is_flag(std::string_view /*name*/) const
{
   return false;
}

Object::Ptr DecimateBlocks::run(RuntimeContext &ctx, CommandInput &input) const
{
   bool should_enable = true;

   if (input.arg_count() > 1)
      return make_error(command_name, "too many arguments");

   if (input.arg_count() == 1) {
      auto enable = input.arg<std::string>(0);
      if (enable == "off") {
         should_enable = false;
      } else if (enable != "on") {
         return make_error(command_name, "invalid first argument");
      }
   }

   auto *world = ctx.world();
   if (world == nullptr)
      return make_error(command_name, "command invoked outside of a world");

   auto entity = ctx.entity();
   if (not entity.has_value())
      return make_error(command_name, "no active entity");

   if (not entity->has_component<AbilitiesComponent>())
      return make_error(command_name, "active entity doesn't have abilities");

   entity->component<AbilitiesComponent>().set_can_instantly_destroy_blocks(*world, should_enable);

   auto info = std::make_shared<FormattedString>();
   info->bold(format::Color::Green, "INFO ");
   info->text(format::Color::White, "instantly destroy blocks: ");
   info->text(format::Color::Yellow, should_enable ? "on" : "off");

   ctx.out().write(info);

//   return info;
   return nullptr;
}

ObjectType DecimateBlocks::return_type(RuntimeContext & /*ctx*/) const
{
   return command_return_type;
}

}// namespace minecpp::command::core
