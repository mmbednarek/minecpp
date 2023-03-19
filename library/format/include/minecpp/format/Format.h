#pragma once
#include <memory>
#include <optional>
#include <sstream>
#include <vector>

namespace minecpp::format {

enum class Color : uint8_t
{
   Black,
   DarkBlue,
   DarkGreen,
   DarkAqua,
   DarkRed,
   DarkPurple,
   Gold,
   Gray,
   DarkGray,
   Blue,
   Green,
   Aqua,
   Red,
   LightPurple,
   Yellow,
   White,
};

struct Action
{
   std::string action;
   std::string value;

   void write(std::ostream &stream) const;
};

struct Node
{
   std::string text;
   std::optional<Color> color;
   std::optional<bool> bold;
   std::optional<Action> click_event;
   std::optional<Action> hover_event;
   std::vector<Node> children;

   void write(std::ostream &stream) const;
};

std::string_view color_to_str(Color c);

class Builder
{
 public:
   Builder &text(std::string_view s);
   Builder &text(Color c, std::string_view s);
   Builder &bold(Color c, std::string_view s);

   Node node();
   std::string to_string();

 private:
   Node m_node;
   bool m_first = true;
};

}// namespace minecpp::format