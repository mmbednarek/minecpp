#include <minecpp/command/core/Spawn.h>
#include <minecpp/command/RuntimeContext.h>
#include <minecpp/entity/Aliases.hpp>
#include <minecpp/entity/factory/Totem.h>
#include <minecpp/entity/factory/Trader.h>

namespace minecpp::command::core {

bool Spawn::is_flag(std::string_view name) const
{
   return false;
}

Object::Ptr Spawn::run(RuntimeContext &ctx, CommandInput &input) const
{
   using format::Color;
   if (input.arg_count() < 2)
      return make_error(command_name, "invalid argument count");

   auto name = input.arg<std::string>(0);
   if (not name.has_value())
      return make_error(command_name, "invalid argument 0");

   auto position = input.arg<game::BlockPosition>(1);
   if (not position.has_value())
      return make_error(command_name, "invalid argument 1");

   auto *world = ctx.world();
   if (world == nullptr)
      return make_error(command_name, "command invoked not within a world");

   if (name == "totem") {
      auto team_name = input.arg<std::string>(2);
      if (not team_name.has_value())
         return make_error(command_name, "you need to provide team's name");

      auto team = game::Team::from_string(*team_name);
      if (not team.has_value())
         return make_error(command_name, "no such team");

      world->spawn<TotemFactory>(position->to_vec3(), *team, 0.0f, 0.0f);
   } else if (name == "trader") {
      world->spawn<TraderFactory>(position->to_vec3(), 0.0f, 0.0f);
   } else {
      return make_error(command_name, "invalid entity name");
   }

   auto info = std::make_shared<FormattedString>();
   info->bold(Color::Green, "INFO ");
   info->text(Color::White, fmt::format("spawning {} at {}", *name, position->to_vec3()));
   return info;
}

ObjectType Spawn::return_type(RuntimeContext &ctx) const
{
   return command_return_type;
}
}// namespace minecpp::command::core
