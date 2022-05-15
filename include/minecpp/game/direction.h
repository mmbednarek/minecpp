#pragma once
#include <minecpp/util/enum.h>
#include <string_view>

namespace minecpp::game {

using Direction =
        minecpp::util::Enum<ENU("north"), ENU("east"), ENU("south"), ENU("west"), ENU("up"), ENU("down")>;

using Axis = minecpp::util::Enum<ENU("x"), ENU("y"), ENU("z")>;

using BellAttachment =
        minecpp::util::Enum<ENU("floor"), ENU("ceiling"), ENU("single_wall"), ENU("double_wall")>;

using RedstoneSide = minecpp::util::Enum<ENU("up"), ENU("side"), ENU("none")>;

using DoubleBlockHalf = minecpp::util::Enum<ENU("upper"), ENU("lower")>;

using Half = minecpp::util::Enum<ENU("top"), ENU("bottom")>;

using WallHeight = minecpp::util::Enum<ENU("none"), ENU("low"), ENU("tall")>;

using RailShape =
        minecpp::util::Enum<ENU("north_south"), ENU("east_west"), ENU("ascending_east"),
                            ENU("ascending_west"), ENU("ascending_north"), ENU("ascending_south"),
                            ENU("south_east"), ENU("south_west"), ENU("north_west"), ENU("north_east")>;

using JigsawOrientation =
        minecpp::util::Enum<ENU("down_east"), ENU("down_north"), ENU("down_south"), ENU("down_west"),
                            ENU("up_east"), ENU("up_north"), ENU("up_south"), ENU("up_west"), ENU("west_up"),
                            ENU("east_up"), ENU("north_up"), ENU("south_up")>;

}// namespace minecpp::game
