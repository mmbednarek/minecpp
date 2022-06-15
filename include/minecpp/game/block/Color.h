#ifndef MINECPP_GAME_BLOCK_COLOR_H
#define MINECPP_GAME_BLOCK_COLOR_H
#include <array>
#include <cstdint>

namespace minecpp::game::block {

typedef uint32_t Color;

enum class ColorId : uint8_t
{
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
   CrimsonNylium,
   CrimsonStem,
   CrimsonHyphae,
   WarpedNylium,
   WarpedStem,
   WarpedHyphae,
   WarpedWart,
};

constexpr std::array<Color, 64> g_colors{
        0,        8368696, 16247203, 13092807, 16711680, 10526975, 10987431, 31744,    16777215, 10791096,
        9923917,  7368816, 4210943,  9402184,  16776437, 14188339, 11685080, 6724056,  15066419, 8375321,
        15892389, 5000268, 10066329, 5013401,  8339378,  3361970,  6704179,  6717235,  10040115, 1644825,
        16445005, 6085589, 4882687,  55610,    8476209,  7340544,  13742497, 10441252, 9787244,  7367818,
        12223780, 6780213, 10505550, 3746083,  8874850,  5725276,  8014168,  4996700,  4993571,  5001770,
        9321518,  2430480, 12398641, 9715553,  6035741,  1474182,  3837580,  5647422,  1356933,
};

}// namespace minecpp::game::block

#endif//MINECPP_GAME_BLOCK_COLOR_H