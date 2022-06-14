#include <minecpp/format/format.h>

namespace minecpp::format {

// TODO: Escape characters

Builder &Builder::text(std::string_view s)
{
   if (m_first) {
      m_node.text = s;
      return *this;
   }

   m_first = false;
   m_node.children.push_back(Node{.text = std::string(s)});
   m_first = false;
   return *this;
}

Builder &Builder::text(Color c, std::string_view s)
{
   m_node.children.push_back(Node{
           .text  = std::string(s),
           .color = c,
   });
   m_first = false;
   return *this;
}

Builder &Builder::bold(Color c, std::string_view s)
{
   m_node.children.push_back(Node{
           .text  = std::string(s),
           .color = c,
           .bold  = true,
   });
   m_first = false;
   return *this;
}

std::string Builder::to_string()
{
   std::stringstream ss;
   m_node.write(ss);
   return ss.str();
}

Node Builder::node()
{
   return m_node;
}

std::string_view color_to_str(Color c)
{
   switch (c) {
   case Color::Black: return "black";
   case Color::DarkBlue: return "dark_blue";
   case Color::DarkGreen: return "dark_green";
   case Color::DarkAqua: return "dark_aqua";
   case Color::DarkRed: return "dark_red";
   case Color::DarkPurple: return "dark_purple";
   case Color::Gold: return "gold";
   case Color::Gray: return "gray";
   case Color::DarkGray: return "dark_gray";
   case Color::Blue: return "blue";
   case Color::Green: return "green";
   case Color::Aqua: return "aqua";
   case Color::Red: return "red";
   case Color::LightPurple: return "light_purple";
   case Color::Yellow: return "yellow";
   case Color::White: return "white";
   }

   return "";
}

void Action::write(std::ostream &stream) const
{
   stream << R"({"action": ")" << action << R"(","value": ")" << value << "\"}";
}

void Node::write(std::ostream &stream) const
{
   stream << "{";
   bool next_item = false;
   stream << R"("text": ")" << text << R"(")";
   if (color)
      stream << R"(, "color": ")" << color_to_str(*color) << R"(")";
   if (bold)
      stream << R"(, "bold": ")" << *bold << R"(")";
   if (click_event) {
      stream << R"(, "clickEvent": )";
      click_event->write(stream);
   }
   if (hover_event) {
      stream << R"(, "hoverEvent": )";
      hover_event->write(stream);
   }

   if (not children.empty()) {
      stream << R"(, "extra": [)";
      bool first = true;
      for (const auto &child : children) {
         if (first) {
            first = false;
         } else {
            stream << ", ";
         };
         child.write(stream);
      }
      stream << "]";
   }
   stream << "}";
}
}// namespace minecpp::format
