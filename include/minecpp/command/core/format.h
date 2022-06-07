#ifndef MINECPP_FORMAT_H
#define MINECPP_FORMAT_H
#include "../command.h"
#include <minecpp/format/format.h>

namespace minecpp::command::core {

class Format : public Command {
   format::Color m_color;
   bool m_bold;
 public:
   Format(format::Color color, bool bold);

   [[nodiscard]] bool is_flag(std::string_view name) const override;
   ObjectType return_type(RuntimeContext &ctx) const override;
   Object::Ptr run(RuntimeContext &ctx, CommandInput &input) const override;
};

}

#endif//MINECPP_FORMAT_H
