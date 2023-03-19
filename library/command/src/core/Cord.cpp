#include <minecpp/command/core/Cord.h>

namespace minecpp::command::core {

bool Cord::is_flag(std::string_view /*name*/) const
{
   return false;
}

Object::Ptr Cord::run(RuntimeContext & /*ctx*/, CommandInput &input) const
{
   if (input.arg_count() != 3)
      return make_error(command_name, "invalid number of arguments");

   auto x = input.arg<int>(0);
   auto y = input.arg<int>(1);
   auto z = input.arg<int>(2);

   if (not x.has_value() || not y.has_value() || not z.has_value())
      return make_error(command_name, "invalid input type");

   return make_obj<game::BlockPosition>(*x, *y, *z);
}

ObjectType Cord::return_type(RuntimeContext & /*ctx*/) const
{
   return command_return_type;
}

}// namespace minecpp::command::core
