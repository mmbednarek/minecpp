#include <minecpp/command/core/KillAll.h>
#include <minecpp/command/RuntimeContext.h>
#include <minecpp/entity/Aliases.hpp>
#include <minecpp/entity/component/Player.h>

using minecpp::format::Color;

namespace minecpp::command::core {

bool KillAll::is_flag(std::string_view /*name*/) const
{
   return false;
}

Object::Ptr KillAll::run(RuntimeContext &ctx, CommandInput & /*input*/) const
{
   auto entity = ctx.entity();
   if (not entity->has_component<PlayerComponent>())
      return make_error(command_name, "invalid entity");

   auto *world = ctx.world();
   if (world == nullptr)
      return make_error(command_name, "invalid entity");

   const auto &visible_entities = entity->component<PlayerComponent>().visible_entities();
   for (auto entity_id : visible_entities) {
      //      if (entity_id == entity->id())
      //         continue;

      world->apply_damage_or_kill_entity(entity_id, game::Damage{
                                                            .amount        = 100.0f,
                                                            .source        = game::DamageSource::CommandKill,
                                                            .source_entity = entity->id(),
                                                            .target_entity = entity_id,
                                                    });
   }

   auto info = std::make_shared<FormattedString>();
   info->bold(Color::Green, "INFO ");
   info->text(Color::White, fmt::format("killing all visible entities"));
   return info;
}

ObjectType KillAll::return_type(RuntimeContext & /*ctx*/) const
{
   return command_return_type;
}

}// namespace minecpp::command::core
