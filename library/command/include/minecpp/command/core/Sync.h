#pragma once
#include "../Command.h"

namespace minecpp::command::core {

class Sync : public Command
{
 public:
   static constexpr auto command_return_type = ObjectType::String;

   [[nodiscard]] bool is_flag(std::string_view name) const override;
   ObjectType return_type(RuntimeContext &ctx) const override;
   Object::Ptr run(RuntimeContext &ctx, CommandInput &input) const override;
};

}