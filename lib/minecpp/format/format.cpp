#include <minecpp/format/format.h>

namespace Format {

Builder::Builder() { stream << "{\"extra\":["; }

// TODO: Escape characters

void Builder::text(std::string_view s) {
   if (!first) {
      stream << ",";
   }
   stream << R"({"color":"white","text":")" << s << "\"}";
   first = false;
}

void Builder::text(Color c, std::string_view s) {
   if (!first) {
      stream << ",";
   }
   stream << R"({"color":")" << color_to_str(c) << R"(","text":")" << s << "\"}";
   first = false;
}

void Builder::bold(Color c, std::string_view s) {
   if (!first) {
      stream << ",";
   }
   stream << R"({"color":")" << color_to_str(c) << R"(","bold":true,"text":")"
          << s << "\"}";
   first = false;
}

std::string Builder::build() {
   stream << R"(],"text":""})";
   return stream.str();
}

std::string_view color_to_str(Color c) {
   switch (c) {
   case Color::Black:
      return "black";
   case Color::DarkBlue:
      return "dark_blue";
   case Color::DarkGreen:
      return "dark_green";
   case Color::DarkAqua:
      return "dark_aqua";
   case Color::DarkRed:
      return "dark_red";
   case Color::DarkPurple:
      return "dark_purple";
   case Color::Gold:
      return "gold";
   case Color::Gray:
      return "gray";
   case Color::DarkGray:
      return "dark_gray";
   case Color::Blue:
      return "blue";
   case Color::Green:
      return "green";
   case Color::Aqua:
      return "aqua";
   case Color::Red:
      return "red";
   case Color::LightPurple:
      return "light_purple";
   case Color::Yellow:
      return "yellow";
   case Color::White:
      return "white";
   }

   return "";
}

} // namespace Format
