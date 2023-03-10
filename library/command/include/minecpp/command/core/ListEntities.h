#pragma once

#include "../Command.h"

namespace minecpp::command::core {

class ListEntities : public Command
{
 public:
   static constexpr auto command_return_type = ObjectType::Array;
   static constexpr auto command_name        = "list-entities";

   [[nodiscard]] bool is_flag(std::string_view name) const override;
   Object::Ptr run(RuntimeContext &ctx, CommandInput &input) const override;
   ObjectType return_type(RuntimeContext &ctx) const override;
};

}// namespace minecpp::command::core