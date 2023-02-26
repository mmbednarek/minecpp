#include <minecpp/command/core/ReloadChunk.h>
#include <minecpp/command/RuntimeContext.h>
#include <minecpp/game/IWorld.hpp>

namespace minecpp::command::core {

bool ReloadChunk::is_flag(std::string_view /*name*/) const
{
   return false;
}

ObjectType ReloadChunk::return_type(RuntimeContext & /*ctx*/) const
{
   return command_return_type;
}

Object::Ptr ReloadChunk::run(RuntimeContext &ctx, CommandInput & /*input*/) const
{
   auto player_id = ctx.player_id();
   if (not player_id.has_value())
      return make_error(command_name, "could not obtain player_id");

   auto player_position = ctx.current_position();
   if (not player_position.has_value())
      return make_error(command_name, "could not obtain player position");

   auto *world = ctx.world();
   if (world == nullptr)
      return make_error(command_name, "command is not invoked within a world");

   auto res = world->send_chunk_to_player(*player_id, player_position->chunk_position());
   if (res.has_failed())
      return make_error(command_name, "could not send chunk to the player: {}", res.err()->msg());

   auto info = std::make_shared<FormattedString>();
   info->bold(format::Color::Green, "INFO ");
   info->text(format::Color::White, "reloading current chunk");
   return info;
}

}// namespace minecpp::command::core
