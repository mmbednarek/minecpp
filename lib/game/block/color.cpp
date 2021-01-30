#include <minecpp/game/block/color.h>

namespace minecpp::game::block {

std::array<Color, 64> colors{
    0,        8368696,  16247203, 13092807, 16711680, 10526975, 10987431,
    31744,    16777215, 10791096, 9923917,  7368816,  4210943,  9402184,
    16776437, 14188339, 11685080, 6724056,  15066419, 8375321,  15892389,
    5000268,  10066329, 5013401,  8339378,  3361970,  6704179,  6717235,
    10040115, 1644825,  16445005, 6085589,  4882687,  55610,    8476209,
    7340544,  13742497, 10441252, 9787244,  7367818,  12223780, 6780213,
    10505550, 3746083,  8874850,  5725276,  8014168,  4996700,  4993571,
    5001770,  9321518,  2430480,  12398641, 9715553,  6035741,  1474182,
    3837580,  5647422,  1356933,
};

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
} // namespace minecpp::game::block