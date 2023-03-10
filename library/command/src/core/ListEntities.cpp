#include <minecpp/command/core/ListEntities.h>
#include <minecpp/command/RuntimeContext.h>
#include <minecpp/entity/Aliases.hpp>
#include <minecpp/entity/component/Player.h>

namespace minecpp::command::core {

bool ListEntities::is_flag(std::string_view name) const
{
   if (name == "p")
      return true;
   return false;
}

Object::Ptr ListEntities::run(RuntimeContext &ctx, CommandInput &input) const
{
   const auto player_only = input.has_flag("p");

   auto output = std::make_shared<ArrayObject>();

   auto entity = ctx.entity();
   if (not entity.has_value())
      return make_error(command_name, "command not performed on an entity");

   if (not entity->has_component<PlayerComponent>())
      return make_error(command_name, "entity doesn't have player component");

   auto &player_com = entity->component<PlayerComponent>();
   for (const auto entity_id : player_com.visible_entities()) {
      if (player_only) {
         auto *world = ctx.world();
         assert(world);

         if (not world->entity_system().entity(entity_id).has_component<PlayerComponent>())
            continue;
      }

      output->emplace_back(static_cast<int>(entity_id));
   }

   return output;
}

ObjectType ListEntities::return_type(RuntimeContext &ctx) const
{
   return command_return_type;
}

}// namespace minecpp::command::core
