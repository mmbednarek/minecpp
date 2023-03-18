#pragma once

#include "Game.h"
#include <mb/enum.h>
#include <minecpp/format/Format.h>

namespace minecpp::game {

enum TeamValue
{
   Blue,
   Black,
   Red,
   Green
};

using Team_Base = mb::enum_wrapper<TeamValue, "Blue", "Black", "Red", "Green">;

class Team : public Team_Base
{
 public:
   MB_ENUM_TRAITS(Team)

   MB_ENUM_FIELD(Blue)
   MB_ENUM_FIELD(Black)
   MB_ENUM_FIELD(Red)
   MB_ENUM_FIELD(Green)

   [[nodiscard]] int sheep_color() const
   {
      /*
       * 0 - White
       * 1 - Orange
       * 2 - Purple
       * 3 - Aqua
       * 4 - Yellow
       * 5 - Green
       * 6 - Pink
       * 7 - Black / Dark Gray
       * 8 - Gray
       * 9 - Cyan
       * 10 - Dark Purple
       * 11 - Dark Blue
       * 12 - Brown
       * 13 - Dark Green
       * 14 - Red
       * 15 - Black
       */
      if (value() == Blue) {
         return 11;
      }
      return 15;
   }

   [[nodiscard]] Team next() const
   {
      if (value() == Blue) {
         return Black;
      }
      return Blue;
   }

   [[nodiscard]] format::Color color() const
   {
      if (value() == Blue) {
         return format::Color::Blue;
      }
      return format::Color::DarkGray;
   }

   [[nodiscard]] std::string_view material() const
   {
      if (value() == Blue) {
         return "diamond";
      }
      return "netherite";
   }
};

}// namespace minecpp::game