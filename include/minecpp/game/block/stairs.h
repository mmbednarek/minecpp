#pragma once
#include <minecpp/util/enum.h>

namespace minecpp::game::block {

using StairsShape = minecpp::util::Enum<ENU("straight"), ENU("inner_left"), ENU("inner_right"), ENU("outer_left"),
                                        ENU("outer_right")>;

}
