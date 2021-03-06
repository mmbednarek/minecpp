#pragma once
#include <array>
#include <cstdint>
#include <minecpp/util/enum.h>

namespace minecpp::game::block {

typedef uint32_t Color;

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
   CrimsonNylium,
   CrimsonStem,
   CrimsonHyphae,
   WarpedNylium,
   WarpedStem,
   WarpedHyphae,
   WarpedWart,
};

using DyeColor =
    minecpp::util::Enum<ENU("white"), ENU("orange"), ENU("magenta"), ENU("light_blue"),
                ENU("yellow"), ENU("lime"), ENU("pink"), ENU("gray"),
                ENU("light_gray"), ENU("cyan"), ENU("purple"), ENU("blue"),
                ENU("brown"), ENU("green"), ENU("red"), ENU("black")>;

ColorId dye_color_id(DyeColor color);

} // namespace minecpp::game::block