#pragma once
#include <array>
#include <cstdint>
#include <mineutils/enum.h>

namespace Game::Block {
typedef uint32_t Color;

std::array<Color, 64> colors{
    0,        8368696,  16247203, 13092807, 16711680, 10526975, 10987431,
    31744,    16777215, 10791096, 9923917,  7368816,  4210943,  9402184,
    16776437, 14188339, 11685080, 6724056,  15066419, 8375321,  15892389,
    5000268,  10066329, 5013401,  8339378,  3361970,  6704179,  6717235,
    10040115, 1644825,  16445005, 6085589,  4882687,  55610,    8476209,
    7340544,  13742497, 10441252, 9787244,  7367818,  12223780, 6780213,
    10505550, 3746083,  8874850,  5725276,  8014168,  4996700,  4993571,
    5001770,  9321518,  2430480,
};

enum class ColorId : uint8_t {
   Air,
   Grass,
   Sand,
   Wool,
   Tnt,
   Ice,
   Iron,
   Foliage,
   Snow,
   Clay,
   Dirt,
   Stone,
   Water,
   Wood,
   Quartz,
   Adobe,
   Magenta,
   LightBlue,
   Yellow,
   Lime,
   Pink,
   Gray,
   LightGray,
   Cyan,
   Purple,
   Blue,
   Brown,
   Green,
   Red,
   Black,
   Gold,
   Diamond,
   Lapis,
   Emerald,
   Obsidian,
   Netherrack,
   WhiteTerracotta,
   OrangeTerracotta,
   MagentaTerracotta,
   LightBlueTerracotta,
   YellowTerracotta,
   LimeTerracotta,
   PinkTerracotta,
   GrayTerracotta,
   LightGrayTerracotta,
   CyanTerracotta,
   PurpleTerracotta,
   BlueTerracotta,
   BrownTerracotta,
   GreenTerracotta,
   RedTerracotta,
   BlackTerracotta,
};

using DyeColor =
    Utils::Enum<ENU("white"), ENU("orange"), ENU("magenta"), ENU("light_blue"),
                ENU("yellow"), ENU("lime"), ENU("pink"), ENU("gray"),
                ENU("light_gray"), ENU("cyan"), ENU("purple"), ENU("blue"),
                ENU("brown"), ENU("green"), ENU("red"), ENU("black")>;

ColorId dye_color_id(DyeColor color) {
   switch (color.index()) {
   case 0:
      return ColorId::Snow;
   case 1:
      return ColorId::Adobe;
   case 2:
      return ColorId::Magenta;
   case 3:
      return ColorId::LightBlue;
   case 4:
      return ColorId::Yellow;
   case 5:
      return ColorId::Lime;
   case 6:
      return ColorId::Pink;
   case 7:
      return ColorId::Gray;
   case 8:
      return ColorId::LightGray;
   case 9:
      return ColorId::Cyan;
   case 10:
      return ColorId::Purple;
   case 11:
      return ColorId::Blue;
   case 12:
      return ColorId::Brown;
   case 13:
      return ColorId::Green;
   case 14:
      return ColorId::Red;
   case 15:
      return ColorId::Black;
   }
   return ColorId::Black;
}

} // namespace Game::Block