#pragma once
#include <mineutils/enum.h>

namespace Game::Block {

using StairsShape =
    Utils::Enum<ENU("straight"), ENU("inner_left"), ENU("inner_right"),
                ENU("outer_left"), ENU("outer_right")>;

}
