#include <algorithm>
#include <minecpp/command/ast/Ast.h>
#include <minecpp/command/Command.h>
#include <minecpp/command/CommandManager.h>
#include <minecpp/command/RuntimeContext.h>

namespace minecpp::command::ast {

Object::Ptr Command::execute(RuntimeContext &ctx)
{
   auto command = ctx.commands().command(name);
   if (command == nullptr)
      return {};

   CommandInput input(ctx, arguments, flags, params);
   return command->run(ctx, input);
}

ObjectType Command::type(RuntimeContext &ctx) const
{
   auto *command = ctx.commands().command(name);
   if (command == nullptr)
      return ObjectType::Null;
   return command->return_type(ctx);
}

Object::Ptr Variable::execute(RuntimeContext &ctx)
{
   return ctx.obj_variable(name);
}

ObjectType Variable::type(RuntimeContext &ctx) const
{
   return ctx.obj_variable(name)->type();
}

}// namespace minecpp::command::ast