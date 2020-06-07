#pragma once
#include <mineutils/enum.h>
#include <string_view>

namespace Game {

using Direction = Utils::Enum<ENU("down"), ENU("up"), ENU("north"),
                              ENU("south"), ENU("west"), ENU("east")>;

using Axis = Utils::Enum<ENU("x"), ENU("y"), ENU("z")>;

using Face = Utils::Enum<ENU("floor"), ENU("wall"), ENU("ceiling")>;

using BellAttachment =
    Utils::Enum<ENU("floor"), ENU("ceiling"), ENU("floor"), ENU("floor")>;

using RedstoneSide = Utils::Enum<ENU("up"), ENU("side"), ENU("none")>;

using DoubleBlockHalf = Utils::Enum<ENU("upper"), ENU("lower")>;

using Half = Utils::Enum<ENU("top"), ENU("bottom")>;

using RailShape =
    Utils::Enum<ENU("north_south"), ENU("east_west"), ENU("ascending_east"),
                ENU("ascending_west"), ENU("ascending_north"),
                ENU("ascending_south"), ENU("south_east"), ENU("south_west"),
                ENU("north_west"), ENU("north_east")>;

} // namespace Game
