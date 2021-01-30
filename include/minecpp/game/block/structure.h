#pragma once
#include <minecpp/util/enum.h>

namespace minecpp::game::block {

using StructureMode =
    minecpp::util::Enum<ENU("save"), ENU("load"), ENU("corner"), ENU("data")>;

}
