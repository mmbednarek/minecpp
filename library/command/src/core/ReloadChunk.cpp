#include <minecpp/command/core/ReloadChunk.h>
#include <minecpp/command/RuntimeContext.h>
#include <minecpp/game/World.h>

namespace minecpp::command::core {

ReloadChunk::ReloadChunk(game::World &world) :
    m_world(world)
{
}

bool ReloadChunk::is_flag(std::string_view name) const
{
   return false;
}

ObjectType ReloadChunk::return_type(RuntimeContext &ctx) const
{
   return command_return_type;
}

std::shared_ptr<RuntimeError> make_error(std::string_view message)
{
   auto err = std::make_shared<RuntimeError>("reload-chunk");
   err->text("player id not specified");
   return err;
}

Object::Ptr ReloadChunk::run(RuntimeContext &ctx, CommandInput &input) const
{
   auto *player_id = cast<UUIDObject>(ctx.variable("player_id"));
   if (player_id == nullptr) {
      return make_error("could not obtain player_id");
   }
   auto *player_position = cast<BlockPositionObject>(ctx.variable("here"));
   if (player_position == nullptr) {
      return make_error("could not obtain player position");
   }

   auto res = m_world.send_chunk_to_player(player_id->value, player_position->value.chunk_position());
   if (res.has_failed()) {
      return make_error("could not send chunk to the player");
   }

   auto info = std::make_shared<FormattedString>();
   info->bold(format::Color::Green, "INFO ");
   info->text(format::Color::White, "reloading current chunk");
   return info;
}

}// namespace minecpp::command::core
