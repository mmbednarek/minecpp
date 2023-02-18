#ifndef MINECPP_GIVE_H
#define MINECPP_GIVE_H
#include "../Command.h"

namespace minecpp::game {
class IEntitySystem;
}

namespace minecpp::command::core {

class Give : public Command
{
 public:
   static constexpr auto command_return_type = ObjectType::String;

   [[nodiscard]] bool is_flag(std::string_view name) const override;
   Object::Ptr run(RuntimeContext &ctx, CommandInput &input) const override;
   ObjectType return_type(RuntimeContext &ctx) const override;
};

}// namespace minecpp::command::core

#endif//MINECPP_GIVE_H
