#include <minecpp/command/core/Format.h>

namespace minecpp::command::core {

Format::Format(format::Color color, bool bold) :
    m_color(color),
    m_bold(bold)
{
}

bool Format::is_flag(std::string_view /*name*/) const
{
   return true;
}

ObjectType Format::return_type(RuntimeContext & /*ctx*/) const
{
   return ObjectType::FormattedString;
}

Object::Ptr Format::run(RuntimeContext & /*ctx*/, CommandInput &input) const
{
   auto str = std::make_shared<FormattedString>();

   for (const auto &obj : input) {
      if (obj->type() == ObjectType::FormattedString) {
         auto formatted_node = cast<FormattedString>(obj);
         if (formatted_node != nullptr) {
            std::copy(formatted_node->nodes.begin(), formatted_node->nodes.end(),
                      std::back_inserter(str->nodes));
         }
         continue;
      }

      str->nodes.emplace_back(FormattedString::Node{
              m_color,
              m_bold,
              obj->to_string(),
      });
   }
   return str;
}

}// namespace minecpp::command::core