#include <minecpp/command/core/Teleport.h>
#include <minecpp/command/RuntimeContext.h>
#include <minecpp/entity/Aliases.hpp>
#include <minecpp/entity/component/Location.h>
#include <minecpp/entity/component/Player.h>
#include <minecpp/entity/component/Streamer.h>

namespace minecpp::command::core {

bool Teleport::is_flag(std::string_view /*name*/) const
{
   return false;
}

Object::Ptr Teleport::run(RuntimeContext &ctx, CommandInput &input) const
{
   if (input.arg_count() != 1)
      return make_error(command_name, "invalid argument count");

   auto entity = ctx.entity();
   if (not ctx.entity())
      return make_error(command_name, "no entity");

   auto position = input.arg<game::BlockPosition>(0);
   if (not position.has_value())
      return make_error(command_name, "invalid argument");

   entity->component<LocationComponent>().teleport_player(*ctx.world(), *entity, position->to_vector3());

   auto info = std::make_shared<FormattedString>();
   info->bold(format::Color::Green, "INFO ");
   info->text(format::Color::White, "teleporting player");
   return info;
}

ObjectType Teleport::return_type(RuntimeContext & /*ctx*/) const
{
   return command_return_type;
}

}// namespace minecpp::command::core
