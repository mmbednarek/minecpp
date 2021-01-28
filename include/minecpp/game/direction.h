#pragma once
#include <minecpp/mineutils/enum.h>
#include <string_view>

namespace Game {

using Direction = Utils::Enum<ENU("north"), ENU("east"), ENU("south"),
                              ENU("west"), ENU("up"), ENU("down")>;

using Axis = Utils::Enum<ENU("x"), ENU("y"), ENU("z")>;

using Face = Utils::Enum<ENU("floor"), ENU("wall"), ENU("ceiling")>;

using BellAttachment = Utils::Enum<ENU("floor"), ENU("ceiling"),
                                   ENU("single_wall"), ENU("double_wall")>;

using RedstoneSide = Utils::Enum<ENU("up"), ENU("side"), ENU("none")>;

using DoubleBlockHalf = Utils::Enum<ENU("upper"), ENU("lower")>;

using Half = Utils::Enum<ENU("top"), ENU("bottom")>;

using WallHeight = Utils::Enum<ENU("none"), ENU("low"), ENU("tall")>;

using RailShape =
    Utils::Enum<ENU("north_south"), ENU("east_west"), ENU("ascending_east"),
                ENU("ascending_west"), ENU("ascending_north"),
                ENU("ascending_south"), ENU("south_east"), ENU("south_west"),
                ENU("north_west"), ENU("north_east")>;

using JigsawOrientation =
    Utils::Enum<ENU("down_east"), ENU("down_north"), ENU("down_south"),
                ENU("down_west"), ENU("up_east"), ENU("up_north"),
                ENU("up_south"), ENU("up_west"), ENU("west_up"), ENU("east_up"),
                ENU("north_up"), ENU("south_up")>;

} // namespace Game
