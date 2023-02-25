#ifndef MINECPP_FORMAT_H
#define MINECPP_FORMAT_H
#include "../Command.h"
#include <minecpp/format/Format.h>

namespace minecpp::command::core {

class Format : public Command
{
 public:
   Format(format::Color color, bool bold);

   [[nodiscard]] bool is_flag(std::string_view name) const override;
   ObjectType return_type(RuntimeContext &ctx) const override;
   Object::Ptr run(RuntimeContext &ctx, CommandInput &input) const override;

 private:
   format::Color m_color;
   bool m_bold;
};

}// namespace minecpp::command::core

#endif//MINECPP_FORMAT_H
