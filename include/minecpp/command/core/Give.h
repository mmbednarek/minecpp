#ifndef MINECPP_GIVE_H
#define MINECPP_GIVE_H
#include "../Command.h"

namespace minecpp::player {
class Provider;
}

namespace minecpp::command::core {

class Give : public Command
{
   player::Provider &m_provider;

 public:
   static constexpr auto command_return_type = ObjectType::String;

   explicit Give(player::Provider &provider);
   [[nodiscard]] bool is_flag(std::string_view name) const override;
   Object::Ptr run(RuntimeContext &ctx, CommandInput &input) const override;
   ObjectType return_type(RuntimeContext &ctx) const override;
};

}// namespace minecpp::command::core

#endif//MINECPP_GIVE_H
