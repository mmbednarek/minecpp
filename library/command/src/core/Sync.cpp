#include <minecpp/command/core/Sync.h>
#include <minecpp/command/RuntimeContext.h>
#include <minecpp/entity/component/Inventory.h>
#include <minecpp/entity/component/StreamingComponent.h>

namespace minecpp::command::core {

bool Sync::is_flag(std::string_view name) const
{
   return false;
}

ObjectType Sync::return_type(RuntimeContext &ctx) const
{
   return command_return_type;
}

namespace {

std::shared_ptr<RuntimeError> make_error(std::string_view message)
{
   auto err = std::make_shared<RuntimeError>("sync");
   err->text("player id not specified");
   return err;
}

}// namespace

Object::Ptr Sync::run(RuntimeContext &ctx, CommandInput &input) const
{
   auto *world = ctx.world();
   if (world == nullptr) {
      return make_error("world is empty");
   }

   auto *entity_id_obj = cast<IntObject>(ctx.variable("entity_id"));
   if (entity_id_obj == nullptr) {
      return make_error("entity id is not specified");
   }
   auto entity_id = static_cast<game::EntityId>(entity_id_obj->value);
   auto entity    = world->entity_system().entity(entity_id);

   auto *player_id = cast<UUIDObject>(ctx.variable("player_id"));
   if (player_id == nullptr) {
      return make_error("could not obtain player_id");
   }

   entity.component<minecpp::entity::component::Inventory>().synchronize_inventory(ctx.world()->dispatcher());
   entity.component<minecpp::entity::component::StreamingComponent>().send_all_visible_chunks(
           *world, player_id->value);

   auto info = std::make_shared<FormattedString>();
   info->bold(format::Color::Green, "INFO ");
   info->text(format::Color::White, "synchronized chunks and inventory");
   return info;
}
}// namespace minecpp::command::core
