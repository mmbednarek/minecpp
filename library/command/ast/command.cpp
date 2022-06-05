#include <algorithm>
#include <minecpp/command/ast/ast.h>
#include <minecpp/command/command_manager.h>
#include <minecpp/command/command.h>
#include <minecpp/command/runtime_context.h>

namespace minecpp::command::ast {

Object::Ptr Command::execute(RuntimeContext &ctx)
{
   auto command = ctx.commands().command(name);
   if (command == nullptr)
      return {};

   CommandInput input{
           .flags = flags,
   };

   input.arguments.resize(arguments.size());
   std::transform(arguments.begin(), arguments.end(), input.arguments.begin(),
                  [&ctx](Expression::Ptr &expr) { return expr->execute(ctx); });

   for (const auto &[param, expr] : params) {
      input.params[param] = expr->execute(ctx);
   }

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
   return ctx.variable(name);
}

ObjectType Variable::type(RuntimeContext& ctx) const
{
   return ctx.variable(name)->type();
}

}// namespace minecpp::command::ast